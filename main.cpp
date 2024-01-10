#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "dinosaurs/dinosaur.hpp"

class Player
{
private:
  enum struct DinosaurType { Tyrannosaurus, Triceratop };

  // resourses
  static std::map<int, Tyrannosuarus> _tyrannosauruses;
  static std::map<int, Triceratops> _triceraptors;
  static int _index;

  int _money = 100;
  std::vector<Dinosaur *> _dinosaurs;
  int _chosed_dinosaur = 0;
  std::string _name;

public:
  int money() { return _money; }
  const std::string & name() { return _name; }

  Player()
  {
    std::cout << "input name: ";
    std::cin >> _name;
  }

  void add_money(int money_to_add) { _money += money_to_add; }

  bool buy()
  {
    std::cout << "you (" << _name << ") have " << _money << " money\n";
    std::cout << "cost of dinosaurs: \n";
    std::cout << "1) Tyrannosuarus: " << Tyrannosuarus::get_cost() << "\n";
    std::cout << "2) Triceratops: " << Triceratops::get_cost() << "\n";
    std::cout << "0 - dont buy, exit, for by input number of dinosaurs: ";
    int number;
    std::cin >> number;
    std::cout << '\n';
    std::string name;
    switch (number)
    {
    case 0:
      return true;
    case 1:
      if (_money < Tyrannosuarus::get_cost())
        return false;
      _money -= Tyrannosuarus::get_cost();
      std::cout << "input name: ";
      std::cin >> name;
      std::cout << "\n";
      _tyrannosauruses.emplace(_index, Tyrannosuarus(name));
      _dinosaurs.push_back(&_tyrannosauruses[_index++]);
      break;
    case 2:
      if (_money < Triceratops::get_cost())
        return false;
      std::cout << "input name: ";
      std::cin >> name;
      std::cout << "\n";
      _money -= Triceratops::get_cost();
      _triceraptors.emplace(_index, Triceratops(name));
      _dinosaurs.push_back(&_triceraptors[_index++]);
      break;
    }
    return false;
  }

  Dinosaur * choose()
  {
    std::cout << "avaible for " << _name << " dinosaurs:\n";
    for (int i = 0; i < _dinosaurs.size(); i++)
      std::cout << i << ") " << _dinosaurs[i]->name() << ", has " << _dinosaurs[i]->hp() << " hp" << '\n';
    std::cout << "input number of dinosaur which you want use: ";
    int number;
    std::cin >> number;
    std::cout << "\n";
    if (number < 0 || number >= _dinosaurs.size())
      throw std::exception("index out of range");
    _chosed_dinosaur = number;
    return _dinosaurs[number];
  }

  bool deal_damage(int damage)
  {
    _dinosaurs[_chosed_dinosaur]->_hp -= damage;
    if (_dinosaurs[_chosed_dinosaur]->_hp > 0)
      return false;
    _dinosaurs.erase(_dinosaurs.begin() + _chosed_dinosaur);
    return true;
  }

  bool is_lose() { return _dinosaurs.size() == 0; }

  void save_to_file(std::ofstream &out)
  {
    DinosaurType type;
    out.write((char *)&_money, sizeof(_money));
    std::size_t size = _dinosaurs.size();
    out.write((char *)&size, sizeof(size));
    std::size_t lenght = _name.length();
    out.write((char *)&lenght, sizeof(lenght));
    out.write(_name.data(), lenght);
    for (auto d : _dinosaurs)
    {
      if (dynamic_cast<Tyrannosuarus *>(d) != nullptr)
        type = DinosaurType::Tyrannosaurus;
      else if (dynamic_cast<Triceratops *>(d) != nullptr)
        type = DinosaurType::Triceratop;
      out.write((char *)&type, sizeof(type));
      out.write((char *)&d->_hp, sizeof(d->_hp));
      lenght = d->_name.size();
      out.write((char *)&lenght, sizeof(lenght));
      out.write(d->_name.data(), lenght);
    }
  }

