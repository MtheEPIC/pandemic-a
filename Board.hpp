#pragma once
#include "City.hpp"
#include <iostream>

namespace pandemic {
	class Board
	{
	public:
		Board operator[](City);
		Board operator=(int);
		bool is_clean();
	};
	std::ostream& operator<<(std::ostream& os, const Board& dt);
}