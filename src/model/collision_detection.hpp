



struct data_object{
    float x, y, z;
    int N;
    float *vert;
    float speed;
    
};



class Collision_detection{

public:
    int add_object(data_object *object);
    float detection(int index);
    int pop_object(int index);
private:


};