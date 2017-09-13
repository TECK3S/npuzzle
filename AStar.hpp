#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <functional>
#include <set>
#include <cstring>
#include <boost/unordered_set.hpp>
#include "State.hpp"
#include "Logger.hpp"
#include "Heuristic.hpp"

#define OFFSET_BASIS 2166136261
#define FNV 16777619

/* Function created to be in the unordered_sets */


struct heur_less// : public std::less<State<n> >
{
  bool operator() (State* const& s1, State* const& s2) const
  {
    return s1->heuristic < s2->heuristic;
  }
};

struct Functor
{
  Functor(unsigned int numb):
    n(numb)
  {}

  ~Functor(){};

  bool operator()(char* const& s1, char* const& s2) const
  {
    for (unsigned int i = 0; i < n; i++)
      if (s1[i] != s2[i])
        return false;
    return true;
  }

  std::size_t operator() (char* const& s) const
  {
    std::size_t hash = OFFSET_BASIS;
    for (unsigned int i = 0; i < n; i++)
    {
      hash = hash * FNV;
      hash = hash ^ (unsigned int)(unsigned char)s[i];
    }
    return hash;
  }

  unsigned int n;
};


/* End of functions */

class AStar
{
  typedef boost::unordered_set<char*, Functor, Functor> Set;
  typedef std::multiset<State*, heur_less> MultiSet;

  public:
  AStar(State* initial, State* final, size_t bucket):
    m_functor(initial->n * initial->n),
    m_openedState(bucket, m_functor, m_functor),
    m_closedState(bucket, m_functor, m_functor),
    m_final(final),
    m_heuristic(0)
  {
    m_openedHeur.insert(initial);
    m_openedState.insert(initial->state);
  }

  ~AStar()
  {
  }

  void SetHeuristic(Heuristic* heur)
  {
    if (this->m_heuristic)
      delete this->m_heuristic;
    this->m_heuristic = heur;
  }

  /* To start the algorithm */

  void start()
  {
    search_final();
  }

  /* End of start */

  private:

  void decide(State* state, Common::Move m)
  {
    State* newState = new State(state->n);
    Common::setState(state, newState, m);
    newState->father = m;
    newState->hit = state->hit + 1;
    newState->heuristic = newState->hit + m_heuristic->GetHeuristic(newState, m_final);
    Set::iterator it = m_closedState.find(newState->state);
    if (it != m_closedState.end())
    {
      delete newState;
      return;
    }
    else
    {
      if (m_openedState.insert(newState->state).second)
        m_openedHeur.insert(newState);
	  else
	  {
		delete newState->state;
        delete newState;
	  }
    }
  }

  /* To deploy sons of a node */
  void expand(State*  state)
  {
    if (state->zeros[0] > 0 && state->father != Common::DOWN)
      decide(state, Common::UP);
    if (state->zeros[1] > 0 && state->father != Common::RIGHT)
      decide(state, Common::LEFT);
    if (state->zeros[1] < state->n - 1 && state->father != Common::LEFT)
      decide(state, Common::RIGHT);
    if (state->zeros[0] < state->n - 1 && state->father != Common::UP)
      decide(state, Common::DOWN);
  }

  void search_final()
  {
    State* currentState;
    bool found = false;
    while (!found && !m_openedHeur.empty())
    {
      currentState = *(m_openedHeur.begin());
      m_openedHeur.erase(m_openedHeur.begin());
      m_openedState.erase(m_openedState.begin());
      m_closedState.insert(currentState->state);
      if (*currentState == *m_final)
      {
        std::cout << "Trouve en " << currentState->hit << " coups." << std::endl;
        found = true;
      }
      else
        expand(currentState);
      delete currentState;
    }
    if (!found)
    {
      std::cout << m_openedState.size() << " élements dans la liste ouverte." << std::endl;
      std::cout << m_closedState.size() << " élements dans la liste fermee." << std::endl;
    }
  }

  /* End of expand */

  private:

  Functor m_functor;
  Set m_openedState;
  Set m_closedState;
  MultiSet m_openedHeur;
  State* m_final;
  Heuristic* m_heuristic;
};

#endif
