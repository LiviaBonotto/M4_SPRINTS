#define led_azul 41 
#define led_verde 6 
#define led_amarelo 10
#define led_vermelho 8
#define captura_btn 1 //botão da esqueda - captura leitura
#define toca_btn 2 //botão da direita - reproduz leituras
#define ldr 14
#define buzzer 18

int binario[4]; // quantidade de número binários
int frequencias[100]; //quantidade max de valores armazenados
int pos = 0; // variável que chama a posição do valor armazenado


//definindo entradas e saídas
void setup() {

  Serial.begin(115200);
  pinMode(led_azul, OUTPUT);
  pinMode(led_verde, OUTPUT);
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(captura_btn, INPUT_PULLUP);
  pinMode(toca_btn, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

}


//associando os leds aos valores binários - faz eles ligarem de acordo com o valor
void leds(){

  if (binario[0] == 0) { //posição 1 do valor binário = 0 -> led desligado
      digitalWrite(led_vermelho, LOW);
    } else { //caso contrário, ele liga
      digitalWrite(led_vermelho, HIGH);
    }

    if (binario[1] == 0) { //para a posição 2
      digitalWrite(led_amarelo, LOW);
    } else {
      digitalWrite(led_amarelo, HIGH);
    }

    if (binario[2] == 0) { //para a posição 3
      digitalWrite(led_verde, LOW);
    } else {
      digitalWrite(led_verde, HIGH);
    }

    if (binario[3] == 0) { //para a posição 4
      digitalWrite(led_azul, LOW);
    } else {
      digitalWrite(led_azul, HIGH);
    }
}


//fazendo a conversão dos valores binários
void converte_bin(int valor) {

  for (int i = 0; i <= 3; i++) {

    if (valor >= 1) {

      binario[i] = valor % 2;
      valor = valor / 2;

    } else {

      binario[i] = 0;

    }
  }
}


void loop() {

  //recebe a leitura do LDR
  int leituraLDR = analogRead(ldr);
  //Serial.println(leituraLDR);

  int leitura_bin = leituraLDR / 257;

  converte_bin(leitura_bin);

  leds();

//ao pressionar o botão de captura, lê o valor binário, emite um som correspondente e guarda a leitura
  if (digitalRead(captura_btn) == LOW) {

    frequencias[pos] = leitura_bin;
    tone(buzzer, frequencias[pos]*100, 350); //multiplica por 100 para ser um som audível
    Serial.println(frequencias[pos]);
    pos += 1;
    delay(500);
  }

//ao pressionar o botão de tocar, vai ler as leituras feitas anteriormente e emitir
  if (digitalRead(toca_btn) == LOW) {

    while (pos >= 0) {
      converte_bin(frequencias[pos]);
      delay(500);
      tone(buzzer, frequencias[pos]*100, 350);
      leds();

      Serial.println(frequencias[pos]);

      pos = pos-1;
    }

  }
  delay(500);
}