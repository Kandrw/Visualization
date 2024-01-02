#include <iostream>

#define N 6
#define X 10
#define Y 10



void print(float **M, int len){
    int i, i2, i3;
    for(i = 0; i < len; ++i){
        for(i2 = 0; i2 < len; ++i2){
            //std::cout<<M[i][i2]<<" ";
            printf("%2.2f ", M[i][i2]);
        }
        std::cout<<"\n";
    }
}
void print_matrix(int M[N][N]){
    int i, j;
    for(i = 0; i < N; ++i){
        for(j = 0; j < N; ++j){
            printf("%3d ", *(M[0] + i * N + j));
        }
        printf("\n");
    }
}

int ylitka1(){
    int matrix[N][N];
    int i, j;
    int i2, j2;
    int n = N, n2 = N-1, n3 = N - 1, n4 = N-2;
    int iter = 1;
    /*Test*/
    for(i = 0; i < N; ++i){
        for(j = 0; j < N; ++j){
            matrix[i][j] = -1;
        }
    }
    int c = 0;
    int k1 = 0, k2 = 0;
    int k3 = 1, k4 = N-1;
    int k5 = N-2, k6 = N-1;
    int k7 = N-2, k8 = 0;
    for(iter = 1; n > 0;){
            for(j = k2; j < n; ++j){
                matrix[k1][j] = iter;
                //iter++;
            }
            k1++;
            k2++;
            n--;

            for(i = k3; i <= n2; ++i){
                matrix[i][k4] = iter;
                //iter++;
            }
            k3++;
            k4--;
            n2--;

            for(j = k5; j > k5-n3; --j){
                matrix[k6][j] = iter;
                //iter++;
            }
            k5--;
            k6--;
            n3-=2;

        
            for(i = k7; i > k7 - n4; --i){
                matrix[i][k8] = iter;
                //iter++;
            }
            k7--;
            k8++;
            n4-=2;

            iter++;
    }
    print_matrix(matrix);    
    printf("End\n");
    return 0;
}

int ylitka(float **matrix, int len){
    //int matrix[N][N];
    int i, j;
    int i2, j2;
    int n = len, n2 = len-1, n3 = len - 1, n4 = len-2;
    float iter = 0.0f;
    /*Test*/
    for(i = 0; i < len; ++i){
        for(j = 0; j < len; ++j){
            matrix[i][j] = -1;
        }
    }
    int c = 0;
    int k1 = 0, k2 = 0;
    int k3 = 1, k4 = len-1;
    int k5 = len-2, k6 = len-1;
    int k7 = len-2, k8 = 0;
    for(iter = 1; n > 0;){
            for(j = k2; j < n; ++j){
                matrix[k1][j] = iter;
                //iter++;
            }
            k1++;
            k2++;
            n--;

            for(i = k3; i <= n2; ++i){
                matrix[i][k4] = iter;
                //iter++;
            }
            k3++;
            k4--;
            n2--;

            for(j = k5; j > k5-n3; --j){
                matrix[k6][j] = iter;
                //iter++;
            }
            k5--;
            k6--;
            n3-=2;

        
            for(i = k7; i > k7 - n4; --i){
                matrix[i][k8] = iter;
                //iter++;
            }
            k7--;
            k8++;
            n4-=2;

            iter += 1.5f;
    }
    //print_matrix(matrix);    
    printf("End\n");
    return 0;
}

int main(){

    

    
    float **M;
    int i, i2, i3;

    M = new float*[N];
    for(i = 0; i < N; ++i){
        M[i] = new float[N];
    }

    ylitka(M, N);
    print(M, N);

    float *buffer = new float[N * N];
    for(i = 0; i < N; ++i){
        for(i2 = 0; i2 < N; ++i2){
            //M[i][i2] = i * X + i2;
        }
    }
    //print(M);

    std::cout<<"End\n";
    return 0;
}
