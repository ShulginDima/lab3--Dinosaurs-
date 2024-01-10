
#include "base_class.hpp"

class Tyrannosuarus : public Dinosaur
{
public:
  int damage(Terrain terrain) override
  {
    return 
      terrain == Terrain::Plain ? 2 * _strong :
      terrain == Terrain::River ? _dexterity :
      _intellect; // terrain is mountain
  }

  Tyrannosuarus() {}

  Tyrannosuarus(const std::string &name)
  {
    _name = name;
    _full_name = "Tyrannosuarus " + name;
    _strong = 26;
    _dexterity = 19;
    _intellect = 10;
    _cost = get_cost();
    _dinosaur_ascii = std::vector<std::string>
    {
      "                            TYRANNOSUARUS                           ",
      "         :==+-:                                                     ",
      "      .-+==+=====-----===---::::..                                  ",
      "   :-===========+====+=++=++=+======---::..... .....::--===--:.     ",
      "  :==-::+=============+=+=+=++=========+=+==+==+=======-:.. ...:::  ",
      "       =--::. .===============+==+================-:..              ",
      "      ::.      .==============++====+==---::::...                   ",
      "              --.:-::::------========-:.                            ",
      "              : :=      .::::-=======:                              ",
      "                              :++======                             ",
      "                             -+-.   .:==-                           ",
      "                            .++        .--                          ",
      "                             -          .==                         ",
      "                                      .-=+-                         ",
      "                                        ..                          ",
    };
    _reverse_dinosaur_ascii = _dinosaur_ascii;
    for (int i = 1; i < _reverse_dinosaur_ascii.size(); i++)
      std::reverse(_reverse_dinosaur_ascii[i].begin(), _reverse_dinosaur_ascii[i].end());
  }

  static int get_cost() { return 40; }
};