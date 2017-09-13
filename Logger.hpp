#ifdef NLOG
#include <string>
#define LFILE \
  std::string(__FILE__, \
      std::string(__FILE__).find_last_of('/') + 1, \
      std::string(__FILE__).size() - std::string(__FILE__).find_last_of('/') - 1)
#define LOG(n) \
  std::cout << \
  LFILE << ":" << __LINE__ << " ---> " << n << \
  std::endl;
#else
#define LOG(n)
#endif
