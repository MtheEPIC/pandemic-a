#pragma once
#include "City.hpp"
#include "Color.hpp"
#include "Board.hpp"

namespace pandemic {
	// typedef unsigned int UI;
	class OperationsExpert
	{
	public:
		OperationsExpert(Board, City);
		void take_card(City);
		void build();
		void drive(City);
		void fly_direct(City);
		void treat(City);
		void fly_charter(City);
		void fly_shuttle(City);
		void discover_cure(Color);
		// Board() : Board(ROWS_INIT, COLS_INIT) {}
		// Board(CUI, CUI);
		// ~Board();
		// void post(CUI, CUI, CDir, sref);
		// std::string read(CUI, CUI, CDir, CUI);
		/*void after tests*/ std::string show();
		
		
		// inline void set_rows(UI rows) {this->_ROWS = rows;}
	};
}