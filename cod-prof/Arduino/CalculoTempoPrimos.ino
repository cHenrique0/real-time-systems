long frequency_of_primes (long n)
{
    long i,j;
    long freq=n-1;
    for (i=2; i<=n; ++i)
    {
      j=(int)sqrt(i);
      while (j>1) {
        if (i%j==0)
            {
            --freq;
            break;
        }
        --j;
      }
    }
    return freq;
}

long tInicio, tFim, t;
long n, f;

void setup() {
  Serial.begin(9600);
  delay(100);

  n = 9999;
  tInicio = micros();
  f = frequency_of_primes(n);
  tFim = micros();
  
  t = tFim-tInicio;

  Serial.println("Exemplo de cálculo de tempo de processamento!");
  Serial.print("Numero de primos menores que ");
  Serial.print(n);
  Serial.print(": ");
  Serial.println(f);
  Serial.print("Tempo gasto: ");
  Serial.println(t);
}

void loop() {}
