#!/bin/bash

iterations=100
#./main_all.out [K_MAX_ITER] [N_EXECUTIONS/RUNS] [N_LENGHT_MATRIX_AND_VECTOR] [N_THREAD]
for prog in "sequential" "par_chunks" "par_chunks_threadpinned" "par_cyc" "par_ff"; do
  for size in 500 5000 20000; do
      for((j=0;j<5;j++)); do

        if [ "$prog" = "sequential" ]; then
            ./sequential.out ${size} ${iterations} 0
        fi

        if [ "$prog" = "par_chunks" ]; then
            for((i=1;i<33;i*=2)); do
              ./parallel_chunks_barrier.out $size $iterations $i 0
            done
        fi

        if [ "$prog" = "par_chunks_threadpinned" ]; then
            for((i=1;i<33;i*=2)); do
                ./parallel_chunks_barrier_threadpinned.out $size $iterations $i 0
            done

        fi

        if [ "$prog" = "par_cyc" ]; then
            for((i=1;i<33;i*=2)); do
                ./parallel_row_cyclic_barrier.out $size $iterations $i 0
            done
        fi

        if [ "$prog" = "par_ff" ]; then
            for((i=1;i<33;i*=2)); do
                ./ff_parallel.out $size $iterations $i 0
            done
        fi
      done
  done
done

