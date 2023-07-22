/* Importações das bibliotecas */
#include <WiFi.h>
#include <WiFiClient.h>
#include <Wire.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* definindo pinos e constantes */
#define WIFI_SSID  "NOME DA SUA REDE WI FI"
#define WIFI_PASS  "**********************"
#define TRIG_PIN    5
#define ECHO_PIN   18
#define LED        26 
#define BUZZER     27
#define B_CHANNEL   0

/* handles do semaforo e fila */
SemaphoreHandle_t xSerialSemaphore;
xQueueHandle xFila;

/* variaveis do sistema */
int queueSize = 5;
bool isNearby;
float distance;
const int limitDistance = 100;
int duration;
WiFiClient client;

/* Protótipos das funções */
void TaskLed(void *pvParameters);
void TaskBuzzer(void *pvParameters);
void TaskReadSensorData(void *pvParameters);
float readDistanceCM();
void initPins();
void initSerial();
void initQueue();
void initSemaphore();
void initWiFi();

void setup() {
  initPins();
  initSerial();
  initQueue();
  initSemaphore();
  initWiFi();

  // Tasks
  xTaskCreate( TaskReadSensorData, "HC-SR04", 5000, NULL, 1, NULL );
  xTaskCreate( TaskBuzzer, "Buzzer", 5000, NULL, 2, NULL );
  xTaskCreate( TaskLed, "Led", 5000, NULL, 3, NULL );
}

void loop() {}

/* Leitura das distâncias */
float readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  
  return duration * 0.034 / 2;
}

/* Inicializa os pinos dos componentes do circuito */
void initPins(){
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

/* Inicializa o Serial */
void initSerial(){
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
}

/* Cria a fila de execução */
void initQueue(){
  xFila = xQueueCreate(queueSize, sizeof(int));

  if(xFila == NULL){
    Serial.println("Erro ao criar fila");
  }
}

/* Cria o semáforo mutex */
void initSemaphore(){
  if ( xSerialSemaphore == NULL ){
    xSerialSemaphore = xSemaphoreCreateMutex();
    if ( ( xSerialSemaphore ) != NULL ) {
      xSemaphoreGive( ( xSerialSemaphore ) );
    }
  }
}

/* Configuração da conexão WiFi */
void initWiFi(){
  Serial.println("Conectando-se na rede: " + String(WIFI_SSID));
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delayMicroseconds(100000);
    Serial.print(".");
  }
  
  Serial.println("\nConectado à rede com sucesso");
  Serial.println("Endereço IP: " + String(WiFi.localIP()));
}

/* Tarefa da leitura do sensor: lê as distância com o sensor ultrassônico HC-SR04 */
void TaskReadSensorData(void *pvParameters){

  (void) pvParameters;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  BaseType_t xStatus;
  float distanceRead;

  for(;;){
    // leitura das distâncias
    xSemaphoreTake(xSerialSemaphore, portMAX_DELAY );

    distanceRead = readDistanceCM();

    xStatus = xQueueSendToFront( xFila, &distanceRead, portMAX_DELAY );
    if( xStatus == pdPASS ) {
      Serial.println("["+String(millis())+" ms]: " + "send = " + String(distanceRead) + " cm");
    }

    xSemaphoreGive(xSerialSemaphore);
    vTaskDelay(1000 / portTICK_PERIOD_MS); // delay de 1 segundo
  }

  vTaskDelete( NULL );
}

/* Tarefa do buzzer: toca quando o sensor medir uma distancia menor que "limitDistance"*/
void TaskBuzzer(void *pvParameters){

  (void) pvParameters;
  float distanceRead;
  BaseType_t xStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

  for(;;){
    xStatus = xQueueReceive( xFila, &distanceRead, portMAX_DELAY );
    
    if(xStatus == pdPASS){

      isNearby = distanceRead < limitDistance;
      
      // Toca o buzzer se a distancia lida for menor que a distancia limite.
      if(isNearby) {  
        ledcAttachPin(BUZZER, B_CHANNEL);
        ledcWriteNote(B_CHANNEL, NOTE_F, 4);
      } else {
        ledcDetachPin(BUZZER);
      }

      Serial.println("["+String(millis())+" ms]: " + "received = " + String(distanceRead) + " cm");
    }
  }

  vTaskDelete( NULL );
}

/* Tarefa do led indicador de temporização: pisca a cada segundo */
void TaskLed(void *pvParameters){
  
  (void) pvParameters;

  for(;;){
    digitalWrite(LED, !digitalRead(LED)); // Troca o estado do led
    vTaskDelay(1000 / portTICK_PERIOD_MS); // delay de 1 segundo
  }

  vTaskDelete( NULL );
}