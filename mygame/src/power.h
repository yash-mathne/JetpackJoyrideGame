#include "main.h"

#ifndef POWER_H
#define POWER_H

class Power {
public:
    Power() {}
    Power(int type);
    glm::vec3 position;
    color_t color; 
    int type;
    float rotation, xspeed, yspeed, radius, yrange, oy, x, y;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // POWER_H