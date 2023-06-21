/*
   Este código trata-se de um gerenciador de tarefas baseado num    
   kernel cooperativo (não preemptivo.)
   Para isso, utilizou-se um buffer estático para armazenar as tarefas;
   As tarefas são escalonadas de acordo com a interrupção do Timer1.     
   Este verifica o tempo restante para cada tarefa ser executada.
   A tarefa que atingir o tempo primeiro, será executada.
   As "prioridades" das tarefas é por ordem de adição no buffer.
   Autor: Caio Moraes (Embarcados.com.br, 2017)
   Modificação: Luis Claudio (2018)
*/ 

#include "avr/wdt.h"
#include "TimerOne.h" // Se for simular no TinkerCad, remover e usar registradores

#define NUMBER_OF_TASKS  4
#define TEMPO_MAXIMO_EXECUCAO 100   // 100ms
#define SUCCESS 1
#define FAIL    0
#define SIM 1
#define NAO 0

typedef void(*ptrFunc)();  // Definição ponteiro de função

// Definição da estrutura que contem as informações das tarefas
typedef struct{
  ptrFunc Function;
  uint32_t period;
  bool enableTask; 
} TaskHandle;

// Definição do buffer para armazenar as tarefas
TaskHandle* buffer[NUMBER_OF_TASKS]; 

// Variáveis globais do kernel
volatile uint32_t taskCounter[NUMBER_OF_TASKS];
volatile int16_t TempoEmExecucao;
volatile uint32_t sysTickCounter = 0;
volatile bool TemporizadorEstourou;
volatile bool TarefaSendoExecutada;
int contador = 0;
int ordem = 0;
int estado = 0;


//---------------------------------------------------------------------------------------------------------------------
// Função vKernelInit()
// Descrição: Inicializa as variáveis utilizadas pelo kernel, e o temporizador resposável pelo tick
// Parâmetros: nenhum
// Saida: nenhuma
//---------------------------------------------------------------------------------------------------------------------
char KernelInit()
{
  memset(buffer, NULL, sizeof(buffer));    // Inicializa o buffer para funções
  memset(taskCounter, 0, sizeof(taskCounter)); 

  TemporizadorEstourou = NAO;
  TarefaSendoExecutada = NAO;

  // Base de tempo para o escalonador
  Timer1.initialize(10000);             // 10ms
  Timer1.attachInterrupt(IsrTimer);    // chama vIsrTimer() quando o timer estoura

  return SUCCESS;
}//end vKernelInit


//---------------------------------------------------------------------------------------------------------------------
// Função KernelAdd()
// Descrição: Adiciona uma nova Tarefa ao pool
// Parâmetros: funcao da tareda, nome, periodo, habilita e estrutura para guardar as informações da tarefa
// Saida: nenhuma
//---------------------------------------------------------------------------------------------------------------------
char KernelAdd(TaskHandle* task)
{
  int i;
 
  // Verifica se já existe a tarefa no buffer
  for(i = 0; i < NUMBER_OF_TASKS; i++)
  {
    if((buffer[i]!=NULL) && (buffer[i] == task))
       return SUCCESS;
  }

  // Adiciona a tarefa em um slot vazio
  for(i = 0; i < NUMBER_OF_TASKS; i++)
  {
    if(!buffer[i])
    {
      buffer[i] = task;
      return SUCCESS;
    }
  }
  return FAIL;
}//end vKernelAdd


//---------------------------------------------------------------------------------------------------------------------
// Função KernelRemoveTask()
// Descrição: de forma contrária a função KernelAddTask, esta função remove uma Tarefa do buffer circular
// Parâmetros: Nenhum
// Saída: Nenhuma
//---------------------------------------------------------------------------------------------------------------------
char KernelRemoveTask(TaskHandle* task)
{
  int i;
  for(i=0; i<NUMBER_OF_TASKS; i++)
  {
     if(buffer[i] == task)
     {
        buffer[i] = NULL;
        return SUCCESS; 
     }
  }
  return FAIL;

}//end vKernelRemoveTask


//---------------------------------------------------------------------------------------------------------------------
// Função KernelLoop()
// Descrição: função responsável por escalonar as tarefas de acordo com a resposta da interrupção do Timer 1
// Parâmetros: Nenhum
// Saída: Nenhuma
//---------------------------------------------------------------------------------------------------------------------
void KernelLoop()
{
  int i;

  for (;;)
  {
    if (TemporizadorEstourou == SIM)
    {
      for (i = 0; i < NUMBER_OF_TASKS; i++)
      {
        if (buffer[i] != 0)
        {
          if (((sysTickCounter - taskCounter[i])>buffer[i]->period) && (buffer[i]->enableTask == SIM))
          {
            TarefaSendoExecutada = SIM;
            TempoEmExecucao = TEMPO_MAXIMO_EXECUCAO;
            buffer[i]->Function();
            TarefaSendoExecutada = NAO;
            taskCounter[i] = sysTickCounter;
          }
        }
      }
    }
  }
}//end vKernelLoop


//---------------------------------------------------------------------------------------------------------------------
// Trata a Interrupção do timer 1
// Decrementa o tempo para executar de cada tarefa
// Se uma tafera estiver em execução, decrementa o tempo máximo de execução para reiniciar o MCU caso ocorra
// algum travamento
//---------------------------------------------------------------------------------------------------------------------
void IsrTimer()
{
  int i;
  TemporizadorEstourou = SIM;

  sysTickCounter++;
  
  // Conta o tempo em que uma tarefa está em execução
  if (TarefaSendoExecutada == SIM)
  {
    TempoEmExecucao--;
    if (!TempoEmExecucao)
    {
      // possivelmente a tarefa travou, então, ativa o WDT para reiniciar o micro
      wdt_enable(WDTO_15MS);
      while (1);
    }
  }
}//end vIsrTimer


// Aqui embarcamos o resto do código: processos, funções auxiliares, void setup() e void loop() "vazio".

char proc1() {
  if (ordem == 0)
    contador++;
  else
    contador--;
  Serial.println("Contador "+String(contador));
}


char proc2() {
  int valorBotao = digitalRead(2);
  if (valorBotao == LOW && estado == 0) {
    if (ordem == 0)
      ordem = 1;
    else
      ordem = 0;
    estado = 1;
  }
  if (valorBotao == HIGH && estado == 1) {
    estado = 0;
  }
}


char proc3() {
  digitalWrite(13,!digitalRead(13));
}


char proc4() {
  float temperatura;
  temperatura = (float(analogRead(A0))*5/(1023))/0.01;
  Serial.print("Temperatura: ");
  Serial.println(temperatura);
}


void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  pinMode(13,OUTPUT);
  TaskHandle task1 = {proc1, 1000, SIM}; 
  TaskHandle task2 = {proc2, 110, SIM};
  TaskHandle task3 = {proc3, 1000, SIM};
  TaskHandle task4 = {proc4, 200, SIM};
  KernelInit();
  KernelAdd(&task1);
  KernelAdd(&task2);
  KernelAdd(&task3);
  KernelAdd(&task4);
  KernelLoop();
}


void loop() {}
