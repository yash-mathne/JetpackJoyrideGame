#include "main.h"


#ifndef GROUND_H
#define GROUND_H


class Ground {
public:
    Ground() {}
    Ground(float x, float y,float width,float height, color_t color);
    glm::vec3 position;
    float speed;
    float rotation;
    float width;
    float height;
    void draw(glm::mat4 VP);
    void tick();
    void set_position(float x, float y);
    bounding_box_t bounding_box();
private:
    VAO *object;    // How an object looks 
};

#endif