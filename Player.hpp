#pragma once
#include <string>
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"

namespace pandemic {
	class Player
	{
	public:
		Player(Board, City);
		Player(Board, City, int);
		~Player();
		Player take_card(City);
		Player drive(City);
		Player fly_direct(City);
		Player treat(City);
		Player fly_charter(City);
		Player build();
		Player fly_shuttle(City);
		Player discover_cure(Color);
		std::string role();
	};
	std::ostream& operator<<(std::ostream& os, const Board& dt);
}