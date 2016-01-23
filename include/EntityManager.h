#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>

class EntityManager
{
    public:
        EntityManager();
        ~EntityManager();
        unsigned int createEntity();
        unsigned int _previousID;

    protected:
    private:
        unsigned int getID();
        std::vector<unsigned int> entities;
};

#endif // ENTITYMANAGER_H
