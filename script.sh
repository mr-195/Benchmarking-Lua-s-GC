#!/bin/bash




# rm -rf callgrind executables images perf
mkdir callgrind executables images perf


# generating executables
echo "Generating executables....."
gcc -o full fullgc.c -llua -lm -ldl
gcc -o generational generationalgc.c -llua -lm -ldl
gcc -o incremental incrementalgc.c -llua -lm -ldl


# generating callgrind output files
echo "Generating call grind output files....."
valgrind --tool=callgrind --callgrind-out-file=callgrind/full.callgrind.out ./full 
valgrind --tool=callgrind --callgrind-out-file=callgrind/generational.callgrind.out ./generational 
valgrind --tool=callgrind --callgrind-out-file=callgrind/incremental.callgrind.out ./incremental

echo "Generating graphs....."
gprof2dot -f callgrind callgrind/full.callgrind.out | dot -Tpng -o images/full.png 
gprof2dot -f callgrind callgrind/generational.callgrind.out | dot -Tpng -o images/generational.png 
gprof2dot -f callgrind callgrind/incremental.callgrind.out | dot -Tpng -o images/incremental.png 


# echo "Generating perf analysis......"
# sudo perf stat ./executables/full > perf/full.txt
# sudo perf stat ./executables/incremental > perf/incremental.txt
# sudo perf stat ./executables/generational > perf/generational.txt