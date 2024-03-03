#!/bin/bash

# Nome do arquivo de saída Excel
output_file="./testes.xlsx"

# Cria um arquivo Excel vazio para armazenar os resultados
echo "Instruções Ciclos Cache_References Cache_Misses" > $output_file

# Loop para executar o comando 10 vezes
for i in {1..3}
do
    # Nome do arquivo de saída temporário do programa
    programa_output_temp_file="./output_fast$i.temp.txt"

    # Comando a ser executado, redirecionando a saída para o arquivo temporário do programa
    command="perf stat -B -e instructions:u,cycles:u,cache-references:u,cache-misses:u ./fast.intel --nthreads 1 --class tiny > $programa_output_temp_file 2>&1"

    # Executa o comando
    eval $command

    # Adiciona apenas as estatísticas de desempenho ao arquivo Excel
    cat $programa_output_temp_file | grep 'instructions\|cycles\|cache-references\|cache-misses' >> $output_file

    echo "Execução $i concluída. Resultados adicionados a $output_file"
done

echo "Resultados dos testes foram salvos em $output_file"
