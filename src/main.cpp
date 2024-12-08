#include <Game.h>
#include <time.h>

// 32kb
// 2 kb

Game::Controler controler;


void setup() {
  for (uint8_t row = 0; row < 8; row++) {
    pinMode(Pantalla::traductRow(row), OUTPUT);
  }
  for (uint8_t column = 0; column < 8; column++) {
    pinMode(Pantalla::traductColumn(column), OUTPUT);
  }
  pinMode(Pantalla::pinVX, INPUT);
  pinMode(Pantalla::pinVY, INPUT);
  pinMode(Pantalla::pinSW, INPUT);
  Pantalla::clear();
  srand(controler.cycle);
}

void loop() {
  controler.loop();
}
