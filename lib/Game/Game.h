#include <Pantalla.h>

namespace Game {
    enum {
        UP = uint8_t(0),
        LEFT = uint8_t(1),
        BOTTOM = uint8_t(2),
        RIGHT = uint8_t(3),
    };

    class Snake {
    // Siempre el ultimo pot es la cabeza
    // Nunca se mueven realmente los otros pots, solo se elimina el ultimo y se agrega uno al final
    public:
        Tensor<Point> pots;
        uint8_t direction;
        Snake(uint8_t x, uint8_t y, uint8_t direction_);
        ~Snake() {};
        Point getNewPot();
        void move(Point newPot, bool keepDims);
    };

    class Controler {
    public:
        Snake snake;
        Tensor<Tensor<bool>> pots;
        Point manzana;
        bool life = true;
        uint8_t score = 0;
        unsigned int time = 1000;
        long long cycle = 0;
        Controler();
        void generateManzana();
        bool move();
        void read();
        void frame();
        void loop();
    };
}