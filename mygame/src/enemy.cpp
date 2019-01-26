#include "enemy.h"
#include "main.h"



Enemy::Enemy(int type, int i ) {
    this->type = type;
    this->height = 0.5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/3.0));
    this->x = 10.0 + 3.0*i + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/2.0));
    this->y = this->height + 2.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(8.0 - 4.0 - this->height)));
    this->width = 0.2;
    this->rotation = 0;
    this->up = true;
    this->speed = 0;
    this->range = 0;
    this->color = COLOR_RED;
    if (this->type == 2){
        this->range = 2.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(8.0 - 3.0 ))); 
    }
    else{
        this->height = 0.2; 
        this->x = 10.0 + 3.0*i + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/6.0));
        this->y = 2.5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(8.0 - 5.0)));
        this->width = 2.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/3.0));
        if (this->type == 4){
             this->range = 2.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(8.0 - 3.0 )));
        }
    }
    this->position = glm::vec3(this->x, this->y, 0);
    GLfloat vertex_buffer_data [] = {
        -width/2, -height/2, 0.0f,
         width/2, -height/2, 0.0f,
        -width/2,  height/2, 0.0f,

         width/2,  height/2, 0.0f,
         width/2, -height/2, 0.0f,
        -width/2,  height/2, 0.0f
    };

    GLfloat vertex_buffer_data_end [] = {
        -width/2, -height/2       , 0.1f,
         width/2, -height/2       , 0.1f,
            0   , -height/2 - 0.1 , 0.1f,

        -width/2,  height/2       , 0.1f,
         width/2,  height/2       , 0.1f,
         0      ,  height/2 + 0.1 , 0.1f
    };
    
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, this->color, GL_FILL);
    this->ends   = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data_end, COLOR_BLACK, GL_FILL);

}

void Enemy::draw(glm::mat4 VP) {
    if (!this->object) return;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 rotate = glm::rotate(this->rotation, glm::vec3(0,0,1));
    glm::mat4 translate = glm::translate (this->position);        // glTranslatef
    Matrices.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->ends);

}

void Enemy::tick() {
    if (this->range != 0){
        if((this->position.y + this->height/2 >= this->y + range/2)||(this->position.y + this->height/2 >= 8.0))
            this->up = false;
        else if ((this->position.y - this->height/2 <= this->y - range/2)||(this->position.y - this->height/2 <= 0.0))
            this->up = true;
        if (this->up == true)
            this->position.y += 0.015;
        else
            this->position.y -= 0.015;
    }
    this->position.x -= dpan;
}

bounding_box_t Enemy::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->width, this->height};
    return bbox;
}