  Player(std::ifstream &in)
  {
    DinosaurType type;
    std::size_t size, lenght;
    in.read((char *)&_money, sizeof(_money));
    in.read((char *)&size, sizeof(size));
    _dinosaurs.resize(size);
    in.read((char *)&lenght, sizeof(lenght));
    _name.resize(lenght);
    in.read((char *)_name.data(), lenght);
    for (auto &d : _dinosaurs)
    {
      in.read((char *)&type, sizeof(type));
      int hp;
      std::string name;
      in.read((char *)&hp, sizeof(hp));
      in.read((char *)&lenght, sizeof(lenght));
      name.resize(lenght);
      in.read((char *)name.data(), lenght);
      switch (type)
      {
      case DinosaurType::Tyrannosaurus:
        _tyrannosauruses.emplace(_index, Tyrannosuarus(name));
        d = &_tyrannosauruses[_index++];
        break;
      case DinosaurType::Triceratop:
        _triceraptors.emplace(_index, Triceratops(name));
        d = &_triceraptors[_index++];
        break;
      }
      d->_hp = hp;
    }
  }
};

std::map<int, Tyrannosuarus> Player::_tyrannosauruses;
std::map<int, Triceratops> Player::_triceraptors;
int Player::_index = 0;

class Game
{
  void draw_field(Terrain terrain, Dinosaur *dinos[2])
  {
    std::string terrrains_name[] {"Plain", "River", "Mountain"};
    std::cout << "Terrain is: " << terrrains_name[(int)terrain] << "\n";
    for (int i = 0; i < 2; i++)
      std::cout << dinos[i]->name() << " has " << dinos[i]->hp() << " hp\n";
    std::cout << '\n';

    auto d1 = dinos[0]->reverse_dinosaur_ascii();
    auto d2 = dinos[1]->dinosaur_ascii();
    std::cout << d1[0] << "   " << d2[0] << '\n';

    int i = 1, j = 1;
    if (d1.size() < d2.size())
    {
      std::string empty(d1.size(), ' ');
      while (d1.size() - i < d2.size() - j)
        std::cout << empty << "   " << d2[j++] << '\n';
    }
    else if (d1.size() > d2.size())
      while (d1.size() - i > d2.size() - j)
        std::cout << d1[i++] << '\n';
    int times = d1.size() - i;
    for (int k = 0; k < times; k++)
      std::cout << d1[i++] << "   " << d2[j++] << '\n';

    std::cout << "\n\n\n";
  }
  
public:
  Game()
  {
    srand(time(NULL));
    std::cout << "input 0 if you want start new game or 1 if you if want load from file: ";
    int number;
    std::cin >> number;
    std::cout << '\n';
    std::vector<Player> players;
    if (number == 0)
      for (int i = 0; i < 2; i++)
        players.push_back(Player());
    else if (number == 1)
    {
      std::ifstream in("save.bin", std::ios_base::binary);
      if (!in)
        throw std::exception("there arent any saved games!");
      for (int i = 0; i < 2; i++)
        players.push_back(Player(in));
    }
    else
      throw std::exception("invalid option");

    while (true)
    {
      std::cout << "\n\n---------------------------\n";
      std::cout << "new turn\n\n";

      Dinosaur *dinos[2] {};
      for (int i = 0; i < 2; i++)
      {
        while (!players[i].buy());
        dinos[i] = players[i].choose();
      }

      if (players[0].is_lose() || players[1].is_lose())
        break;

      auto terrain = (Terrain)(rand() % 3);
      draw_field(terrain, dinos);

      int damages[] {dinos[0]->damage(terrain), dinos[1]->damage(terrain)};
      int costs[] {dinos[0]->cost(), dinos[1]->cost()};
      for (int i = 0; i < 2; i++)
      {
        std::cout << dinos[i]->name() << " dealt " << damages[i] << " to " << dinos[1 - i]->name() << "\n";
        if (players[1 - i].deal_damage(damages[i]))
        {
          players[i].add_money(costs[1 - i] / 2);
          std::cout << players[i].name() << " win " << costs[1 - i] / 2 << " money\n";
        }
      }

      std::cout << "turn end\n\n";

      std::cout << "do you want continue (0) or u want save game (1)?: ";
      int number;
      std::cin >> number;
      std::cout << "\n\n";
      if (number == 0)
        continue;
      else if (number == 1)
      {
        std::ofstream out("save.bin", std::ios_base::binary);
        for (int i = 0; i < 2; i++)
          players[i].save_to_file(out);
        break;
      }
      else
        throw std::exception("invalid option");
    }
  }
};

int main()
{
  Game game;
}