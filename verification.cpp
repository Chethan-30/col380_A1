
// Here We defined the required names and files


#define DD double
#define ll long
#define SS string 
#define thread_include  <pthread.h>
#define total_include <bits/stdc++.h>
#define time_include <time.h>
#define sec_include <chrono>
#define openmp_include <omp.h>




// Here We included the required names and files


#include thread_include
#include total_include
#include time_include
#include sec_include
#include openmp_include
#include <iomanip> 
#include <cmath>


//Here We added the required Namespaces


using namespace std;

#define change_to_int stoi
#define change_to_string to_string
#define open_infile(name)  ifstream in_file(name)
#define close_infile in_file.close()
#define tt std::chrono::steady_clock::now()
#define dff std::chrono::duration_cast<std::chrono::milliseconds>
#define exiting pthread_exit(NULL)
#define WHL while
#define rd  uniform_real_distribution<double>


void create_verify_space(DD ** &PP ,DD **&PA , DD **&LU,int Size){

    PP = (DD **)malloc(Size * sizeof(DD *));
PA = (DD **)malloc(Size * sizeof(DD *));
LU = (DD **)malloc(Size * sizeof(DD *));

for (int i = 0; i < Size; i++) {
    PP[i] = (DD *)malloc(Size * sizeof(DD));
    PA[i] = (DD *)malloc(Size * sizeof(DD));
    LU[i] = (DD *)malloc(Size * sizeof(DD));
}



}
void initialize_verify_space(DD ** &PP ,DD **&PA , DD **&LU,int Size){

   int a=0,b=0;
WHL(a<Size){
    b=0;
    WHL(b<Size){
        PP[a][b]=0.0;
        b++;
    }
    a++;
}

a=0,b=0;
WHL(a<Size){
    b=0;
    WHL(b<Size){
        PA[a][b]=0.0;
        b++;
    }
    a++;
}

a=0,b=0;
WHL(a<Size){
    b=0;
    WHL(b<Size){
        LU[a][b]=0.0;
        b++;
    }
    a++;
}


}

void verification(int Size,int *Perm,DD **Mat ,DD **Lower , DD **Upper){

    DD **PP, **PA, **LU;
    create_verify_space(PP,PA,LU,Size);
    initialize_verify_space(PP,PA,LU,Size);
    for(int i=0;i<Size;i++){
        PP[i][Perm[i]]=1;
    }

    int a=0,b=0,c=0;
    WHL(a<Size){
        b=0;
        WHL(b<Size){
            c=0;
            WHL(c<Size){
                 PA[a][b]+=PP[a][c]*Mat[c][b];
                c++;
            }
            b++;
        }
        a++;
    }
       a=0,b=0,c=0;
    WHL(a<Size){
        b=0;
        WHL(b<Size){
            c=0;
            WHL(c<Size){
                LU[a][b]+=Lower[a][c]*Upper[c][b];

                c++;
            }
            b++;
        }
        a++;
    }




    double res_sum=0.0;

    a=0;b=0;
    WHL(a<Size){
        b=0;
        double sum = 0;
        WHL(b<Size){

            sum += (PA[a][b] - LU[a][b]) * (PA[a][b] - LU[a][b]);

            b++;
        }

        res_sum+= sqrt(sum);
        a++;
    }



    cout<<"Check Sum ::: "<<res_sum<<endl;

    for (int i = 0; i < Size; i++) {
    free(PP[i]);
    free(PA[i]);
    free(LU[i]);
     }
free(PP);
free(PA);
free(LU);



}


void create_space(int Size,DD **&Mat,DD **&Lower,DD **&Upper,int *&Perm){

Perm = (int *)malloc(Size * sizeof(int));

Mat = (DD **)malloc(Size * sizeof(DD *));
Lower = (DD **)malloc(Size * sizeof(DD *));
Upper = (DD **)malloc(Size * sizeof(DD *));

for (int i = 0; i < Size; i++) {
    Mat[i] = (DD *)malloc(Size * sizeof(DD));
    Lower[i] = (DD *)malloc(Size * sizeof(DD));
    Upper[i] = (DD *)malloc(Size * sizeof(DD));
}

  

}




void intialize_space(int Size,DD **&Mat,DD **&Lower,DD **&Upper,int *&Perm,SS var_p,SS var_mat,SS var_Lower,SS var_Upper)
{



ifstream in_p(var_p);
ifstream in_mat(var_mat);
ifstream in_Lower(var_Lower);
ifstream in_Upper(var_Upper);
int a=0;int b=0;
WHL(a<Size){
    b=0;
    WHL(b<Size){
        in_mat>>Mat[a][b];
        b++;
    }
    a++;
}




a=0; b=0;
WHL(a<Size){
    b=0;
    WHL(b<Size){
        in_Lower>>Lower[a][b];
        b++;
    }
    a++;
}



a=0; b=0;
WHL(a<Size){
    b=0;
    WHL(b<Size){
        in_Upper>>Upper[a][b];
        b++;
    }
    a++;
}


a=0;
WHL(a<Size){
    in_p>>Perm[a];
    a++;
}

in_p.close();
in_mat.close();
in_Lower.close();
in_Upper.close();




}


void free_space(int Size,DD **Mat,DD **Lower,DD **Upper,int *Perm){

    for (int i = 0; i < Size; i++) {
    free(Mat[i]);
    free(Lower[i]);
    free(Upper[i]);
     }
free(Mat);
free(Lower);
free(Upper);
free(Perm);

}


int main(int argc, char *argv[]){

    int Size=change_to_int(argv[1]);
    SS var_p=argv[2];
    SS var_mat=argv[3];
    SS var_Lower=argv[4];
    SS var_Upper=argv[5];

    DD **Mat, **Lower, **Upper;
    int *Perm;
    create_space(Size,Mat,Lower,Upper,Perm);
    intialize_space(Size,Mat,Lower,Upper,Perm,var_p,var_mat,var_Lower,var_Upper);
    verification(Size,Perm,Mat,Lower,Upper);
    
   free_space(Size,Mat,Lower,Upper,Perm);
    
    

    return 0;
}



