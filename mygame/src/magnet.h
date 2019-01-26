#include "main.h"
#include "player.h"

#ifndef MAGNET_H;
#define MAGNET_H;

class Magnet {
public:
    Magnet() {}
    Magnet(int i);
    glm::vec3 position;
    float rotation, x, y;
    color_t color;
    void draw(glm::mat4 VP);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;    // How an object looks 
};

#endif // MAGNET_H