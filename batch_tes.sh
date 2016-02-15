#!/bin/bash
for run in {1..100}
do
  ./shared_mem_test 4000 1 >> result_Process.txt
done
for run in {1..100}
do
  ./shared_mem_test 4000 0 >> result_Process.txt
done

for run in {1..100}
do
  ./shared_mem_test 16000 1 >> result_Process1.txt
done
for run in {1..100}
do
  ./shared_mem_test 16000 0 >> result_Process1.txt
done

for run in {1..100}
do
  ./shared_mem_test 64000 1 >> result_Process2.txt
done
for run in {1..100}
do
  ./shared_mem_test 64000 0 >> result_Process2.txt
done

for run in {1..100}
do
  ./shared_mem_test 256000 1 >> result_Process3.txt
done
for run in {1..100}
do
  ./shared_mem_test 256000 0 >> result_Process3.txt
done

for run in {1..100}
do
  ./shared_mem_test 1024000 1 >> result_Process4.txt
done
for run in {1..100}
do
  ./shared_mem_test 1024000 0 >> result_Process4.txt
done

for run in {1..100}
do
  ./shared_mem_test 4096000 1 >> result_Process5.txt
done
for run in {1..100}
do
  ./shared_mem_test 4096000 0 >> result_Process5.txt
done

for run in {1..100}
do
  ./shared_mem_test 16384000 1 >> result_Process6.txt
done
for run in {1..100}
do
  ./shared_mem_test 16384000 0 >> result_Process6.txt
done

for run in {1..100}
do
  ./shared_mem_test 65536000 1 >> result_Process7.txt
done
for run in {1..100}
do
  ./shared_mem_test 65536000 0 >> result_Process7.txt
done


for run in {1..100}
do
  ./shared_mem_test 262144000 1 >> result_Process8.txt
done
for run in {1..100}
do
  ./shared_mem_test 262144000 0 >> result_Process8.txt
done


for run in {1..100}
do
  ./shared_mem_test 524288000 1 >> result_Process9.txt
done
for run in {1..100}
do
  ./shared_mem_test 524288000 0 >> result_Process9.txt
done
