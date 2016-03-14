#ifndef STATESYSTEM_H
#define STATESYSTEM_H

#include <System.h>
#include <string>
#include <vector>

struct StateComponent
{
public:
    inline StateComponent(unsigned int eid, std::string state) :
        state(state)
    {}
     int eid;
    std::string state;
};

class StateSystem : public System
{
    public:
        StateSystem();
        virtual ~StateSystem();
        void update(float deltaTime);

        StateComponent& addComponent(unsigned int eid, std::string stateString);
        bool deleteComponent(unsigned int eid);
        bool hasComponent(unsigned int eid);
        StateComponent& getComponent(unsigned int eid);

        std::vector<StateComponent> components;
        std::vector<int> handles;

    protected:
    private:
};

#endif // STATESYSTEM_H
