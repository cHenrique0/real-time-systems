typedef char (*ptrFunc)(void);

// vetor de processos
#define POOL_SIZE 5
#define SUCCESS 0
#define FAIL 1
#define REPEAT 2

ptrFunc pool[POOL_SIZE];
int ini, fim;
int globalContador = 0;

void print(String msg) {
  Serial.println(msg);
}

char contador(void) {
  globalContador++;
  return REPEAT;
}

// protótipo das funções do kernel
char kernelInit(void);
char kernelAdd(ptrFunc nFunc);
void kernelLoop(void);

// implementação das funções do kernel
char kernelInit(void) {
  ini = 0; fim = 0;
  return SUCCESS;
}

char kernelAdd(ptrFunc nFunc) {
  // checa a existência de espaço livre
  if ((fim+1)%POOL_SIZE != ini) {
    pool[fim] = nFunc;
    fim = (fim+1)%POOL_SIZE;
    return SUCCESS;
  }
  return FAIL;
}

void KernelLoop(void) {
  for (;;) {
    // Testa se há processos pra rodar
    if (ini != fim) {
      // Executa a primeira função
      if ((*pool[ini])() == REPEAT) {
          kernelAdd(pool[ini]); // Agendado
      }
      // Próximo processo
      ini = (ini+1)%POOL_SIZE;
      delay(400); // Pausa entre a execução das tarefas
    }
  }
}

char proc1(void) {
  print("Processo 1 "+String(ini));
  return REPEAT;
}

char proc2(void) {
  print("Processo 2 "+String(ini));
  return REPEAT;
}

char proc3(void) {
  print("Processo 3 "+String(ini));
  return REPEAT;
}

// utilizando o kernel – função principal
void setup() {
  Serial.begin(9600);
  kernelInit();
  kernelAdd(proc1);
  kernelAdd(proc2);
  kernelAdd(proc3);
  KernelLoop();
}
