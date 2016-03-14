#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>

class EntityManager
{
    public:
        EntityManager();
        ~EntityManager();
       int createEntity();
       int _previousID;

    protected:
    private:
       int getID();
        std::vector<int> entities;
};

#endif // ENTITYMANAGER_H
