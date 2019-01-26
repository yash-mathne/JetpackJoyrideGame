#include "main.h"

#ifndef COIN_H
#define COIN_H

class Coin {
public:
    Coin() {}
    Coin(int type, int k);
    glm::vec3 position;
    float rotation, x, y;
    color_t color;
    int type;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double xspeed, yspeed, radius;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // COIN_H