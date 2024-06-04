#include "Score.h"

CS230::Score::Score(int score)
	:score(score)
{ }

void CS230::Score::Add(int value) {
	score += value;
}

int CS230::Score::Value() {
	return score;
}