#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t  xSerialSemaphore;

void TaskDigitalRead( void *pvParameters );
void TaskAnalogRead( void *pvParameters );

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
  xTaskCreate( TaskAnalogRead, "AnalogRead", 128, NULL, 1, NULL );

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


void TaskAnalogRead( void *pvParameters )
{

  for(;;)
  {
    int sensorValue = analogRead(A0);
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      Serial.println(sensorValue);
      xSemaphoreGive( xSerialSemaphore );
    }
    vTaskDelay(1);
  }
}
