#!/bin/bash

# Nome do arquivo de saída Excel
output_file="./km.xlsx"

# Cria um arquivo Excel vazio para armazenar os resultados
echo "Instruções Ciclos Cache_References Cache_Misses" > $output_file

# Loop para executar o comando 10 vezes
for i in {1..10}
do
    # Nome do arquivo de saída temporário do programa
    programa_output_temp_file="./output_km$i.temp.txt"

    # Comando a ser executado, redirecionando a saída para o arquivo temporário do programa
    command="perf stat -o >(grep 'instructions\|cycles\|cache-references\|cache-misses\|branches' >> $output_file) -B -e instructions:u,cycles:u,cache-references:u,cache-misses:u,branches:u ./km.intel --nthreads 1 --class large > $programa_output_temp_file 2>&1"

    # Executa o comando
    eval $command

    echo "Execução $i concluída. Resultados temporários adicionados a $output_file"
done

# Concatena os arquivos temporários de saída em um único arquivo Excel
cat ./output_km*.temp.txt >> $output_file

# Remove os arquivos temporários
rm ./output_km*.temp.txt

echo "Resultados dos testes foram salvos em $output_file"