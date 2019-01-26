#include "magnet.h"
#include "main.h"

Magnet::Magnet(int i) {
    this->x = 15.0 + 3.0*i + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/2.0));
    this->y = 2.0 + 2.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(8.0 - 4.0)));
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->color = COLOR_RED;
    
    GLfloat vertex_buffer_data[] ={ 
        0.0 ,0.0 ,0.0 ,
        0.2 ,0.0 ,0.0 ,
        0.0 ,1.0 ,0.0 ,

        0.0 ,1.0 ,0.0 ,
        0.2 ,1.0 ,0.0 ,
        0.2 ,0.0 ,0.0 ,

        0.2 ,0.0 ,0.0 ,
        1.0 ,0.0 ,0.0 ,
        0.2 ,0.2 ,0.0 ,

        0.2 ,0.8 ,0.0 ,
        1.0 ,0.8 ,0.0 ,
        0.1 ,1.0 ,0.0 ,

        0.2 ,0.8 ,0.0 ,
        1.0 ,0.8 ,0.0 ,
        0.2 ,1.0 ,0.0 ,

        0.2 ,0.8 ,0.0 ,
        1.0 ,0.8 ,0.0 ,
        0.1 ,1.0 ,0.0 ,
    }; 

    this->object = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data, this->color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = glm::translate(glm::vec3(0, 0, 0)) * rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::tick(){
    this->position.x -= dpan;
}

bounding_box_t Magnet::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 3.0f, 3.0f };
    return bbox;
}