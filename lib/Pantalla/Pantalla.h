#pragma once
#include <Arduino.h>
#include <Tensor.h>

// Estructura Point
struct Point {
  uint8_t x;
  uint8_t y;
  Point(): x(0), y(0) {};
  Point(uint8_t x_, uint8_t y_): x(x_), y(y_) {};
  bool operator==(const Point& other) const {
    bool val_return = false;
    if(this->x == other.x && this->y == other.y) val_return = true;
    return val_return;
  }
};

namespace Pantalla {
  // Funciones de Traducción y Mapeo de Pines (segun esquema)
  const uint8_t ROWS = 8;
  const uint8_t COLUMNS = 8;
  const uint8_t pinVX = A6;
  const uint8_t pinVY = A5;
  const uint8_t pinSW = A7;
  uint8_t traductColumn(uint8_t column);
  uint8_t traductRow(uint8_t row);
  // Funciones de Prueba de Pines
  void pruebaTotal(unsigned long time);
  void pruebaIndividual(unsigned long time);
  // Funciones de Pantalla
  void clear();
  // Funcion de Prueba y Referencia, no optimo el graficado por puntos debido al bajo PWM
  void drawPoint(Point p, unsigned int time);
  // Funcion Graficadora de pantalla, recibe matriz ROWSxCOLUMNS de booleanos
  void drawPantalla(Tensor<Tensor<bool>>& pots, unsigned int time);
}
