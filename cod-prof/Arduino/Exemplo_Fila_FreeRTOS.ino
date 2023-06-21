#include <Arduino_FreeRTOS.h>
#include <queue.h>

QueueHandle_t xFila;

static void Producer( void *pvParameters );
static void Consumer( void *pvParameters );

int tamFila = 10;

void setup() {
   Serial.begin(9600);
   while(!Serial) ;
   xFila = xQueueCreate( tamFila, sizeof( int ) );
   if(xFila == NULL){
    Serial.println("Erro criando fila");
  }
  xTaskCreate( Producer, ( const char * ) "Produtor", 100, NULL, 1, NULL );
  xTaskCreate( Consumer, ( const char * ) "Consumidor", 100, NULL, 1, NULL );
}

void loop() {}

static void Producer( void *pvParameters )
{
   for( int i = 0; i < tamFila; i++ ){
      xQueueSend(xFila, (void *)&i, portMAX_DELAY);
   }
   vTaskDelete( NULL );
}

static void Consumer( void *pvParameters )
{
   int element;
 
   for( int i = 0; i < tamFila; i++ ){
 
      xQueueReceive(xFila, (void *)&element, portMAX_DELAY);
      Serial.print(element);
      Serial.print("|");
   }
   vTaskDelete( NULL );
}
