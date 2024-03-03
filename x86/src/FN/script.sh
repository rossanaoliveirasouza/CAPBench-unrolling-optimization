#!/bin/bash

# Nome do arquivo de saída Excel
output_file="./compilation_times.xlsx"

# Cria um arquivo Excel vazio para armazenar os resultados
echo "Tempo de Compilação (segundos)" > $output_file

# Loop para compilar o programa 10 vezes
for i in {1..10}
do
    # Nome do arquivo de saída temporário do tempo de compilação
    compilation_time_temp_file="./compilation_time_$i.temp.txt"

    # Comando a ser executado, redirecionando a saída para o arquivo temporário do tempo de compilação
    command="time gcc friendly-numbers.c balance.c main.c -Wall -Wextra -Werror -O3 -fno-unroll-loops -I /home/rosana/Documentos/TCC/testes/CAPBenchmarks-unrolling-optimization/x86/include -o /home/rosana/Documentos/TCC/testes/CAPBenchmarks-unrolling-optimization/x86/bin/fn.intel /home/rosana/Documentos/TCC/testes/CAPBenchmarks-unrolling-optimization/x86/lib/libcapb.a -lm -fopenmp > $compilation_time_temp_file 2>&1"

    # Executa o comando
    eval $command

    # Extrai o tempo de compilação e armazena no arquivo Excel
    compilation_time=$(tail -n 3 $compilation_time_temp_file | head -n 1 | cut -d " " -f 3)
    echo "$compilation_time" >> $output_file

    echo "Compilação $i concluída. Tempo de compilação adicionado a $output_file"

    # Remove o arquivo temporário do tempo de compilação
    rm $compilation_time_temp_file
done

echo "Tempos de compilação foram salvos em $output_file"