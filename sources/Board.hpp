#pragma once
#include "City.hpp"
#include "Color.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
using namespace std;
namespace pandemic {
class Board {
  class Location {
  public:
    set<City> connections;
    bool laboratoryEx;
    Color color;
    int numOfCubes;
    Location() {}
    Location(Color color, set<City> connections)
        : color{color}, connections{move(connections)} {
      laboratoryEx = false;
      numOfCubes = 0;
    }
  };
  map<City, Location> loc{
      {Algiers, {Black, {Madrid, Paris, Istanbul, Cairo}}},
      {Atlanta, {Blue, {Chicago, Miami, Washington}}},
      {Baghdad, {Black, {Tehran, Istanbul, Cairo, Riyadh, Karachi}}},
      {Bangkok, {Red, {Kolkata, Chennai, Jakarta, HoChiMinhCity, HongKong}}},
      {Beijing, {Red, {Shanghai, Seoul}}},
      {Bogota, {Yellow, {MexicoCity, Lima, Miami, SaoPaulo, BuenosAires}}},
      {BuenosAires, {Yellow, {Bogota, SaoPaulo}}},
      {Cairo, {Black, {Algiers, Istanbul, Baghdad, Khartoum, Riyadh}}},
      {Chennai, {Black, {Mumbai, Delhi, Kolkata, Bangkok, Jakarta}}},
      {Chicago,
       {Blue, {SanFrancisco, LosAngeles, MexicoCity, Atlanta, Montreal}}},
      {Delhi, {Black, {Tehran, Karachi, Mumbai, Chennai, Kolkata}}},
      {Essen, {Blue, {London, Paris, Milan, StPetersburg}}},
      {HoChiMinhCity, {Red, {Jakarta, Bangkok, HongKong, Manila}}},
      {HongKong,
       {Red, {Bangkok, Kolkata, HoChiMinhCity, Shanghai, Manila, Taipei}}},
      {Istanbul,
       {Black, {Milan, Algiers, StPetersburg, Cairo, Baghdad, Moscow}}},
      {Jakarta, {Red, {Chennai, Bangkok, HoChiMinhCity, Sydney}}},
      {Johannesburg, {Yellow, {Kinshasa, Khartoum}}},
      {Karachi, {Black, {Tehran, Baghdad, Riyadh, Mumbai, Delhi}}},
      {Khartoum, {Yellow, {Cairo, Lagos, Kinshasa, Johannesburg}}},
      {Kinshasa, {Yellow, {Lagos, Khartoum, Johannesburg}}},
      {Kolkata, {Black, {Delhi, Chennai, Bangkok, HongKong}}},
      {Lagos, {Yellow, {SaoPaulo, Khartoum, Kinshasa}}},
      {Lima, {Yellow, {MexicoCity, Bogota, Santiago}}},
      {London, {Blue, {NewYork, Madrid, Essen, Paris}}},
      {LosAngeles, {Yellow, {SanFrancisco, Chicago, MexicoCity, Sydney}}},
      {Madrid, {Blue, {London, NewYork, Paris, SaoPaulo, Algiers}}},
      {Manila, {Red, {Taipei, SanFrancisco, HoChiMinhCity, Sydney, HongKong}}},
      {MexicoCity, {Yellow, {LosAngeles, Chicago, Miami, Lima, Bogota}}},
      {Miami, {Yellow, {Atlanta, MexicoCity, Washington, Bogota}}},
      {Milan, {Blue, {Essen, Paris, Istanbul}}},
      {Montreal, {Blue, {Chicago, Washington, NewYork}}},
      {Moscow, {Black, {StPetersburg, Istanbul, Tehran}}},
      {Mumbai, {Black, {Karachi, Delhi, Chennai}}},
      {NewYork, {Blue, {Montreal, Washington, London, Madrid}}},
      {Osaka, {Red, {Taipei, Tokyo}}},
      {Paris, {Blue, {Algiers, Essen, Madrid, Milan, London}}},
      {Riyadh, {Black, {Baghdad, Cairo, Karachi}}},
      {SanFrancisco, {Blue, {LosAngeles, Chicago, Tokyo, Manila}}},
      {Santiago, {Yellow, {Lima}}},
      {SaoPaulo, {Yellow, {Bogota, BuenosAires, Lagos, Madrid}}},
      {Seoul, {Red, {Beijing, Shanghai, Tokyo}}},
      {Shanghai, {Red, {Beijing, HongKong, Taipei, Seoul, Tokyo}}},
      {StPetersburg, {Blue, {Essen, Istanbul, Moscow}}},
      {Sydney, {Red, {Jakarta, Manila, LosAngeles}}},
      {Taipei, {Red, {Shanghai, HongKong, Osaka, Manila}}},
      {Tehran, {Black, {Baghdad, Moscow, Karachi, Delhi}}},
      {Tokyo, {Red, {Seoul, Shanghai, Osaka, SanFrancisco}}},
      {Washington, {Blue, {Atlanta, NewYork, Montreal, Miami}}}};
  array<int, 4> cures;
public:
  Board() { cures.fill(0); }
  ~Board() {}
  friend ostream &operator<<(ostream &os, const Location &loc);
  int &operator[](City c);
  friend ostream &operator<<(ostream &os, const Board &board);
  bool is_clean();
  bool isConnected(City from, City to);
  bool labExists(City city);
  void makeLab(City city);
  void remove_cures();
  void remove_stations();
  static string toString(City city);
  static string toString(Color color);
  Color colorOf(City city);
  void addCure(Color color);
  array<int, 4> &getCureArray();
  int numOfCubes();
};
} // namespace pandemic