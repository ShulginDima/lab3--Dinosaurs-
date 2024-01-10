#pragma once

#include "base_class.hpp"

class Triceratops : public Dinosaur
{
public:
  int damage(Terrain terrain) override
  {
    return 
      terrain == Terrain::Plain ? _strong :
      terrain == Terrain::River ? _dexterity :
      2 * _intellect; // terrain is mountain
  }

  Triceratops() {};

  Triceratops(const std::string &name)
  {
    _name = name;
    _full_name = "Triceratops " + name;
    _strong = 15;
    _dexterity = 22;
    _intellect = 24;
    _cost = get_cost();
    _dinosaur_ascii = std::vector<std::string>
    {
      "                       TRICERATOPS                          ",
      "                ...                                         ",
      "              -=+++=:                                       ",
      "             =+=+==+= ...:::::..                            ",
      "            :+=+===+++======---====---:.                    ",
      "      ..    =++====+++=================--                   ",
      "     ..:...:======+++====================-                  ",
      "      :-:-========+++=================-===-.                ",
      " ::-=-===========++============+===========-.               ",
      "  --============++====-=======++============-.              ",
      "  ..:::--=====--==+===========+=====++=======-.             ",
      "                =*++====+=+===++===++=+++=====-             ",
      "               .++*====-:...:::--===+**:.-=====-            ",
      "            .-=+++====:          .===++-   -=====:..        ",
      "             ::=+====           :-===+=-     :=++========-: ",
      "               ..:..             ....           ......      ",
    };
    _reverse_dinosaur_ascii = _dinosaur_ascii;
    for (int i = 1; i < _reverse_dinosaur_ascii.size(); i++)
      std::reverse(_reverse_dinosaur_ascii[i].begin(), _reverse_dinosaur_ascii[i].end());
  }

  static int get_cost() { return 34; }
};