#include "ground.h"
#include "main.h"

Ground::Ground(float x, float y,float width, float height, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->height = height;  
    this->width = width;
    this->speed = 0;
    GLfloat vertex_buffer_data[] = { 
        width/2, -height, 0.0f,
        width/2, 0 , 0.0f,
       -width/2, 0, 0.0f,

        width/2, -height, 0.0f,
       -width/2, 0, 0.0f,
       -width/2, -height, 0.0f 
        };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Ground::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ground::tick(){
    this->position.x -= speed;
}

void Ground::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Ground::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->width, this->height };
    return bbox;
}

