#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Configuração do display LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Define o endereço e as dimensões do LCD

// Definindo os pinos dos LEDs de semáforo
#define ledVerde 12      // LED verde no pino 12
#define ledAmarelo 26    // LED amarelo no pino 26
#define ledVermelho 32   // LED vermelho no pino 32

// Configurações iniciais
void setup() {
  pinMode(ledVerde, OUTPUT);    // Define o LED verde como saída
  pinMode(ledAmarelo, OUTPUT);  // Define o LED amarelo como saída
  pinMode(ledVermelho, OUTPUT); // Define o LED vermelho como saída

  lcd.init();          // Inicializa o display LCD
  lcd.backlight();     // Liga a luz de fundo do display
}

// Função para controlar o comportamento dos LEDs
void acenderLed(int led, int time, bool travessia) {
  digitalWrite(led, HIGH);  // Acende o LED especificado
  delay(time);              // Mantém o LED aceso pelo tempo especificado
  lcd.clear();              // Limpa o display LCD

  if (travessia == false) {
    digitalWrite(led, LOW); // Apaga o LED se não for travessia de pedestre
  } else {
    // Pisca o LED 5 vezes se for travessia de pedestre
    for (int i = 0; i < 5; i++) {
      digitalWrite(led, HIGH);
      delay(200);
      digitalWrite(led, LOW);
      delay(200);
    }
  }
}

// Função para exibir mensagens no LCD
void exibirMensagem(String sms1, String sms2) {
  lcd.print(sms1);       // Exibe a primeira linha de mensagem
  lcd.setCursor(0, 1);   // Move o cursor para a segunda linha
  lcd.print(sms2);       // Exibe a segunda linha de mensagem
}

// Loop principal que simula um ciclo de semáforo
void loop() {
  acenderLed(ledVermelho, 6000, false);       // Acende o LED vermelho por 6 segundos
  exibirMensagem("Atencao, Carro", "Passando!"); // Exibe mensagem no LCD

  acenderLed(ledAmarelo, 2000, false);        // Acende o LED amarelo por 2 segundos
  exibirMensagem("Atencao, ainda", "nao passe!");

  acenderLed(ledVerde, 2000, true);           // Acende o LED verde por 2 segundos e pisca
  exibirMensagem("Agora, pode", "passar!");

  acenderLed(ledAmarelo, 2000, false);        // Acende o LED amarelo novamente por 2 segundos
  exibirMensagem("Atencao, ainda", "nao passe!");
}
