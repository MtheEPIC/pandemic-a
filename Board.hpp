#pragma once
#include "City.hpp"
#include <iostream>
#include <unordered_map>

namespace pandemic {
	typedef std::unordered_map<City, int> M;
	class Board
	{
		M cities_pandemic_level;
	public:
		int& operator[](City);
		bool is_clean();
	};
	std::ostream& operator<<(std::ostream& os, const Board& dt);
	
}