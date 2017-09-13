#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Parser.hh"

static void from_string(const std::string & Str, unsigned int & Dest)
{
  int            tmp;
  unsigned int   i = 0;

  while (i < Str.length() && (Str[i] < '0' || Str[i] > '9'))
    i++;
  std::istringstream iss(&Str[i]);
  if (!(iss >> tmp))
  {
    std::cout << "Bad String, could not convert!!!!!!!!!" << std::endl;
    // return (0);
  }
  Dest = tmp;
  // return (Dest);
}

Parser::Parser(const char * file_name):
  _puzzle(""), // indice = x + y * Largeur
  _puzzleLength(0),
  _size(0)
{
  unsigned int i, cpt = 0;
  std::ifstream readFile(file_name);
  if (readFile)
  {
    std::string line;
	i = 0;
    while (std::getline(readFile, line))
    {
	  if (line.length() > 0 && line[0] == '#')
		  continue;
	  unsigned int j;
	  if (_size == 0 && (line[0] < '0' || line[0] > '9'))
	  {
		  std::cout << "There is a bad character in this room !" << std::endl;
		  exit(1);
	  }
	  else if (_size == 0)
	  {
		  _puzzle = new char[_size * _size];
		  from_string(line, _size);
	  }
	  else if (_size != 0)
	  {
		  unsigned int j = 0;
		  unsigned int h = 0;
		  while ((j = line.find_first_of("0123456789", j)) != std::string::npos)
		  {
			  h = line.find_first_not_of("0123456789", j);
			  std::cout << line.substr(j, h - j) << std::endl;
			  unsigned int tmp;
			  from_string(line.substr(j, h - j), tmp);
			  _puzzle[i] = (char) tmp;
			  i++;
			  j = h;
		  }
	  }
    }
  }
  readFile.close();
}

Parser::~Parser()
{
}

int Parser::getSize()const
{
  return (this->_size);
}

unsigned int Parser::getPuzzleLength() const
{
  return (this->_puzzleLength);
}

char * Parser::getInitialState()
{
  return (this->_puzzle);
}

char * Parser::getFinalState()
{
 _final = new char[_size * _size];
  unsigned int n = this->_size;
  unsigned int length = this->_puzzleLength - 1;
  char tmp = this->_puzzle[n];
  for (int cpt = length; cpt >= 0; cpt--)
  {
    for (int i = 0; i < cpt ; i++)
    {
      if (this->_puzzle[cpt] != '0' && (this->_puzzle[i] > this->_puzzle[cpt] || this->_puzzle[i] == '0'))
      {
        tmp = this->_puzzle[i];
        this->_puzzle[i] = this->_puzzle[cpt];
        this->_puzzle[cpt] = tmp;
      }
    }
  }
  std::cout << "Sorted puzzle : " << this->_puzzle << std::endl;
  this->_final[0] = this->_puzzle[0 + 1];
  bool inc  = true;
  unsigned int downRight = length - 1;
  unsigned int upLeft = 0;
  unsigned int upRight = n - 1;
  unsigned int downLeft =  n * (n - 1);
  unsigned int cpt = 0;

  for (unsigned i = 0; i < length ; i++)
  {
    if (inc)
    {
      if (cpt < upRight)
        ++cpt;
      else if (upRight < downRight)
      {
        upRight+= n;
        cpt+= n;
      }
      else
      {
        cpt+= 1;
        downRight = downRight - n -1;
        upRight = upRight + n - 1;
        inc = false;
      }
    }
    else
    {
      if (cpt > downLeft)
        --cpt;
      else if (downLeft > upLeft)
      {
        downLeft-= n;
        cpt-= n;
      }
      else
      {
        upLeft = upLeft + n + 1;
        cpt = upLeft;
        downLeft = downLeft - n + 1;
        inc = true;
      }
    }
    this->_final[cpt] = this->_puzzle[i];
    ++i;
    // indice = x + y * Largeur
  }
  return (this->_final);
}
