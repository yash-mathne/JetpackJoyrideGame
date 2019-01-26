#define PI 3.14
#define SIDES 360

#include "coin.h"
#include "main.h"


Coin::Coin(int type, int k) {
    if ( type == 1 ){
        this->color = COLOR_YELLOW;
        this->radius = 0.3;
    }
    if ( type == 2 ){
        this->color = COLOR_MAGENTA;
        this->radius = 0.4;
    }
    this->x = 8.0 + k*0.5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/6.0)),
    this->y = 1.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/7.0)),
    this->position = glm::vec3(this->x, this->y, 0);
    this->rotation = 1;
    this->xspeed = 0;
    this->yspeed = 0;
    this->type = type;
    static GLfloat vertex_buffer_data[10000] = { 0 };

    // Set the number of sides of the polygon here
    const float sides = SIDES;

    // Initialize loop variables
    float i = 0;
    int j = 0;

    // Dynamically populate the vertex data for each triangle
    for (; i <= 360; i += (360.0f / sides), j += 9) {
        vertex_buffer_data[j]     = 0;
        vertex_buffer_data[j + 1] = 0;
        vertex_buffer_data[j + 2] = 0;

        vertex_buffer_data[j + 3] = this->radius * cos (i * PI / 180);
        vertex_buffer_data[j + 4] = this->radius * sin (i * PI / 180);
        vertex_buffer_data[j + 5] = 0;

        vertex_buffer_data[j + 6] = this->radius * cos ((i + 360.0f / sides) * PI / 180);
        vertex_buffer_data[j + 7] = this->radius * sin ((i + 360.0f / sides) * PI / 180);
        vertex_buffer_data[j + 8] = 0;
    }

    this->object = create3DObject(GL_TRIANGLES, (3 * (sides + 1)), vertex_buffer_data, color, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    //rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


void Coin::tick() {
    this->position.x -= dpan;
    this->rotation += 1.5;
}

bounding_box_t Coin::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->radius*2, this->radius*2};
    return bbox;
}
