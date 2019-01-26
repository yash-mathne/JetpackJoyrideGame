#include "main.h"
#include "timer.h"
#include "player.h"
#include "ground.h"
#include "coin.h"
#include "timer.h"
#include "score.h"
#include "enemy.h"
#include "power.h"
#include "bullet.h"
#include "magnet.h"
#include <stdlib.h>



using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/


//objects
Ground ground1, ground2;
Player player1;
std::vector<Power> powers;
std::vector<Magnet> magnets;
std::vector<Coin> coins;
std::vector<Enemy> enemies;
std::vector<Bullet> bullets;
std::vector<Bullet> jets;
Score score;
// Enemy enemy1;
// Power power1;

float screen_zoom = 0.5, screen_center_x = 0, screen_center_y = 0, dpan = 0.018, swindow = 6;
float camera_rotation_angle = 0, px, py;
int coin_num = 6, enemy_num = 2, magnet_num = 1, power_num = 1;

bool up_pressed = false, motion = false, shot = false, fly = false, speedmod = false;

int test = 0, countb = 0, countj = 0, countp = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 0, 2, 12);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 2, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    //Matrices.view = glm::lookAt(glm::vec3(0, 2, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    player1.draw(VP);
    ground1.draw(VP);
    ground2.draw(VP);
    // enemy1.draw(VP);
    // for ( auto &coin: coins )
    //     if 
    for (int i = 0; i < powers.size(); ++i) {
        powers[i].draw(VP);
    }
    for (int i = 0; i < magnets.size(); ++i) {
        magnets[i].draw(VP);
    }
    for (int i = 0; i < coins.size(); ++i) {
        coins[i].draw(VP);
    }
    for (int i = 0; i < enemies.size(); ++i) {
        enemies[i].draw(VP);
    }
    for (int i = 0; i < bullets.size(); ++i) {
        bullets[i].draw(VP);
    }
    for (int i = 0; i < jets.size(); ++i) {
        jets[i].draw(VP);
    }

    // power1.draw(VP);
    score.draw(VP);
}

void tick_input(GLFWwindow *window) {
    glfwSetScrollCallback(window, scroll_callback);
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up    = glfwGetKey(window, GLFW_KEY_UP);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);

    if (left) {
        motion = true;
        if (player1.xdis > 0){
            player1.xdis -= 0.003;
            if (player1.position.x >= screen_center_x + swindow){
                player1.xdis = dpan - 0.003 - ( player1.position.x - screen_center_x - swindow);
            }
        }
        else{
            player1.xdis -= 0.0007;
        }
        if ( player1.position.x <= screen_center_x - swindow){
            player1.xdis = dpan + ( screen_center_x - swindow - player1.position.x );
        } 
    }
    else if (right) {
        motion = true;
        if (player1.xdis < 0){
            player1.xdis += 0.003;
            if (player1.position.x <= screen_center_x - swindow){
                player1.xdis = dpan + 0.003 + ( screen_center_x - swindow - player1.position.x );
            }
        }
        else{
            player1.xdis += 0.0007;    
        }
        if ( player1.position.x >= screen_center_x + swindow){
            player1.xdis = dpan - ( player1.position.x - screen_center_x - swindow);
        }
    }
    else {
        if (player1.position.x <= screen_center_x - swindow){
                player1.xdis = 0 + ( screen_center_x - swindow - player1.position.x );
            }
        else if (motion) {
            if (player1.xdis < 0) {
                player1.xdis += 0.003;
                if ( player1.xdis >= 0){
                    player1.xdis = 0;
                    motion = false;
                }
                if (player1.position.x <= screen_center_x - swindow){
                    player1.xdis = 0 + ( screen_center_x - swindow - player1.position.x );
                }
            }
            else if (player1.xdis > 0) {
                player1.xdis -= 0.003;
                if ( player1.xdis <= 0){
                    player1.xdis = 0;
                    motion = false;
                }
                if (player1.position.x >= screen_center_x + swindow){
                    player1.xdis = 0 - (  player1.position.x - screen_center_x - swindow );
                }
            }
        }
        if (player1.xdis == 0)
            player1.xdis = -dpan;
    }

    if (fly){
        if (countj++ >= 5){
            countj = 0;
            fly = false;
        }
    }

    if (up) {
        if(!fly){
            fly = true;
            jets.push_back(Bullet(player1.position.x, player1.position.y, 2));
        }
        if (player1.position.y < screen_center_y + 8.0)
            player1.ydis = +0.1;
        else
            player1.ydis = 0;
    }
    if (!up) {
        player1.ydis = -0.07;
        if ( player1.position.y < 0.03 )
            player1.ydis = -player1.position.y;
    }

    if (shot){
        if (countb++ >= 20){
            countb = 0;
            shot = false;
        }
    }

    if (space && !shot){
        shot = true;
        bullets.push_back(Bullet(player1.position.x, player1.position.y, 1));
    }

}


