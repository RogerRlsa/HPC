#!/bin/bash
#sudo cpufreq-set -r -g powersave
#sudo cpufreq-set -r -g performance
#rm *.csv
#L1
#echo "L1 Cache"
#for ((part = 500; part <= 1000; part+=10))
#do
#	for ((s = 1; s <= 10; s+=1))#
#	#do
#		echo "$part  step: $s"
#		./memory.exec 3145728 1024 > /dev/null
#		./n-bodies-1.0.exec 100 $part L1.sequencial.csv 0 > /dev/null
#	done
#done

#echo "L2 Cache"
#for ((part = 6000; part <= 7000; part+=100))
#do#
#	for ((s = 1; s <= 10; s+=1))
#	do
#		echo "$part  step: $s"
#		./memory.exec 3145728 1024 > /dev/null
#		./n-bodies-1.0.exec 100 $part L2.sequencial.csv 0 > /dev/null
#	done
#done
echo "L1 Cache - OpenMP"
for ((part = 500; part <= 1000; part+=10))
do
	for ((s = 1; s <= 10; s+=1))
	do
		echo "$part  step: $s"
		./memory.exec 3145728 1024 > /dev/null
		./n-bodies-2.0.exec 100 $part L1.openMP-100S.csv 0 > /dev/null
	done
done

echo "L1 Cache - OpenMP"
for ((part = 500; part <= 1000; part+=10))
do
	for ((s = 1; s <= 10; s+=1))
	do
		echo "$part  step: $s"
		./memory.exec 3145728 1024 > /dev/null
		./n-bodies-2.0.exec 1000 $part L1.openMP-1000S.csv 0 > /dev/null
	done
done

echo "L1 Cache - OpenMP"
for ((part = 500; part <= 1000; part+=10))
do
	for ((s = 1; s <= 10; s+=1))
	do
		echo "$part  step: $s"
		./memory.exec 3145728 1024 > /dev/null
		./n-bodies-2.0.exec 10000 $part L1.openMP-10000S.csv 0 > /dev/null
	done
done