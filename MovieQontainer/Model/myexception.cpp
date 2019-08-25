#include "myexception.h"

myexception::myexception(std::string c) : cosa(c) {}

std::string myexception::getCosa() const {
    return cosa;
}
