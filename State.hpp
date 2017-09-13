#ifndef STATE_HPP
#define STATE_HPP
#include <iostream>
#include <cstring>
#include <cstring>

struct State
{
  State(unsigned int n):
    hit(0),
    heuristic(0),
    father(4),
    n(n)
  {
    state = new char[n * n];
    zeros[0] = 0;
    zeros[1] = 0;
  }

  State(const char * source, unsigned int n):
    hit(0),
    heuristic(0),
    father(4),
    n(n)
  {
    state = new char[n * n];
    for (unsigned int i = 0; i < n * n; i++)
      this->state[i] = source[i];
    this->seek_zero();
  }

  State(State const& cpy):
    hit(cpy.hit),
    heuristic(cpy.heuristic),
    father(cpy.father),
    n(cpy.n)
  {
    state = new char[n * n];
    for (unsigned int i = 0; i < n * n; i++)
      this->state[i] = cpy.state[i];
    this->seek_zero();
  }

  State& operator=(const State& state)
  {
    this->hit = state.hit;
    this->heuristic = state.heuristic;
    this->father = state.father;
    this->n = state.n;
    for (unsigned int i = 0; i < n * n; i++)
      this->state[i] = state.state[i];
    this->seek_zero();
    return *this;
  }

  bool operator==(const State& state) const
  {
    unsigned int i = 0;
    while (i < n * n)
    {
      if (this->state[i] != state.state[i])
        return false;
      i++;
    }
    return true;
  }

  char seek_zero()
  {
    for (unsigned int i = 0; i < n * n; i++)
      if (state[i] == 0)
      {
        this->zeros[0] = i / n;
        this->zeros[1] = i % n;
        return i;
      }
    return 0;
  }

  char *state;
  unsigned int hit;
  unsigned int heuristic;
  unsigned int father;
  unsigned int zeros[2];
  unsigned int n;
};

namespace Common
{
  enum Move
  {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
  };

  void setState(State* source, State* dest, Move m)
  {
    memcpy(dest->state, source->state, source->n * source->n);
    if (m == NONE)
      return;
    switch (m)
    {
      case UP:
        dest->state[source->zeros[0] * source->n + source->zeros[1]] = dest->state[(source->zeros[0] - 1) * source->n + source->zeros[1]];
        dest->state[(source->zeros[0] - 1) * source->n + source->zeros[1]] = 0;
        dest->zeros[0] = source->zeros[0] - 1;
        dest->zeros[1] = source->zeros[1];
        break;
      case DOWN:
        dest->state[source->zeros[0] * source->n + source->zeros[1]] = dest->state[(source->zeros[0] + 1) * source->n + source->zeros[1]];
        dest->state[(source->zeros[0] + 1) * source->n + source->zeros[1]] = 0;
        dest->zeros[0] = source->zeros[0] + 1;
        dest->zeros[1] = source->zeros[1];
        break;
      case LEFT:
        dest->state[source->zeros[0] * source->n + source->zeros[1]] = dest->state[source->zeros[0] * source->n + source->zeros[1] - 1];
        dest->state[source->zeros[0] * source->n + source->zeros[1] - 1] = 0;
        dest->zeros[0] = source->zeros[0];
        dest->zeros[1] = source->zeros[1] - 1;
        break;
      case RIGHT:
        dest->state[source->zeros[0] * source->n + source->zeros[1]] = dest->state[source->zeros[0] * source->n + source->zeros[1] + 1];
        dest->state[source->zeros[0] * source->n + source->zeros[1] + 1] = 0;
        dest->zeros[0] = source->zeros[0];
        dest->zeros[1] = source->zeros[1] + 1;
        break;
      default:
        break;
    }
  }
}

#endif
