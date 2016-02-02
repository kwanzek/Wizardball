#ifndef STATECOMPONENT_H
#define STATECOMPONENT_H

#include <string>

class StateComponent
{
public:
    inline StateComponent(std::string state) :
        state(state)
    {}
    std::string state;
};

#endif // STATECOMPONENT_H
