#!/bin/bash

# Lista de pastas
pastas=("FAST" "FN" "GF" "IS" "KM" "LU")

# Loop para percorrer cada pasta
for pasta in "${pastas[@]}"
do
    # Entrar na pasta
    cd "$pasta"
    
    # Executar o script
    ./script.sh
    
    # Voltar para a pasta anterior
    cd ..
done
