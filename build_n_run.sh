#!/bin/bash

workdir=/project/mgouicem/MKL-DNN/DeepBench/
nb_cores=${nb_cores:-$(lscpu | awk '/Socket/{ print $2*nc } /Core/{ nc=$4} ')}
input_h=${input_h:-input_topologies.h}


source /nfs/site/proj/mkl/mirror/NS/MKLQA/tools/setenv/setup_lnx_comp.sh 32e gnu491
source /nfs/site/proj/mkl/mirror/NS/MKLQA/tools/setenv/setup_lnx_comp.sh 32e 170
source /nfs/site/proj/mkl/mirror/NS/MKLQA/tools/setenv/setup_lnx_mpi.sh 32e 2017

source ~/setup_mkl_nightly.sh mkl2017u3 latest

if [[ $(lscpu | awk '/Thread/ {print $4}') > 1 ]]
then
    export KMP_AFFINITY=granularity=fine,compact,1,0
else
    export KMP_AFFINITY=granularity=fine,compact 
fi

MKLDNNROOT=/project/mgouicem/MKL-DNN/ipl_mkl_dnn-master/install/
export LD_LIBRARY_PATH=$MKLDNNROOT/lib:$LD_LIBRARY_PATH

LIBXSMMROOT=/project/mgouicem/MKL-DNN/libxsmm

function run_bench_mkl {
    local library_tested=$1
    local output_file=$2

    for num_threads in "$nb_cores"
    do
        export OMP_NUM_THREADS=${num_threads}
        cat <<EOF 
------------------------
$library_tested  Convolution - ${num_threads} threads
started...
EOF

        ./std_conv_bench 0 --csv-output >> $output_file
        
        cat <<EOF
done
--------------
EOF
    done
}

timestamp=$(date +%Y%m%d_%H%M%S)

# MKL bench
cd $workdir/code/intel/convolution/mkl_conv

## Pure MKL bench
make -B clean all INPUT_H=$input_h CONVLIB=MKL
run_bench_mkl "MKL" mkl-${timestamp}.csv

## MKL-DNN bench
make -B clean all INPUT_H=$input_h CONVLIB=MKLDNN
run_bench_mkl "MKL-DNN" "mkldnn-${timestamp}.csv"

# libxsmm bench
make -B clean all INPUT_H=$input_h CONVLIB=LIBXSMM LIBXSMMROOT=$LIBXSMMROOT
run_bench_mkl "LIBXSMM" "libxsmm-${timestamp}.csv"
