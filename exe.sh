#!/bin/bash

echo "executando testes 1t"

for i in `seq 1 60`
do
echo "----------------------------" >>result/graphStm1t.txt
./graph.out 1 >>result/graphStm1t.txt 
done


echo "executando testes 2t"

for i in `seq 1 60`
do
echo "----------------------------" >>result/graphStm2t.txt
./graph.out 2 >>result/graphStm2t.txt
done



echo "executando testes 4t"

for i in `seq 1 60`
do
echo "----------------------------" >>result/graphStm4t.txt
./graph.out 4 >>result/graphStm4t.txt 
done



echo "executando testes 8t"

for i in `seq 1 60`
do
echo "----------------------------" >>result/graphStm8t.txt
./graph.out 8 >>result/graphStm8t.txt
done