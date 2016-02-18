#ifndef LZ_RUNNABLE_H 
#define LZ_RUNNABLE_H

namespace LZ {

class Runnable {

  public:

    Runnable() {}

    virtual ~Runnable() {}

    virtual void run() = 0;

  private:

};

} // close namespace

#endif
