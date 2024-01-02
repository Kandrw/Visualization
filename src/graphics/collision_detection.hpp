#include <vector>

#include "template_object.hpp"

class Collision_detection{

public:
    Collision_detection();
    int add_object(Data_object *object);
    float detection(int id, float x, float y, float z);
    int pop_object(int id);
private:
    std::vector<Data_object *> list;

};