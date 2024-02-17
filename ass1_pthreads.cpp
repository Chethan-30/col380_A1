
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






//Here We added the required Namespaces


using namespace std;



// define objects 

#define change_to_int stoi
#define change_to_string to_string
#define open_infile(name)  ifstream in_file(name)
#define close_infile in_file.close()
#define tt std::chrono::steady_clock::now()
#define dff std::chrono::duration_cast<std::chrono::milliseconds>
#define exiting pthread_exit(NULL)
#define WHL while



//The code is written Below 



struct contentTh{int Size;DD **Mat ;DD **Lower ; DD **Upper;int col;int swap_index; int id;int var1;int var2;};


void initialize_thread(vector<contentTh> &thread_var,int Size,DD **&Mat ,DD **&Lower ,DD **&Upper,int col,int swap_index, int id,int var1,int var2){

    thread_var[id].id=id;thread_var[id].Upper=Upper;thread_var[id].Lower=Lower;thread_var[id].Mat=Mat;thread_var[id].swap_index=swap_index;thread_var[id].var1=var1;thread_var[id].var2=var2;thread_var[id].col=col;thread_var[id].Size=Size;
}


void* swappingTh(void* temp){

    contentTh* threadvar=(contentTh*)temp;    

    int ps1=(threadvar->id)*(threadvar->var1),pe1=min((threadvar->id+1)*(threadvar->var1),threadvar->Size),ps2=(threadvar->id)*(threadvar->var2),pe2=min((threadvar->id+1)*(threadvar->var2),threadvar->col);

    int a=ps1;

    WHL(a<pe1){
        swap(threadvar->Mat[threadvar->col][a],threadvar->Mat[threadvar->swap_index][a]);
        a++;
    }

    
    a=ps2;
    WHL(a<pe2){
        swap(threadvar->Lower[threadvar->col][a],threadvar->Lower[threadvar->swap_index][a]);
        a++;
    }

   exiting;
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
void*  LUTh(void* temp){
    

      contentTh* threadvar = (contentTh*)temp;



int id_times_var1 = threadvar->id * threadvar->var1;


int col_plus_one = threadvar->col + 1;

int ps1 = id_times_var1 + col_plus_one;
int pe1 = min((threadvar->id + 1) * threadvar->var1 + col_plus_one, threadvar->Size);


      int a=ps1;

      WHL(a<pe1)
      {
       int col = threadvar->col;
double divisor = threadvar->Upper[col][col];
threadvar->Lower[a][col] = threadvar->Mat[a][col] / divisor;
threadvar->Upper[col][a] = threadvar->Mat[col][a];

      a++;
      }
    exiting;
    
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

void*  MatTh(void* temp){
   contentTh* threadvar = (contentTh*)temp;

int id_times_var1 = threadvar->id * threadvar->var1;
int col_plus_1 = threadvar->col + 1;
int id_plus_1_times_var1 = (threadvar->id + 1) * threadvar->var1;

int ps1 = id_times_var1 + col_plus_1;
int pe1 = min(id_plus_1_times_var1 + col_plus_1, threadvar->Size);


      int a=ps1;
      int b=0;
      WHL(a<pe1)
      {
        b=threadvar->col;
        WHL(b<threadvar->Size){
            threadvar->Mat[a][b]=threadvar->Mat[a][b]-(threadvar->Lower[a][threadvar->col]*threadvar->Upper[threadvar->col][b]);

            b++;
        }
      a++;
      }

 exiting;
}







void Parallel_LU_Decomposition_Pthreads(int Size,int *&Perm,DD **&Mat ,DD **&Lower , DD **&Upper,int num_threads){

        //here we iterate for each column

        //creating Threads
        pthread_t thread[num_threads];
        vector<contentTh> thread_p(num_threads);

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
            
            for(int a=0;a<num_threads;a++){int var1=(Size+num_threads-1)/num_threads;int var2=(col+num_threads-1)/num_threads;initialize_thread(thread_p,Size,Mat,Lower,Upper,col,swap_index,a,var1,var2);pthread_create(&thread[a],NULL,swappingTh,(void*)&thread_p[a]);}
            
            int a=0;
            WHL(a<num_threads){
                pthread_join(thread[a],NULL);
                a++;
            }
            Upper[col][col]=Mat[col][col];
            for(int a=0;a<num_threads;a++){int var1=(Size+num_threads-col-2)/num_threads;int var2=0;initialize_thread(thread_p,Size,Mat,Lower,Upper,col,swap_index,a,var1,var2);pthread_create(&thread[a],NULL,LUTh,(void*)&thread_p[a]);}
             a=0;
            WHL(a<num_threads){
                pthread_join(thread[a],NULL);
                a++;
            }
            for(int a=0;a<num_threads;a++){int var1=(Size+num_threads-col-2)/num_threads;int var2=0;initialize_thread(thread_p,Size,Mat,Lower,Upper,col,swap_index,a,var1,var2);pthread_create(&thread[a],NULL,MatTh,(void*)&thread_p[a]);}
             a=0;
            WHL(a<num_threads){
                pthread_join(thread[a],NULL);
                a++;
            }

            
            

            
            

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

SS Lower_trianle_mat="./output/pthreads_Lower_"+change_to_string(Size)+"_"+change_to_string(num_threads)+".mat";

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


SS Upper_trianle_mat="./output/pthreads_Upper_"+change_to_string(Size)+"_"+change_to_string(num_threads)+".mat";

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

SS Perm_mat="./output/pthreads_Perm_"+change_to_string(Size)+"_"+change_to_string(num_threads)+".mat";

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

    Parallel_LU_Decomposition_Pthreads(Size,Perm,Mat,Lower,Upper,num_threads);
    

    auto ending = tt;

    auto differnce = dff(ending - starting);
    cout << "Total Time :: " << differnce.count() << " ms" << endl;

    write_into_file(Size,Lower,Upper,Perm,num_threads);
  


   
// delete
free_space(Size,Mat,Lower,Upper,Perm);

    return 0;
}

