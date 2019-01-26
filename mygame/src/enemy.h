#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:
    Enemy() {}
    Enemy(int type, int i);
    bool up;
    int type;
    color_t color;
    float x, y, rotation, range, height, width, speed;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO* object;
    VAO* ends;
};

#endif // ENEMY_H

