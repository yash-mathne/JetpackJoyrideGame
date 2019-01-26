#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player() {}
    Player(float x, float y );
    glm::vec3 position;
    float rotation;
    color_t color;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double xdis;
    double ydis;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // PLAYER_H
