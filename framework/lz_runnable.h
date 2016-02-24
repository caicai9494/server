#ifndef LZ_RUNNABLE_H 
#define LZ_RUNNABLE_H

namespace LZ {

#include <string>

class Runnable {

    // This class defines an interface class
    // for thread function.

  public:

    Runnable() {}

    virtual ~Runnable() {}

    virtual void run() = 0;

  private:

};

} // close namespace

#endif
