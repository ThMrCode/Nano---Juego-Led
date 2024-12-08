#include <Pantalla.h>

// Funciones de Traducción y Mapeo de Pines (segun esquema)
uint8_t Pantalla::traductColumn(uint8_t column) {
  return column+2;
}
uint8_t Pantalla::traductRow(uint8_t row) {
  switch (row) {
    case 0:
      return 10;
      break; 
    case 1:
      return A0;
      break; 
    case 2:
      return A2;
      break; 
    case 3:
      return 11;
      break; 
    case 4:
      return A1;
      break; 
    case 5:
      return 12;
      break; 
    case 6:
      return A3;
      break; 
    case 7:
      return A4;
      break; 
    default:
      return 13;
      break;
  }
}

// Funciones de Prueba de Pines
void Pantalla::pruebaTotal(unsigned long time) {
  Pantalla::clear();
  delay(time);
  for (uint8_t row = 0; row < Pantalla::ROWS; row++) {
    digitalWrite(Pantalla::traductRow(row),HIGH);
  }
  for (uint8_t column = 0; column < Pantalla::COLUMNS; column++) {
    digitalWrite(Pantalla::traductColumn(column), LOW);
  }
  delay(time);
  Pantalla::clear();
}
void Pantalla::pruebaIndividual(unsigned long time) {
  for (uint8_t column = 0; column < Pantalla::COLUMNS; column++) {
    digitalWrite(Pantalla::traductColumn(column), LOW);
    for (uint8_t row = 0; row < Pantalla::ROWS; row++) {
      pinMode(Pantalla::traductRow(row), OUTPUT);
      digitalWrite(Pantalla::traductRow(row), HIGH);
      delay(time);
      digitalWrite(Pantalla::traductRow(row), LOW);
      delay(time);
    }
    digitalWrite(Pantalla::traductColumn(column), HIGH);
  }
}

// Funciones de Pantalla
void Pantalla::clear() {
  for (uint8_t row = 0; row < Pantalla::ROWS; row++) {
    digitalWrite(Pantalla::traductRow(row),LOW);
  }
  for (uint8_t column = 0; column < Pantalla::COLUMNS; column++) {
    digitalWrite(Pantalla::traductColumn(column), HIGH);
  }
};
void Pantalla::drawPoint(Point p, unsigned int time) {
  digitalWrite(Pantalla::traductColumn(p.x),LOW);
  digitalWrite(Pantalla::traductRow(p.y),HIGH);
  delayMicroseconds(time);
  digitalWrite(Pantalla::traductColumn(p.x),HIGH);
  digitalWrite(Pantalla::traductRow(p.y),LOW);
}
void Pantalla::drawPantalla(Tensor<Tensor<bool>>& pots, unsigned int time)
{
  for (uint8_t row = 0; row < Pantalla::ROWS; row++)
  {
    digitalWrite(Pantalla::traductRow(row),HIGH);
    for (uint8_t column = 0; column < Pantalla::COLUMNS; column++)
    {
      if(pots[column][row]) digitalWrite(Pantalla::traductColumn(column),LOW);
    }
    delayMicroseconds(time);
    for (uint8_t column = 0; column < Pantalla::COLUMNS; column++)
    {
      if(pots[column][row]) digitalWrite(Pantalla::traductColumn(column),HIGH);
    }
    digitalWrite(Pantalla::traductRow(row),LOW);
  }
}

