#include "score.h"
#include "main.h"
#include <cstring>

Score::Score()
{
    score = 0;
    digslen = 0;
}

void Score::update(int score) {
    this->score = score;
    char scorestr[50];
    sprintf(scorestr, "%d", score);
    digslen = strlen(scorestr);
    for (int i = digslen - 1; i >= 0; i--) {
        digs[i] = Digit(scorestr[i], screen_center_x + 7 - 0.6*(digslen - i), -4.8);
    }
}

void Score::add(int d) {
    score += d;
}

int Score::get() {
    return this->score;
}

void Score::subtract(int d) {
    score -= d;
}
void Score::draw(glm::mat4 VP) {
    update(score);
    for (int i = 0; i < digslen; i++) digs[i].draw(VP);
}
