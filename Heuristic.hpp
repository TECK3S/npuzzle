#ifndef HEURISTIC_HPP
#define HEURISTIC_HPP

#include "State.hpp"

class Heuristic
{
  public:
    virtual ~Heuristic(){}
    virtual float GetHeuristic(State* current, State* final) const = 0;
};

#endif
