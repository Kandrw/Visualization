#include <iostream>
#include <fstream>


#include <cstring>


void read_txt_to_bin_write(char *filename, char *f_lat, char *f_lon, char *f_h){
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
    std::cout<<"sh = "<<sh<<"\tslat = "<<slat<<"\tslon = "<<slon<<"\n";
    //char fwname_h[] = "heights.bin";
    //char fwname_lat[] = "lats.bin";
    //char fwname_lon[] = "lons.bin";
    
    FILE *filew = fopen(f_h, "wb");
    int size = fwrite(height_array, sizeof(int), N, filew);
    std::cout<<"sizeh = "<<size<<"\n";
    fclose(filew);
    FILE * filew1 = fopen(f_lat, "wb");
    size = fwrite(lat_array, sizeof(double), N, filew1);
    std::cout<<"sizelat = "<<size<<"\n";
    fclose(filew1);
    filew = fopen(f_lon, "wb");
    size = fwrite(lon_array, sizeof(double), N, filew);
    std::cout<<"sizelon = "<<size<<"\n";
    fclose(filew);
    
    delete[] height_array, lat_array, lon_array;
    
}




int *read_bin_type_int(char *fname, int N){
    FILE *filew = fopen(fname, "rb");
    int *array = new int[N];
    int size = fread(array, sizeof(int), N, filew);
    std::cout<<"size = "<<size<<"\n";
    fclose(filew);
    return array;
}
double *read_bin_type_double(char *fname, int N){
    
    FILE *filew = fopen(fname, "rb");
    double *array = new double[N];
    memset(array, 0, N);
    int size; 
    size = fread(array, sizeof(double), N, filew);
    std::cout<<"size = "<<size<<"\n";
    fclose(filew);
    return array;
}
int read_bin_l_l_h(char *f_lat, char *f_lon, char *f_h){

    int *height_array;
    double *lat_array;
    double *lon_array;
    int N = 1e6;
    lon_array = read_bin_type_double(f_lon, N);
    lat_array = read_bin_type_double(f_lat, N);
    height_array = read_bin_type_int(f_h, N);
    
    
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
    std::cout<<"sh = "<<sh<<"\tslat ="<<slat<<"\tslon = "<<slon<<"\n";

    //delete[] height_array, lat_array, lon_array;

}

int main(){
    char file[] = "DATA_1000_1000_LAN_LON_HEIGHT.txt";
    char fwname_h[] = "heights.bin";
    char fwname_lat[] = "lats.bin";
    char fwname_lon[] = "lons.bin";
    //std::cout<<sizeof(double)<<"\n";
    //read_txt_to_bin_write(file, fwname_lat, fwname_lon, fwname_h);
    read_bin_l_l_h(fwname_lat, fwname_lon, fwname_h );
    std::cout<<"End program\n";
    return 0;
}



