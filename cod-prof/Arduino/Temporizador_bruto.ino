// Temporizador bruto usando for usando ATmega328P (UNO) - 16 MHz
// Tempo de acesso usando for com "100 loops" para os tipos char e int

// char: 29.0 us (não recomendado, otimização do compilador)
// volatile char: aprox. 70 us

// int: 42,2 us
// volatile int: 120.8 us

int contador = 0;

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() {
  digitalWrite(13,HIGH);
  delay1s();
  digitalWrite(13,LOW);
  delay1s();
  Serial.println(contador);
}

void delay1s() {
  volatile char i;
  volatile unsigned int j;
  for (j=0; j < 14286; j++)    // 14285.7*70 ~ 0.999999 s
  {
    for (i=0; i < 100; i++) ;  // 100 loops ~ 70us
  }
  contador++;
}
