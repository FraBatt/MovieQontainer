#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <iostream>

class myexception {
private:
    std::string cosa;
public:
    myexception(std::string);

    std::string getCosa() const;
};

#endif // MYEXCEPTION_H
