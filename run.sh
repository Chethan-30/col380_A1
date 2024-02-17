if [ $1 == "Random" ] 
then
   ./random $2 

elif [ $1 == "Openmp" ] 
then
    ./ass1_openmp $2 $3 $4

elif [ $1 == "Pthread" ] 
then
    ./ass1_pthreads $2 $3 $4

elif [ $1 == "Nonparallel" ] 
then
    ./ass1_Nonparallel $2 $3 $4

elif [ $1 == "Verification" ] 
then
    ./verification $2 $3 $4 $5 $6

else
 echo "Argument not found"
 
fi