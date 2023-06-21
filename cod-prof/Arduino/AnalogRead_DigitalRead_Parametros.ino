#include <Arduino_FreeRTOS.h>
#include <semphr.h>

//tipo de parâmetros
typedef struct {
  const char *pcNomeTask;
  const char *pcTexto;
  int SensorID;
  int TempoDelayTicks;
} AnalogReadParametro_t;


SemaphoreHandle_t xSerialSemaphore;

void TaskDigitalRead( void *pvParameters );
void TaskAnalogReadParam( void *pvParameters );

AnalogReadParametro_t xParams[3], *pxParam = xParams;


void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  if ( xSerialSemaphore == NULL )
  {
    xSerialSemaphore = xSemaphoreCreateMutex();
    if ( ( xSerialSemaphore ) != NULL )
      xSemaphoreGive(( xSerialSemaphore ));
  }

  xTaskCreate( TaskDigitalRead, "DigitalRead", 128, NULL, 2, NULL );

  pxParam->pcNomeTask = "TaskEntradaA1";
  pxParam->pcTexto = "Entrada A1";
  pxParam->SensorID = A1;
  pxParam->TempoDelayTicks = pdMS_TO_TICKS( 250 );
  pxParam++;
  
  pxParam->pcNomeTask = "TaskEntradaA2";
  pxParam->pcTexto = "Entrada A2";
  pxParam->SensorID = A2;
  pxParam->TempoDelayTicks = 1; // 1 Tick = 15 ms
  pxParam++;
  
  pxParam->pcNomeTask = "TaskEntradaA3";
  pxParam->pcTexto = "Entrada A3";
  pxParam->SensorID = A3;
  pxParam->TempoDelayTicks = 1; // 1 Tick = 15 ms

  for (pxParam = xParams; pxParam < &xParams[3]; pxParam++)  // for (int i = 0; i < 3; i++)
  {
    Serial.println("\n--------------------------");
    Serial.print("Criando ");
    Serial.println(pxParam->pcNomeTask);
    xTaskCreate( TaskAnalogReadParam, pxParam->pcNomeTask, 128, (void *)pxParam, 2, NULL );
  }

}

void loop() {}

void TaskDigitalRead( void *pvParameters )
{

  uint8_t pushButton = 2;
  pinMode(pushButton, INPUT);

  for (;;)
  {
    int buttonState = digitalRead(pushButton);

    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      Serial.println(buttonState);
      xSemaphoreGive( xSerialSemaphore );
    }
    vTaskDelay(1);
  }
}


void TaskAnalogReadParam( void *pvParameters )
{
  AnalogReadParametro_t *pxParams = (AnalogReadParametro_t *) pvParameters;
  
  for(;;)
  {
    int sensorValue = analogRead(pxParams->SensorID);
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      Serial.print(pxParams->pcTexto);
      Serial.print(": ");
      Serial.println(sensorValue);
      xSemaphoreGive( xSerialSemaphore );
    }
    vTaskDelay(pxParams->TempoDelayTicks);
  }
}
