#include "../Engine/Component.h"

#pragma once

namespace CS230 {
	class Score : public CS230::Component {
	public:
		Score(int score);
		void Add(int value);
		int Value();
	private:
		int score;
	};
}