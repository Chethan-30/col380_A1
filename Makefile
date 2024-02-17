all :
	g++ ass1_Nonparallel.cpp -o ass1_Nonparallel
	g++ ass1_openmp.cpp -fopenmp -o ass1_openmp
	g++ ass1_pthreads.cpp -lpthread  -o ass1_pthreads
	g++ random.cpp -o random
	g++ verification.cpp -o verification

clean :
	rm -rf ass1_Nonparallel ass1_openmp ass1_pthreads random verification
	