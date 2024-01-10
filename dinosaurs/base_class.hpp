#pragma once

#include <string>
#include <vector>

enum struct Terrain { Plain, River, Mountain };

class Dinosaur
{
  friend class Player;

protected:
  int _strong;
  int _dexterity;
  int _intellect;
  int _hp = 100;
  int _cost;
  std::string _name;
  std::string _full_name;
  std::vector<std::string> _dinosaur_ascii;
  std::vector<std::string> _reverse_dinosaur_ascii;

public:
  const std::string & name() { return _full_name; }
  const std::vector<std::string> & dinosaur_ascii() { return _dinosaur_ascii; }
  const std::vector<std::string> & reverse_dinosaur_ascii() { return _reverse_dinosaur_ascii; }
  int hp() { return _hp; }
  int cost() { return _cost; }

public:
  virtual int damage(Terrain terrain) = 0;
};
