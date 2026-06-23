#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     -1 
// Declaração do pino e tipo do sensor (mude para DHT22 se for o caso)
#define DHTPIN 2     
#define DHTTYPE DHT22 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  // Inicializa o display com o endereço I2C 0x3C
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;); // Trava se não encontrar o display
  }
}
void drawBox() {
  display.clearDisplay();

  // Desenha as linhas verticais
  for (int x = 0; x <= SCREEN_WIDTH; x += 63) {
    display.drawLine(x, 0, x, SCREEN_HEIGHT, SSD1306_WHITE);
  }

  // Desenha as linhas horizontais
  for (int y = 0; y <= SCREEN_HEIGHT; y += 31) {
    display.drawLine(0, y, SCREEN_WIDTH, y, SSD1306_WHITE);
  }
}

void drawHeader() {
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setTextSize(1);
    display.setCursor(20,5);
    display.println(F("Temp"));

    display.setCursor(80,5);
    display.setTextSize(1);
    display.println(F("Umid"));
}

void loop() {
  drawBox();
  drawHeader();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.setCursor(10,15);
    display.setTextSize(3);
    display.println(F("ERRO"));
    return;
  }
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10,15);
    display.setTextSize(2);
    String hStr = String(h);
    display.print(t, 1);
    display.setCursor(70,15);
    String hStr = String(h);
    display.print(hStr.substring(0, 3));
    display.print(F("%"));
    display.display(); // Envia os dados para a tela
    delay(10000);
}
