#define PI 3.14
#define SIDES 360

#include "power.h"
#include "main.h"


Power::Power(int type) {
    this->x = 30.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/2.0));
    this->y = 4.0;
    this->oy = y;
    this->type = type;
    if ( this->type == 1 ){
        this->radius = 0.3;
        this->color = COLOR_GREEN;
        this->rotation = 0;
        this->xspeed = -dpan - 0.01;
        this->yspeed = 0.016;
        this->yrange = 8;
    }
    else if ( this->type == 2 ){
        this->radius = 0.3;
        this->color = COLOR_RED;
        this->rotation = 0;
        this->xspeed = -dpan - 0.015;
        this->yspeed = 0.012;
        this->yrange = 8;
    }
    
    this->position = glm::vec3(x, y, 0);
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

void Power::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    //rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Power::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Power::tick() {
    this->position.x += this->xspeed;
    if ((this->position.y >= this->oy + this->yrange/2) ||( this->position.y <= this->oy - this->yrange/2 )){
        this->yspeed = -this->yspeed;
    }
    this->position.y += this->yspeed;
}

bounding_box_t Power::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->radius*2, this->radius*2};
    return bbox;
}
