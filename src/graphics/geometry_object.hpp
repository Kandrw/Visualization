




class Shader;

class GeometryObj{

public:
    GeometryObj();
    ~GeometryObj();
    
    int get_N();
    void set_N(int N);
    
private:
    bool load_data();
    bool load_shader();
    void render();
private:
    int N;
    //Вынести в отдельную структуру данных или класс
    int *array_heights = nullptr;
    float *array_lats = nullptr;
    float *array_lons = nullptr;
    
    Shader *shader = nullptr;

    float *buffer = nullptr;


    


};



