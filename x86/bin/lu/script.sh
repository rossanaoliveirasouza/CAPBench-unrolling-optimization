#!/bin/bash

# Nome do arquivo de saída para dados brutos do perf
raw_data_file="./dados_brutos_lu.txt"

# Nome do arquivo de saída para a planilha CSV
output_file="./resultados_lu.csv"

# Cria um arquivo de texto vazio para armazenar os dados brutos do perf
> $raw_data_file

# Loop para executar o comando 10 vezes
for i in {1..20}
do
    # Nome do arquivo de saída do programa
    programa_output_file="./output_lu_$i.txt"

    # Comando a ser executado, redirecionando a saída para o arquivo de dados brutos do perf
    command="perf stat -o $programa_output_file -B -e instructions:u,cycles:u,cache-references:u,cache-misses:u,branches:u ./lu.intel --nthreads 8 --class standard > /dev/null 2>&1"

    # Executa o comando
    eval $command

    # Concatena os dados brutos do perf ao arquivo de dados brutos
    cat $programa_output_file >> $raw_data_file

    echo "Execução $i concluída. Dados brutos adicionados a $raw_data_file"
done

# Escreve os dados processados em um arquivo CSV
echo "Instruções;Ciclos;Cache_References;Cache_Misses;Branches;Tempo_Execucao;Instrucoes_por_Ciclo" > $output_file
awk '/instructions/ {instrucoes=$1} /cycles/ {ciclos=$1} /cache-references/ {cache_refs=$1} /cache-misses/ {cache_misses=$1} /branches/ {branches=$1} /seconds time elapsed/ {tempo_exec=$1; tempo_exec = tempo_exec / 1; instr_por_ciclo = instrucoes / ciclos; print instrucoes ";" ciclos ";" cache_refs ";" cache_misses ";" branches ";" tempo_exec ";" instr_por_ciclo}' $raw_data_file >> $output_file

echo "Resultados dos testes foram salvos em $output_file"
