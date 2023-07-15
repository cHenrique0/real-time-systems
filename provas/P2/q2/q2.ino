#define INTERVAL1 1500
#define INTERVAL2 5000
#define INTERVAL3 3500

unsigned long limiteTarefa1 = INTERVAL1;
unsigned long limiteTarefa2 = INTERVAL2;
unsigned long limiteTarefa3 = INTERVAL3;
unsigned long timeTarefa1;
unsigned long timeTarefa2;
unsigned long timeTarefa3;

const unsigned int gLedPin = 11;
const unsigned int rLedPin = 4;
const unsigned int motorPin = 7;
const unsigned int buzzerPin = 10;
const unsigned int button = 2;

bool buzzerState = false;

void info(String tarefa, String id, unsigned int tempo);
void interruptThread();

void setup() {
  timeTarefa1 = 0;
  timeTarefa2 = 0;
  timeTarefa3 = 0;
  
  pinMode(gLedPin, OUTPUT);
  pinMode(rLedPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  digitalWrite(motorPin, LOW);
  
  attachInterrupt(digitalPinToInterrupt(button), interruptThread, FALLING);
  
  Serial.begin(9600);
}

void loop() {
  // Tarefa 1 - Led Verde
  unsigned int timeDiffT1 = millis() - timeTarefa1;
  if(timeDiffT1 > limiteTarefa1){
    digitalWrite(gLedPin, !digitalRead(gLedPin));
    timeTarefa1 = millis();
    info("Trocar estado do led verde", "T1", timeTarefa1);
  }

  // Tarefa 2 - Motor DC
  unsigned int timeDiffT2 = millis() - timeTarefa2;
  if(timeDiffT2 > limiteTarefa2){
    digitalWrite(motorPin, !digitalRead(motorPin));
    timeTarefa2 = millis();
    info("Motor DC", "T2", timeTarefa2);
  }

  // Tarefa 3 - Buzzer
  unsigned int timeDiffT3 = millis() - timeTarefa3;
  if (timeDiffT3 > limiteTarefa3) {
    tone(buzzerPin, 1000, 500);
    timeTarefa3 = millis();
    info("Tocar buzzer", "T3", timeTarefa3);
  }
}

void info(String tarefa, String id, unsigned int tempo) {
  Serial.println("\nID: " + id);
  Serial.println("Tarefa: " + tarefa);
  Serial.println("Tempo: " + String(tempo) + " ms");
  Serial.println("Status: executado");
}

void interruptThread() {
  digitalWrite(rLedPin, !digitalRead(rLedPin));
  digitalWrite(gLedPin, !digitalRead(gLedPin));
  digitalWrite(motorPin, !digitalRead(motorPin));
  noTone(buzzerPin);
  info("INTERRUPT", "ISR", millis());
}