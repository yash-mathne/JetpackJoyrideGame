#include "main.h"

#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:
    Bullet() {}
    Bullet( float px, float py, int type);
    glm::vec3 position;
    int type;
    float x, y, radius;
    color_t color;
    void draw(glm::mat4 VP);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BULLET_H