void tick_elements() {

    player1.tick();
    for(int i=0;i<magnets.size();++i){
        magnets[i].tick();
    }

    for(int i=0;i<powers.size();++i){
        powers[i].tick();
    }

    for (int i = 0; i < coins.size() ; ++i)
    {
        coins[i].tick();
    }
    for (int i = 0; i < enemies.size() ; ++i)
    {
        enemies[i].tick();
    }
    for (int i = 0; i < bullets.size() ; ++i)
    {
        bullets[i].tick();
    }
    for (int i = 0; i < jets.size() ; ++i)
    {
        jets[i].tick();
    }


    //======================================================================
    for (auto i = jets.begin(); i != jets.end(); ++i) { 
        if (i->position.y <= 0.07){
            jets.erase(i);
            i--;
        }
    }

    for (auto i = bullets.begin(); i != bullets.end(); ++i) { 
        if (i->position.y <= 0.2){
            bullets.erase(i);
            i--;
        }
        for (auto j = enemies.begin(); j != enemies.end(); ++j) {
            if (detect_collision(j->bounding_box(), i->bounding_box())){
                bullets.erase(i);
                enemies.erase(j);
                score.add(10);
                i--;
                j--;            
            }
        }
    }


    for (auto i = coins.begin(); i != coins.end(); ++i) { 
        if (i->position.x <= screen_center_x - 10.0){
            coins.erase(i);
            i--;
        }
        else if (detect_collision(player1.bounding_box(), i->bounding_box())){
            if ( i->type == 1)
                score.add(10);
            else
                score.add(20);
            coins.erase(i);
            i--;            
        }

    }

    for (auto i = enemies.begin(); i != enemies.end(); ++i) { 
        if (i->position.x <= screen_center_x - 10.0){
            enemies.erase(i);
            i--;
        }
        else if (detect_collision(player1.bounding_box(), i->bounding_box())){
            score.subtract(50);
            enemies.erase(i);
            i--;            
        }
    }

    if (speedmod){
        if (countp++ > 180)
            dpan = 0.018;
            speedmod = false;
    }

    for (auto i = powers.begin(); i != powers.end(); ++i) { 
        if (i->position.x <= screen_center_x - 10.0){
            powers.erase(i);
            i--;
        }
        else if (detect_collision(player1.bounding_box(), i->bounding_box())){
            if ( i->type == 1 && !speedmod){
                dpan += 0.02;
                speedmod = true;
                powers.erase(i);
                i--;
            }
            else if ( i->type == 2 && !speedmod){
                dpan -= 0.01;
                speedmod = true;
                powers.erase(i);
                i--;
            }
                        
        }
    }

    for (auto i = magnets.begin(); i != magnets.end(); ++i) { 
        if (i->position.x <= screen_center_x - 10.0){
            magnets.erase(i);
            i--;
        }
        else if (detect_collision(player1.bounding_box(), i->bounding_box())){
            if( player1.position.x > i->position.x)
                player1.xdis -= 0.02;
            else
                player1.xdis += 0.02;
            if( player1.position.y > i->position.y)
                player1.ydis -= 0.02;
            else
                player1.ydis += 0.02;
        }
    }

    //======================================================================

    for (int i=0; magnets.size()<magnet_num; i++) {
        magnets.push_back(Magnet(i));
    }
    if(!speedmod){
        for (int i=0; powers.size()<power_num; i++) {
            powers.push_back(Power((rand() % 2) + 1));
        }
    }
    for (int i=0; coins.size()<coin_num; i++) {
        coins.push_back(Coin( (rand() % 2) + 1, i ));
    }
    for (int i=0; enemies.size()<enemy_num; i++) {
        enemies.push_back(Enemy( (rand() % 4) + 1 , i));
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    player1       = Player(0, 0);
    ground1       = Ground(0,0,100,30,COLOR_BROWN);
    ground2       = Ground(0,12,100,3,COLOR_BROWN);

    score = Score();
    // power1 = Power(1.0,4.5,1);
    score.add(10);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 800;
    int height = 800;

   window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            
            tick_input(window);
            tick_elements();
            reset_screen();
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
