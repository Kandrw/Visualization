#include <iostream>
#include <fstream>


#include <cstring>









void read_txt_to_bin_write(char *filename){
    std::ifstream file(filename);
    int N = 1e6;
    int i = 0;
    std::string ns;
    file>>ns>>ns;
    //file>>N;
    std::cout<<"ns = "<<ns<<"\n";
    double lat, lon;
    int height;
    double *lat_array = new double[N];
    double *lon_array = new double[N];
    int *height_array = new int[N];
    std::cout.precision(10);

    int sh = 0, slat = 0, slon = 0;
    for(i = 0; i < N; ++i){
        file>>lat>>lon>>height;
        lat_array[i] = lat;
        lon_array[i] = lon;
        height_array[i] = height;
        if(i % 100000 == 0){
            std::cout<<height_array[i]<<" "<<lat_array[i]<<" "<<lon_array[i]<<"\n";
        }
        sh += height_array[i];
        slat += lat_array[i];
        slon += lon_array[i];
    }
    file.close();
    std::cout<<"sh = "<<sh<<"\tslat ="<<slat<<"\tslon"<<slon<<"\n";
    char fwname_h[] = "heights.bin";
    char fwname_lat[] = "lats.bin";
    char fwname_lon[] = "lons.bin";
    
    FILE *filew = fopen(fwname_h, "w");
    int size = fwrite(height_array, sizeof(int), N, filew);
    std::cout<<"sizeh = "<<size<<"\n";
    fclose(filew);
    filew = fopen(fwname_lat, "w");
    size = fwrite(lat_array, sizeof(double), N, filew);
    std::cout<<"sizelat = "<<size<<"\n";
    fclose(filew);
    filew = fopen(fwname_lon, "w");
    size = fwrite(lon_array, sizeof(double), N, filew);
    std::cout<<"sizelon = "<<size<<"\n";
    fclose(filew);
    
    delete[] height_array, lat_array, lon_array;
    
}
void read_txt_to_bin_write2(char *filename){
    std::ifstream file(filename);
    //FILE *file = fopen(filename, "r");
    int N = 1e6;
    int i = 0;
    std::string ns;
    file>>ns>>ns;
    //file>>N;
    std::cout<<"ns = "<<ns<<"\n";
    double lat, lon;
    int height;
    double *lat_array = new double[N];
    double *lon_array = new double[N];
    int *height_array = new int[N];

    std::cout.precision(10);
    int t = 0;
    for(i = 0; i < N; ++i){
        file>>lat>>lon>>height;
        lat_array[i] = lat;
        lon_array[i] = lon;
        height_array[i] = height;
        if(i % 100000 == 0){
            std::cout<<height_array[i]<<" "<<lat_array[i]<<" "<<lon_array[i]<<"\n";
            //std::cout<<height_array[i]<<"\n";
        }
        //std::cout<<height_array[i]<<" "<<lat_array[i]<<" "<<lon_array[i]<<"\n";
        //t += height_array[i] + lat_array[i] + lon_array[i];
        t += height_array[i];
        
    }
    file.close();
    std::cout<<"t = "<<t<<"\n";
    char fwname_h[] = "heights.bin";
    char fwname_lat[] = "lats.bin";
    char fwname_lon[] = "lons.bin";
    
    std::ofstream filew(fwname_h);
    filew.write((char*)height_array, N);
    filew.close();
    filew.open(fwname_lat);
    filew.write((char*)lat_array, N);
    filew.close();
    filew.open(fwname_lon);
    filew.write((char*)lon_array, N);
    filew.close();
    
    
    delete[] height_array, lat_array, lon_array;
    
}
int *read_bin_type_int1(char *fname, int N){
    FILE *filew = fopen(fname, "r");
    int *array = new int[N];
    int size = fread(array, sizeof(int), N, filew);
    std::cout<<"size = "<<size<<"\n";
    fclose(filew);
    return array;
}
int *read_bin_type_int(char *fname, int N){

    // std::ifstream file(fname);
    // int *array = new int[N];
    // std::memset(array, 0, N);
    // file.read((char*)array, N);
    // file.close();
    FILE *filew = fopen(fname, "r");
    int *array = new int[N];
    int size = fread(array, sizeof(int), N, filew);
    std::cout<<"size = "<<size<<"\n";
    fclose(filew);
    return array;
}
double *read_bin_type_double(char *fname, int N){
    
    FILE *filew = fopen(fname, "r");
    double *array = new double[N];
    int size = fread(array, sizeof(double), N, filew);
    std::cout<<"size = "<<size<<"\n";
    fclose(filew);
    
    /*
    std::ifstream file(fname);
    double *array = new double[N];
    std::memset(array, 0, N);
    file.read((char*)array, N);
    file.close();
    */
    return array;
}


int read_bin_l_l_h(char *f_lat, char *f_lon, char *f_h){

    int *height_array;
    double *lat_array;
    double *lon_array;
    int N = 1e6;
    

    height_array = read_bin_type_int(f_h, N);
    lat_array = read_bin_type_double(f_lat, N);
    lon_array = read_bin_type_double(f_lon, N);
    int sh = 0, slat = 0, slon = 0;

    for(int i = 0; i < N; ++i){
        if(i % 100000 == 0){
            std::cout<<height_array[i]<<" "<<lat_array[i]<<" "<<lon_array[i]<<"\n";
            //std::cout<<height_array[i]<<"\n";
        }
        //std::cout<<height_array[i]<<"\n";
        sh += height_array[i];
        slat += lat_array[i];
        slon += lon_array[i];

    }
    std::cout<<"sh = "<<sh<<"\tslat ="<<slat<<"\tslon"<<slon<<"\n";

    //delete[] height_array, lat_array, lon_array;

}




int main(){
    char file[] = "DATA_1000_1000_LAN_LON_HEIGHT.txt";
    char fwname_h[] = "heights.bin";
    char fwname_lat[] = "lats.bin";
    char fwname_lon[] = "lons.bin";
    //std::cout<<sizeof(double)<<"\n";
    read_txt_to_bin_write(file);
    read_bin_l_l_h(fwname_lat, fwname_lon, fwname_h );
    std::cout<<"End program\n";
    return 0;
}



