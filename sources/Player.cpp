//*Nothing here works.
#include "Player.hpp"
#include "Board.hpp"
#include <stdexcept>
using namespace std;
namespace pandemic {

//*Implementation of output stream operator for Player class .
ostream &operator<<(ostream &os, const Player &player) {
  os << "Cards :\n_____________________________________\n" << endl;
  for (const auto &city : player.cards) {
    os << Board::toString(city) << endl;
  }
  os<<"\n"<<endl;
  os << "Location :\n_____________________________________\n" << endl;
  os << Board::toString(player.currentLoc) << endl;
  os<<"\n"<<endl;
  return os;
}

//*Boolean method that tells if the player has a card of a specific city .
bool Player::hasCard(City city) { return (cards.count(city) != 0); }


//*Implemenation of a standart player interface methods.


Player &Player::drive(City city) {
  if (currentLoc == city) {
    throw invalid_argument{"You cant move from the city to itself ."};
  }
  if (!board.isConnected(currentLoc, city)) {
    throw invalid_argument{"Those cities are not connected."};
  }
  move(city);
  return *this;
}


Player &Player::fly_direct(City city) {
  if (currentLoc == city) {
    throw invalid_argument{"You cant move from the city to itself ."};
  }
  if (!hasCard(city)) {
    throw invalid_argument{"You dont have the card of " +
                           Board::toString(city) + "."};
  }
  cards.erase(city);
  move(city);
  return *this;
}

Player &Player::fly_charter(City city) {
  if (currentLoc == city) {
    throw invalid_argument{"You cant move from the city to itself ."};
  }
  if (!hasCard(currentLoc)) {
    throw invalid_argument{"You dont have the " + Board::toString(currentLoc) +
                           " card (the card of the city you are in) ."};
  }
  cards.erase(currentLoc);
  move(city);
  return *this;
}
Player &Player::fly_shuttle(City city) {
  if (currentLoc == city) {
    throw invalid_argument{"You cant move from the city to itself ."};
  }
  if (!board.labExists(currentLoc)) {
    throw invalid_argument{"There is no research station in " +
                           Board::toString(currentLoc) + "."};
  }
  if (!board.labExists(city)) {
    throw invalid_argument{"There is no research station in " +
                           Board::toString(city) + "."};
  }
  move(city);
  return *this;
}
Player &Player::build() {
  if (!hasCard(currentLoc)) {
    throw invalid_argument{"You dont have a card for " +
                           Board::toString(currentLoc) + "."};
  }
  cards.erase(currentLoc);
  board.makeLab(currentLoc);
  return *this;
}
Player &Player::discover_cure(Color color) {
  if (!board.labExists(currentLoc)) {
    throw invalid_argument{"There is no research station in " +
                           Board::toString(currentLoc) + "."};
  }
  int nOc = numOfCards(color);
  const int PAYMENT_FOR_FINDING_THE_TREAT = 5;
  if (nOc < PAYMENT_FOR_FINDING_THE_TREAT) {
    throw invalid_argument{"You have only " + to_string(nOc) +
                           " cards remaining ."};
  }
  discard(color, PAYMENT_FOR_FINDING_THE_TREAT);
  board.addCure(color);
  return *this;
}
Player &Player::treat(City city) {
  if (currentLoc != city) {
    throw invalid_argument{"To treat you need to be located at " +
                           Board::toString(city) + "."};
  }
  if (board[city] == 0) {
    throw invalid_argument{"No more cubes remain in " + Board::toString(city) +
                           " ."};
  }
  if (cureExist(city)) {
    useCure(city);
  } else {
    board[city] -= 1;
  }
  return *this;
}
Player &Player::take_card(City city) {
  cards.insert(city);
  return *this;
}
string Player::role() { return ""; }
Player &Player::remove_cards() {
  cards.clear();
  return *this;
}
//*Returns number of cards a player hold with specific color .
int Player::numOfCards(Color color) {
  int counter = 0;
  for (const auto &city : cards) {
    if (board.colorOf(city) == color) {
      counter++;
    }
  }
  return counter;
}

//*Helping method which takes out specific amount of cards with specific color.
void Player::discard(Color color, int amount) {
  set<City> clearList;
  for (const auto &city : cards) {
    if (board.colorOf(city) == color) {
      clearList.insert(city);
    }
  }
  for (const auto &city : clearList) {
    if (amount > 0) {
      cards.erase(city);
      amount -= 1;
    } else {
      return;
    }
  }
}
//*Boolean method which tells if a cure exist for given city.
bool Player::cureExist(City city) {
  return (board.getCureArray().at(board.colorOf(city)) > 0);
}
//*Using cure nullifies the number of infection cubes in specific city.
void Player::useCure(City city) { board[city] = 0; }

//*Intuitive implementation, basically exist for manipulation through inheritance .
void Player::move(City city) { currentLoc = city; }
} // namespace pandemic









