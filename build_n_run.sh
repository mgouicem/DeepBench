#!/bin/bash

#set -x

workdir=$(pwd)


#takes the parameters from the command line
eval "$@"

input_h=${input_h:-input_topologies.h}
# detects the number of physical cores
nb_cores=${nb_cores:-$(lscpu | awk '/Socket/{ print $2*nc } /Core/{ nc=$4} ')}
#detects the flat mode but looking for a node without cores
pre_cmd=$(numactl --hardware | awk '/node [0-9] cpus:$/ {print "numactl -m "$2; quit}')
#selects which test to run
run=${run:-mkl,mkldnn,libxsmm}

tools_dir=/nfs/site/proj/mkl/mirror/NS/MKLQA/tools/setenv
export MKLDNNROOT=/export/users/mgouicem/ipl_mkl_dnn-master/install/
export LD_LIBRARY_PATH=$MKLDNNROOT/lib:$LD_LIBRARY_PATH
export LIBXSMMROOT=/export/users/mgouicem/libxsmm

source $tools_dir/setup_lnx_comp.sh 32e gnu491
source $tools_dir/setup_lnx_comp.sh 32e 170
source $tools_dir/setup_lnx_mpi.sh 32e 2017
source ~/setup_mkl_nightly.sh mkl2017u3 latest


if [[ $(lscpu | awk '/Thread/ {print $4}') > 1 ]]
then
    export KMP_AFFINITY=granularity=fine,compact,1,0
else
    export KMP_AFFINITY=granularity=fine,compact 
fi

function run_bench_mkl {
    local library_tested=$1
    local output_file=$2

    for num_threads in $nb_cores
    do
        export OMP_NUM_THREADS=${num_threads}
        cat <<EOF 
------------------------
$library_tested  Convolution - ${num_threads} threads
started...
EOF

        $pre_cmd ./std_conv_bench 0 --csv-output >> $workdir/logs/$output_file
        
        cat <<EOF
done
--------------
EOF
    done
}

timestamp=$(date +%Y%m%d_%H%M%S)

cd $workdir/code/intel/convolution/mkl_conv

## Pure MKL bench
if $(echo $run | grep -wq mkl)
then
    make -B clean all INPUT_H=$input_h CONVLIB=MKL CPPFLAGS="$CPPFLAGS"
    run_bench_mkl "MKL" "${timestamp}-mkl${file_suffix}.csv"
fi

## MKL-DNN bench
if $(echo $run | grep -wq mkldnn)
then
    make -B clean all INPUT_H=$input_h CONVLIB=MKLDNN MKLDNNROOT=$MKLDNNROOT CPPFLAGS="$CPPFLAGS"
    run_bench_mkl "MKL-DNN" "${timestamp}-mkldnn${file_suffix}.csv"
fi

# libxsmm bench
if $(echo $run | grep -wq libxsmm)
then
    make -B clean all INPUT_H=$input_h CONVLIB=LIBXSMM LIBXSMMROOT=$LIBXSMMROOT CPPFLAGS="$CPPFLAGS"
    run_bench_mkl "LIBXSMM" "${timestamp}-libxsmm${file_suffix}.csv"
fi
