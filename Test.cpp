#include "doctest.h"
#include "Board.hpp"
#include "City.hpp"
#include "OperationsExpert.hpp"
#include "Virologist.hpp"
#include "FieldDoctor.hpp"
#include "Medic.hpp"

using namespace pandemic;
using namespace std;

TEST_CASE("is_clean")
{
	Board game_board;
	CHECK_EQ(game_board.is_clean(), true);
	
	game_board[City::HongKong] = 1;
	CHECK_EQ(game_board.is_clean(), false);
	
	game_board[City::HongKong] = 0;
	CHECK_EQ(game_board.is_clean(), true);
	
	game_board[City::HongKong] = 1;
	game_board[City::Atlanta] = 1;
	game_board[City::HongKong] = 0;
	CHECK_EQ(game_board.is_clean(), false);
}

TEST_CASE("player-treat")
{
	Board game_board;
	OperationsExpert player {game_board, City::Atlanta};
	CHECK_EQ(game_board.is_clean(), true);
	
	// treat a city you're in
	game_board[City::Atlanta] = 1;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// treat a city you're in with high infection
	game_board[City::Atlanta] = 2;
	player.treat();
	CHECK_EQ(game_board.is_clean(), false);
	// treat a city you're next to
	game_board[City::Atlanta] = 0;
	game_board[City::Chicago] = 1;
	player.treat(City::HongKong);
	CHECK_EQ(game_board.is_clean(), false);
	// treat a city you're not it
	game_board[City::Chicago] = 0;
	game_board[City::HongKong] = 1;
	player.treat();
	CHECK_EQ(game_board.is_clean(), false);
	// move to an infected city
	game_board[City::HongKong] = 0;
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);
	CHECK_EQ(game_board.is_clean(), false);
	// ... treat it
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// try to go to a city (you can't reach) and treat it
	game_board[City::Chicago] = 0;
	game_board[City::HongKong] = 1;
	player.drive(City::HongKong);
	player.treat();
	CHECK_EQ(game_board.is_clean(), false);
}

TEST_CASE("Virologist-treat")
{
	Board game_board;
	Virologist player {game_board, City::Atlanta};
	
	// treat a city you're in
	game_board[City::Atlanta] = 1;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// treat a city you're in with high infection
	game_board[City::Atlanta] = 2;
	player.treat();
	CHECK_EQ(game_board.is_clean(), false);
	// treat a city you're next to
	game_board[City::Atlanta] = 0;
	game_board[City::Chicago] = 1;
	player.treat(City::HongKong);
	CHECK_EQ(game_board.is_clean(), true);
	// treat a city you're not in
	game_board[City::Chicago] = 0;
	game_board[City::HongKong] = 1;
	player.treat(City::HongKong);
	CHECK_EQ(game_board.is_clean(), true);
	// move to an infected city
	game_board[City::HongKong] = 0;
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);
	CHECK_EQ(game_board.is_clean(), false);
	// ... treat it
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// try to go to a city (you can't reach) and treat it
	game_board[City::Chicago] = 0;
	game_board[City::HongKong] = 1;
	player.drive(City::HongKong);
	player.treat();
	CHECK_EQ(game_board.is_clean(), false);
}

TEST_CASE("FieldDoctor-treat")
{
	Board game_board;
	FieldDoctor player {game_board, City::Atlanta};
	
	// treat a city you're in
	game_board[City::Atlanta] = 1;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// treat a city you're in with high infection
	game_board[City::Atlanta] = 2;
	player.treat();
	CHECK_EQ(game_board.is_clean(), false);
	// treat a city you're next to
	game_board[City::Atlanta] = 0;
	game_board[City::Chicago] = 1;
	player.treat(City::HongKong);
	CHECK_EQ(game_board.is_clean(), true);
	// treat a city you're not in
	game_board[City::Chicago] = 0;
	game_board[City::HongKong] = 1;
	player.treat(City::HongKong);
	CHECK_EQ(game_board.is_clean(), false);
	// move to an infected city
	game_board[City::HongKong] = 0;
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);
	CHECK_EQ(game_board.is_clean(), false);
	// ... treat it
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// try to go to a city (you can't reach) and treat it
	game_board[City::Chicago] = 0;
	game_board[City::HongKong] = 1;
	player.drive(City::HongKong);
	player.treat();
	CHECK_EQ(game_board.is_clean(), false);
}

TEST_CASE("Medic-treat")
{
	Board game_board;
	Medic player {game_board, City::Atlanta};
	
	// treat a city you're in
	game_board[City::Atlanta] = 1;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// treat a city you're in with high infection
	game_board[City::Atlanta] = 2;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// treat a city you're next to
	game_board[City::Atlanta] = 0;
	game_board[City::Chicago] = 1;
	player.treat(City::HongKong);
	CHECK_EQ(game_board.is_clean(), false);
	// treat a city you're not in
	game_board[City::Chicago] = 0;
	game_board[City::HongKong] = 1;
	player.treat(City::HongKong);
	CHECK_EQ(game_board.is_clean(), false);
	// move to an infected city
	game_board[City::HongKong] = 0;
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);
	CHECK_EQ(game_board.is_clean(), false);
	// ... treat it
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// try to go to a city (you can't reach) and treat it
	game_board[City::Chicago] = 0;
	game_board[City::HongKong] = 1;
	player.drive(City::HongKong);
	player.treat();
	CHECK_EQ(game_board.is_clean(), false);
}

TEST_CASE("player-treat-cure")
{
	Board game_board;
	OperationsExpert player {game_board, City::Atlanta};
	player.take_card(City::Atlanta).take_card(City::Washinton).take_card(City::NewYork).take_card(City::Chicago).take_card(City::Montreal);
	player.discover_cure();
	
	// treat a city you're in
	game_board[City::Atlanta] = 1;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
	// treat a city you're in with high infection
	game_board[City::Atlanta] = 2;
	player.treat();
	CHECK_EQ(game_board.is_clean(), true);
}

TEST_CASE("Medic-treat-cure")
{
	Board game_board;
	Medic player {game_board, City::Atlanta};
	player.take_card(City::Atlanta).take_card(City::Washinton).take_card(City::NewYork).take_card(City::Chicago).take_card(City::Montreal);
	
	// move to an infected city
	game_board[City::HongKong] = 0;
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);
	CHECK_EQ(game_board.is_clean(), true);
	// ... treat it
	game_board[City::Chicago] = 1;
	player.drive(City::Chicago);;
	CHECK_THROWS(player.treat());
}