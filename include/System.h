#ifndef SYSTEM_H
#define SYSTEM_H


class System
{
    public:
        System() {};
        virtual void update(float deltaTime) = 0;
    protected:
    private:
};

#endif // SYSTEM_H
