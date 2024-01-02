#include <iostream>
#include <cmath>

int distance_points(int x1, int y1, int x2, int y2){
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}
float distance_points(float x1, float y1, float x2, float y2){
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}



int main(){
    std::cout<<distance_points(0.1f, 0.1f, -0.1f, -0.1f);
    
}
















