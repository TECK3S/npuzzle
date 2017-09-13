#ifndef PARSER_HH
#define PARSER_HH

class Parser
{
public:
  Parser(const char * file_name);
  ~Parser();
  Parser(Parser const & p);
  Parser & operator=(Parser const & p);
  int getSize() const;
  unsigned int getPuzzleLength() const;
  char * getInitialState();
  char * getFinalState();

private:
  char *_puzzle;
  char *_final;
  std::string file_state;
  unsigned int _puzzleLength;
  unsigned int _size;
};

#endif //!PARSER_HH
