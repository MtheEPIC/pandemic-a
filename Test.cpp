#include "doctest.h"
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "OperationsExpert.hpp"
#include "Virologist.hpp"
#include "FieldDoctor.hpp"
#include "Medic.hpp"
#include "Scientist.hpp"
#include "GeneSplicer.hpp"

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

TEST_CASE("player-discover_cure")
{
	Board game_board;
	OperationsExpert player {game_board, City::Atlanta};
	
	// try to discover a cure with 4 cards
	player.take_card(City::Atlanta).take_card(City::Washington).take_card(City::NewYork).take_card(City::Chicago);
	CHECK_THROWS(player.discover_cure(Color::Blue));
	// try to discover a cure with 5 cards of different colors
	player.take_card(City::HongKong);
	CHECK_THROWS(player.discover_cure(Color::Blue));
	// try to discover a cure with 5 cards of the same color
	player.take_card(City::Montreal);
	CHECK_NOTHROW(player.discover_cure(Color::Blue));
	// check if player gave the cards back
	CHECK_EQ(game_board.cities_pandemic_level.size(), 1);
	// try to discover a cure twice
	player.take_card(City::Atlanta).take_card(City::Washington).take_card(City::NewYork).take_card(City::Chicago).take_card(City::Montreal);
	CHECK_NOTHROW(player.discover_cure(Color::Blue)); // keep the cards in hand
	CHECK_EQ(game_board.cities_pandemic_level.size(), 6);
}

TEST_CASE("Scientist-discover_cure")
{
	Board game_board;
	Scientist player {game_board, City::Atlanta, 4};
	
	// try to discover a cure with 3 cards
	player.take_card(City::Atlanta).take_card(City::Washington).take_card(City::NewYork);
	CHECK_THROWS(player.discover_cure(Color::Blue));
	// try to discover a cure with 4 cards of different colors
	player.take_card(City::HongKong);
	CHECK_THROWS(player.discover_cure(Color::Blue));
	// try to discover a cure with 4 cards of the same color
	player.take_card(City::Montreal);
	CHECK_NOTHROW(player.discover_cure(Color::Blue));
	// check if player gave the cards back
	CHECK_EQ(game_board.cities_pandemic_level.size(), 1);
	// try to discover a cure twice
	player.take_card(City::Atlanta).take_card(City::Washington).take_card(City::NewYork).take_card(City::Montreal);
	CHECK_NOTHROW(player.discover_cure(Color::Blue)); // keep the cards in hand
	CHECK_EQ(game_board.cities_pandemic_level.size(), 5);
}

TEST_CASE("GeneSplicer-discover_cure")
{
	Board game_board;
	OperationsExpert player {game_board, City::Atlanta};
	
	// try to discover a cure with 4 cards
	player.take_card(City::Atlanta).take_card(City::Washington).take_card(City::NewYork).take_card(City::Chicago);
	CHECK_THROWS(player.discover_cure(Color::Blue));
	// try to discover a cure with 5 cards of different colors
	player.take_card(City::HongKong);
	CHECK_NOTHROW(player.discover_cure(Color::Blue));
	// check if player gave the cards back
	CHECK_EQ(game_board.cities_pandemic_level.size(), 0);
	// try to discover a cure twice
	player.take_card(City::Atlanta).take_card(City::Washington).take_card(City::NewYork).take_card(City::Chicago).take_card(City::Montreal);
	CHECK_NOTHROW(player.discover_cure(Color::Blue)); // keep the cards in hand
	CHECK_EQ(game_board.cities_pandemic_level.size(), 5);
}
TEST_CASE("player-treat-cure")
{
	Board game_board;
	OperationsExpert player {game_board, City::Atlanta};
	player.take_card(City::Atlanta).take_card(City::Washington).take_card(City::NewYork).take_card(City::Chicago).take_card(City::Montreal);
	player.discover_cure(Color::Blue);
	
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
	player.take_card(City::Atlanta).take_card(City::Washington).take_card(City::NewYork).take_card(City::Chicago).take_card(City::Montreal);
	player.discover_cure(Color::Blue);
	
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