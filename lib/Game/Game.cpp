#include "Game.h"

Game::Snake::Snake(uint8_t x, uint8_t y, uint8_t direction_)
{
    this->direction = direction_;
    this->pots.push(Point(x,y));
}

Point Game::Snake::getNewPot()
{
    uint8_t new_x = pots[pots.size()-1].x;
    uint8_t new_y = pots[pots.size()-1].y;
    switch (this->direction)
    {
        case UP:
            if(new_y == (Pantalla::ROWS - 1)) new_y = 0;
            else new_y += 1;
            break;
        case LEFT:
            if(new_x == 0) new_x = (Pantalla::COLUMNS - 1);
            else new_x -= 1;
            break;
        break;
        case BOTTOM:
            if(new_y == 0) new_y = (Pantalla::ROWS - 1);
            else new_y -= 1;
            break;
        case RIGHT:
            if(new_x == (Pantalla::COLUMNS - 1)) new_x = 0;
            else new_x += 1;
            break;
        default:
        break;
    }
  return Point(new_x,new_y);
}

void Game::Snake::move(Point newPot, bool keepDims)
{
    this->pots.push(newPot);
    if(keepDims == false) this->pots.pop(0);
}

Game::Controler::Controler(): snake(3,1,0), manzana(5,5)
{
  Tensor<bool> columnEx;
  columnEx.resize_value(Pantalla::ROWS,false);
  this->pots.resize_value(Pantalla::COLUMNS,columnEx);
}

void Game::Controler::generateManzana()
{
    /*
    // Los pots libres descontando los de la serpiente son Rows*Columns - snake.pots.size
    int libres = (Pantalla::ROWS * Pantalla::COLUMNS) - this->snake.pots.size();
    uint8_t n_rand = rand() % libres;
    uint8_t counter = 0;
    for (uint8_t i = 0; i < Pantalla::ROWS; i++)
    {
        for (uint8_t j = 0; j < Pantalla::COLUMNS; j++)
        {
            if(!this->pots[j][i]) counter++;
            if(counter == n_rand) this->manzana
        }
    }*/
}

bool Game::Controler::move()
{
    // de momento solo movida
    Point newPot = this->snake.getNewPot();
    bool keepDims;
    // Verificar si ha chocado con su cola
    if(this->snake.pots.indexOf(newPot) != -1) this->life = false;
    else {
        // Verificar si se ha comido una manzana
        keepDims = (newPot == manzana);
        if(keepDims) {
            this->score ++;
            this->pots[this->manzana.x][this->manzana.y] = false;
        }
        // Eliminar el pot anterior de la pantalla POTS si no hay keepDims
        else this->pots[this->snake.pots[0].x][this->snake.pots[0].y] = false;
        // Snake Move con el valor de keepDims
        this->snake.move(newPot, keepDims);
    }
    return keepDims;
}

void Game::Controler::read()
{
    // No te permite ir en tu misma direccion en contra porque te comerias
    int middle = 527;
    int minToChange = 400;
    int vx = analogRead(Pantalla::pinVX);
    int vxAbs = abs(vx - middle);
    int vy = analogRead(Pantalla::pinVY);
    int vyAbs = abs(vy - middle);
    // Solo acepta un cambio por vez
    if(vxAbs > vyAbs) {
        // Preguntar cambio en X
        if(vxAbs > minToChange) {
            if (vx < middle) {
                if(this->snake.direction != Game::RIGHT) this->snake.direction = Game::LEFT;
            }
            else {
                if(this->snake.direction != Game::LEFT) this->snake.direction = Game::RIGHT;
            }
        }
    }
    else {
        // Preguntar cambio en Y
        if(vyAbs > minToChange) {
            if(vy < middle) {
                if(this->snake.direction != Game::UP) this->snake.direction = Game::BOTTOM;
            }
            else {
                if(this->snake.direction != Game::BOTTOM) this->snake.direction = Game::UP;
            }
        }
    }

}

void Game::Controler::frame()
{
    uint8_t n = this->snake.pots.size();
    for (uint8_t i = 0; i < n; i++)
    {
        this->pots[this->snake.pots[i].x][this->snake.pots[i].y] = true;
    }
    this->pots[this->manzana.x][this->manzana.y] = true;
}

void Game::Controler::loop()
{
    if(this->life) {
        if(this->cycle % 16 == 0) this->move();
        this->read();
        this->frame();
        Pantalla::drawPantalla(this->pots,this->time);
        this->cycle++;
    }
    else {
        // Mostrar Score
        if(score != 0) {
            //Cuantificar el Score en la pantalla porque recien ha muerto
            Tensor<bool> columnEx;
            columnEx.resize_value(Pantalla::ROWS,false);
            this->pots.resize_value(Pantalla::COLUMNS,columnEx);
            // Traducir a ultima fila columna
            for (uint8_t i = 0; i < Pantalla::ROWS; i++)
            {
                for (uint8_t j = 0; j < Pantalla::COLUMNS; j++)
                {
                    if((i*8 + j) < score) this->pots[j][i] = true;
                }
            }
            this->score = 0;
        }
        else  Pantalla::drawPantalla(this->pots, this->time);
    }
}
