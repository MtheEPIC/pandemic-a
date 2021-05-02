#pragma once
#include "Player.hpp"

namespace pandemic {
	// typedef unsigned int UI;
	class OperationsExpert : public Player
	{
	public:
		OperationsExpert(Board, City);
	};
}