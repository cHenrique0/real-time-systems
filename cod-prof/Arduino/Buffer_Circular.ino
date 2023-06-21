#define CB_SIZE 5
#define SUCESS 1
#define FAIL 0

int circular_buffer[CB_SIZE];
int start = 0;
int end = 0;

char AddBuff(int newData) {
  // checa se ha espaco para inserir um novo dado
  if ( ((end+1)%CB_SIZE) != start ) {
    circular_buffer[end] = newData;
    end = (end+1)%CB_SIZE;
    return SUCESS;
  }
  return FAIL;
}

char RemoveBuff() {
  // testa se tem dados
  if (start != end) {
    int dado = circular_buffer[start];
    start = (start+1)%CB_SIZE;
    return dado;
  }
}

void setup()
{
  Serial.begin(9600);
  teste();
}

void loop() {}

void teste() {
  int dado;
  
  if (AddBuff('A')) Serial.println("'A' inserido");
  if (AddBuff('B')) Serial.println("'B' inserido");
  if (AddBuff('C')) Serial.println("'C' inserido");
  if (AddBuff('D')) Serial.println("'D' inserido");
  if (AddBuff('E')) Serial.println("'E' inserido");
  
  dado = RemoveBuff();
  Serial.print("Removendo ");
  Serial.println((char)dado);
  
  Serial.println("Buffer:");
  imprimeBuffer();
  
  if (AddBuff('E')) Serial.println("'E' inserido");
  Serial.println("Buffer:");
  imprimeBuffer();
  
  dado = RemoveBuff();
  Serial.print("Removendo ");
  Serial.println((char)dado);
  
  Serial.println("Buffer:");
  imprimeBuffer();
  
  if (AddBuff('F')) Serial.println("'F' inserido");
  if (AddBuff('G')) Serial.println("'G' inserido");
  
  Serial.println("Buffer:");
  imprimeBuffer();
}

void imprimeBuffer() {
  int aux = start;
  while (aux != end)
  {
    int dado = circular_buffer[aux];
    aux = (aux+1)%CB_SIZE;
    Serial.print((char)dado);
    Serial.print(" ");
  }
  Serial.println("");
}
