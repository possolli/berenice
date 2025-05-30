#!/bin/bash

# Nome do executável
EXECUTAVEL="bere"

# Diretórios
SRC_DIR="src"
INC_DIR="include"
BUILD_DIR="build"

# Arquivos-fonte
FONTES=$(find "$SRC_DIR" -name "*.c")

# Compilador e flags
COMPILADOR="gcc"
CFLAGS="-Wall -I$INC_DIR"

# Verifica se o diretório build existe, senão cria
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
    echo "[✔] Pasta '$BUILD_DIR' criada."
fi

# Compila os arquivos
echo "[ℹ️] Compilando projeto..."
$COMPILADOR $CFLAGS $FONTES -o "$BUILD_DIR/$EXECUTAVEL"

# Verifica o sucesso
if [ $? -eq 0 ]; then
    echo "[✅] Compilação concluída com sucesso!"
    echo "➡️  Execute com: ./$BUILD_DIR/$EXECUTAVEL"
else
    echo "[❌] Erro na compilação."
fi
