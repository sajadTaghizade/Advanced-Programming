#ifndef MAJOR_HPP
#define MAJOR_HPP

#include "globalStuff.hpp"

class Major {
public:
    Major(string _mid, string _major);
    string get_mid(){return mid;}
    string get_major_name(){return major;}

private:
    string mid, major;
};

#endif // MAJOR_HPP
