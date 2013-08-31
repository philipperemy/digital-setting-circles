#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

class Object
{
public:
    Object(std::string name, double ra, double dec, std::string description);
    ~Object();

    std::string name;
    double ra;
    double dec;
    std::string description;


    static void fill();
    static void release();
    static std::vector<Object*> _objects_ptr;
private:
    static int object_instanced_count;
};

#endif // OBJECT_H
