
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






//Here We added the required Namespaces


using namespace std;



// define objects 

#define change_to_int stoi
#define change_to_string to_string
#define open_infile(name)  ifstream in_file(name)
#define close_infile in_file.close()
#define tt std::chrono::steady_clock::now()
#define dff std::chrono::duration_cast<std::chrono::milliseconds>
#define WHL while


//The code is written Below 


void Parallel_LU_Decomposition_OpenMp(int Size,int *Perm,DD **Mat ,DD **Lower , DD **Upper,int num_threads){
    omp_set_num_threads(num_threads);

        //here we iterate for each column
        for(int col=0;col<Size;col++){

            DD Max_val=0.0;
            int swap_index;
            for(int row=col;row<Size;row++){
                     if(Max_val<abs(Mat[row][col])){

                        Max_val=abs(Mat[row][col]);
                        swap_index=row;
                    }

            
            }
            if(Max_val==0.0){
                cout<<"Given Matrix is Singular"<<endl;
                return;
            }

            //Swapping in the Permutation Matrix
            swap(Perm[col],Perm[swap_index]);

            #pragma omp parallel
        {
            #pragma omp for nowait
            for(int a=0;a<Size;a++){

                swap(Mat[col][a],Mat[swap_index][a]);
            }

            #pragma omp for
            for(int a=0;a<col;a++){

               DD temp = *(*(Lower + col) + a);
      *(*(Lower + col) + a) = *(*(Lower + swap_index) + a);
      *(*(Lower + swap_index) + a) = temp;
            }

            Upper[col][col]=Mat[col][col];

            #pragma omp for
            for(int a=col+1;a<Size;a++){

                *(*(Lower + a) + col) = *(*(Mat + a) + col) / Upper[col][col];
                *(*(Upper + col) + a) = *(*(Mat + col) + a);

               
            }
              
            #pragma omp for collapse(2)  
            for(int a=col+1;a<Size;a++){

                for(int b=col+1;b<Size;b++){

                    Mat[a][b]=Mat[a][b]-Lower[a][col]*Upper[col][b];
                }
            }
            

        }



        }

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

void intialize_space(int Size,DD **&Mat,DD **&Lower,DD **&Upper,int *&Perm,SS given_input_file)
{


open_infile(given_input_file);

int a=0;int b=0;
WHL(a<Size){
    b=0;
    WHL(b<Size){
        in_file>>Mat[a][b];
        b++;
    }
    a++;
}


close_infile;

a=0;b=0;
WHL(a<Size){
    b=0;
    WHL(b<Size){
        Lower[a][b] = (a == b) ? 1.0 : 0.0;
        b++;
    }
    a++;
}



a=0;b=0;
WHL(a<Size){
    b=0;
    WHL(b<Size){
        Upper[a][b]=0.0;
        b++;
    }
    a++;
}


a=0;
WHL(a<Size){
    Perm[a]=a;
    a++;
}





}


void write_into_file(int Size,DD **&Lower,DD **&Upper,int *&Perm,int num_threads){

SS Lower_trianle_mat="./output/OpenMp_Lower_"+change_to_string(Size)+"_"+change_to_string(num_threads)+".mat";

ofstream out1(Lower_trianle_mat);

int a=0;int b=0;

out1<<fixed<<setprecision(20);

WHL(a<Size){
    b=0;
    WHL(b<Size){
        out1<<Lower[a][b]<<" ";
        b++;
    }
    a++;
    out1<<endl;
}



out1.close();


SS Upper_trianle_mat="./output/OpenMp_Upper_"+change_to_string(Size)+"_"+change_to_string(num_threads)+".mat";

ofstream out2(Upper_trianle_mat);
a=0;b=0;

out2<<fixed<<setprecision(20);

WHL(a<Size){
    b=0;
    WHL(b<Size){
        out2<<Upper[a][b]<<" ";
        b++;
    }
    a++;
    out2<<endl;
}


out2.close();

SS Perm_mat="./output/OpenMp_Perm_"+change_to_string(Size)+"_"+change_to_string(num_threads)+".mat";

ofstream out3(Perm_mat);
a=0;
WHL(a<Size){
    out3<<Perm[a]<<" ";
    a++;
   
}

out3<<endl;


out3.close();
}








int main(int argc,char* argv[]){

SS given_input_file=argv[1];  

DD **Mat, **Lower, **Upper;
int *Perm;

int Size=change_to_int(argv[2]);



//create

create_space(Size,Mat,Lower,Upper,Perm);




//intialize

intialize_space(Size,Mat,Lower,Upper,Perm,given_input_file);





int num_threads=change_to_int(argv[3]);




    auto starting = tt;

    Parallel_LU_Decomposition_OpenMp(Size,Perm,Mat,Lower,Upper,num_threads);
    

    auto ending = tt;

    auto differnce = dff(ending - starting);
    cout << "Total Time :: " << differnce.count() << " ms" << endl;

    write_into_file(Size,Lower,Upper,Perm,num_threads);
   


   
// delete
free_space(Size,Mat,Lower,Upper,Perm);

    return 0;
}

