#ifndef SINGLETON_H
#define SINGLETON_H

namespace LZ {

template <typename T>
class Singleton {
  public:

    // This code is concurrently safe in c++1x.
    // A thread will wait if the static variable 
    // is being initialized.
    static T* instance()
    {
	// Using the default constructor
	static T instn;
	return &instn;
    }

  protected:

    Singleton() = default;
};

} // close namespace

#endif
