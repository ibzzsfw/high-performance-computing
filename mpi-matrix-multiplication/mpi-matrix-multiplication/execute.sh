for ((i = 1; i <= 15; i++)); do
  for ((j = 1; j <= 7; j++)); do
    mpirun -n ${i} -hostfile ../hosts.txt ./multiplication ./materials/matAsmall.txt ./materials/matBsmall.txt
  done
done
