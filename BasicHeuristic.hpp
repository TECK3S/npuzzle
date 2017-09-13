#ifndef BASIC_HEURISTIC_HPP
#define BASIC_HEURISTIC_HPP
#include "Heuristic.hpp"

class BasicHeuristic : public Heuristic
{
  public:
    virtual ~BasicHeuristic(){}
    float GetHeuristic(State* current, State* final) const
    {
      if (current->n != final->n)
        return -1;
      float heuristic = 0;
      for (unsigned int i = 0; i < current->n * current->n; i++)
      {
        if (current->state[i] != final->state[i])
          heuristic++;
      }
      return heuristic;
    }
};

#endif
