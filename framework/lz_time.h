#ifndef LZ_TIME_H 
#define LZ_TIME_H

#include <ctime>
#include <iostream>

namespace LZ {

class Time {

    // This class defines a Time object to retrieve current time

  public:

    Time() { }

    ~Time() { }

    friend std::ostream& operator<< (std::ostream& stream, const Time&); 

    int getYear() const;
    int getMon() const;
    int getDay() const;
    int getHour() const;
    int getMin() const;
    int getSec() const;

  private:

};

} // close namespace

#endif
