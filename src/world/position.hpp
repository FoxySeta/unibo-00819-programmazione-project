/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Mattia Girolimetto #977478
  01/08/2021

  position.cpp: //TODO.
*/
#ifndef WORLD_POSITION_HPP
#define WORLD_POSITION_HPP

#include "../engine/block_tile.hpp"
#include "../engine/screen.hpp"
#include "../nostd/list.hpp"
#include "../nostd/matrix.hpp"
#include <exception>
#include <functional>
#include <iterator>

namespace World {
class Position {
private:
  const Nostd::List<Nostd::Matrix<Engine::BlockTile *>> *environment;
  Nostd::List<Nostd::Matrix<Engine::BlockTile *>>::iterator
      fragment; // TODO const iterator
  int x;
  int y;
  static const int INITIAL_Y = 19;

public:
  Position(const Nostd::List<Nostd::Matrix<Engine::BlockTile *>> *environment,
           int x = 0, int y = INITIAL_Y);

  int get_x() const noexcept;
  int get_y() const noexcept;
  Nostd::List<Nostd::Matrix<Engine::BlockTile *>>::iterator
  get_fragment() const noexcept;

  bool move_left();

  bool move_right();

  bool move_down();

  bool move_up();
};

class InvalidPositionException : public std::exception {
private:
  std::string message;

public:
  InvalidPositionException(const int &x, const int &y) {
    this->message = "(" + std::to_string(x) + " " + std::to_string(y) +
                    ") isn't a valid position";
  }

  const char *what() const noexcept override { return message.c_str(); }
};
} // namespace World

#endif // WORLD_POSITION_HPP
