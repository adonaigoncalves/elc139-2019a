#!/bin/bash
#SBATCH -J adonaidoyle           # job name
#SBATCH -o adonaidoyle%j.out       # output file name (%j expands to jobID), this file captures standered output from the shell
#SBATCH -e adonaidoyle%j.err      # error file name (%j expands to jobID), this file captures standered errors genereted from the program
#SBATCH  --nodes  1        # total number of nodes requested
#SBATCH --ntasks-per-node 1 # total number cores requested per node. Using this option and --node option above you could fine tune resource requests.
#SBATCH -p qCDER            # partition --qCDER (to find out available partitions please run 'sinfo' command)
#SBATCH --mem-per-cpu=4000   # request specific amount of RAM per CPU, now since we request 16 cores, the total amount of memory avilable for the program is 48GB
#SBATCH --gres=gpu:1      # request gpus for the job,if needed, otherwise remove this line
#SBATCH -t 00:05:00       # run time (hh:mm:ss) - 5 minutes
 
## Included any modules that may be required for your job. in this example load MPI module
 
# execute any program
#to run MPI program
srun make
srun ./mandelbrot < mandelbrot.in