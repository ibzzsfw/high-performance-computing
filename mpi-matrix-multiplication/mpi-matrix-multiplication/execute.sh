for i in {1..12}; do
  echo "Number of processes: ${i}"
  for j in {1..7}; do
    mpirun -n "${i}" -hostfile ../hosts.txt ./multiplication ./materials/matAlarge.txt ./materials/matBlarge.txt
  done
done