#include <iostream>
#include "AStar.hpp"
#include "State.hpp"
#include "Parser.hh"
#include "BasicHeuristic.hpp"

int main(int argc, char **argv)
{
  if (argc != 2)
    {
      std::cout << "Error : Too few or many argument!\n"
		<< "Usage : ./taquin input_file" << std::endl;
      return 1;
    }
  char initial_state[9] =
  {
    1, 2, 8,
    7, 6, 0,
    4, 3, 5
  };

  char final_state[9] =
  {
    1, 2, 3,
    8, 0, 4,
    7, 6, 5
  };
  char initial_state4[16] =
  {
    3, 2, 8, 10,
    7, 6, 0, 11,
    4, 1, 5, 14,
    15, 12, 13, 9
  };

  char final_state4[16] =
  {
    1, 2, 3, 4,
    12, 13, 14, 5,
    11, 0, 15, 6,
    10, 9, 8, 7
  };
  
  Parser p(argv[1]);
  int n = p.getSize();
  char * initial_stateq = p.getInitialState();

  Heuristic* heur = new BasicHeuristic();
  State* initial = new State(initial_stateq, n);
  State* final;
  if (n == 4)
	final = new State(final_state4, n);
  else if (n == 3)
	final = new State(final_state, n);
  else
  {
	  std::cout << "Sorry for that :(" << std::endl;
	  exit(1);
  }
  initial->heuristic = heur->GetHeuristic(initial, final);
  boost::unordered_set<char*> tmpd;
  AStar astar(initial, final, tmpd.bucket_count());
  astar.SetHeuristic(heur);
  astar.start();
  system("PAUSE");
  return 0;
}
