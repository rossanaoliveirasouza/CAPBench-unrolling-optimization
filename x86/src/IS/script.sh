#!/bin/bash

# Nome do arquivo CSV de saída
output_file="compilacao_is.csv"

# Cria um arquivo CSV vazio para armazenar os tempos de compilação
echo "Tempo de Compilação (segundos)" > $output_file

# Loop para compilar o programa 20 vezes
for i in {1..20}
do
    # Nome do arquivo de saída temporário do tempo de compilação
    compilation_time_temp_file="compilation_time_$i.temp.txt"

    # Comando a ser executado para compilar o programa e medir o tempo de compilação
    command="perf stat -o >(grep 'time elapsed' | awk '{print \$1}' >> $output_file) -B -- gcc quicksort.c darray.c bucket-sort.c main.c -Wall -Wextra -O3 -fno-unroll-loops -I /home/rossana.souza/CAPBench-unrolling-optimization/x86/include -o /home/rossana.souza/CAPBench-unrolling-optimization/x86/bin/is.intel /home/rossana.souza/CAPBench-unrolling-optimization/x86/lib/libcapb.a -lm -fopenmp"

    # Executa o comando e mede o tempo de compilação
    eval $command

    echo "Compilação $i concluída. Tempo de compilação adicionado a $output_file"
done

echo "Tempos de compilação foram salvos em $output_file"
