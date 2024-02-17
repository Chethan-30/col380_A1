
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

#define change_to_int stoi
#define change_to_string to_string
#define open_infile(name)  ifstream in_file(name)
#define close_infile in_file.close()
#define tt std::chrono::steady_clock::now()
#define dff std::chrono::duration_cast<std::chrono::milliseconds>
#define exiting pthread_exit(NULL)
#define WHL while
#define rd  uniform_real_distribution<double>


#define SEED 123456L

int main(int argc, char *argv[]) {


    int Size = change_to_int(argv[1]);
  
   auto starting = tt;

    mt19937_64 rng(SEED);

    string name_of_file = "./output/Mat_"+to_string(Size)+".mat";

    ofstream out(name_of_file);

    
    int a=0;int b=0;
    WHL(a<Size){
        b=0;
        WHL(b<Size){
             rd dist(0.0, 1.0);

            double var_temp = abs(drand48());

            out<<var_temp<<" ";

            b++;
        }
        a++;

        out<<endl;
    }


    out.close();

   auto ending = tt;

    auto differnce = dff(ending - starting);

    cout << "Total Time :: " << differnce.count() << " ms" << endl;

    int Temp_var_1 = Size * Size;

    open_infile(name_of_file);

    int temp_var = 0;

    double val;

    WHL(in_file >> val)temp_var++;
    
    close_infile;

    std::cout << "Total Values :: " << temp_var << ", Inserted :: " << Temp_var_1 << std::endl;

    return 0;
}