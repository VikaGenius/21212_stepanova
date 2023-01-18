#include "score.h"

constexpr int kDefaultFactor = 100;

Score::Score() {
    score = 0;
}

int Score::CountOfScore(int countOfLines) {
    score += countOfLines * kDefaultFactor;
    return score;
}
