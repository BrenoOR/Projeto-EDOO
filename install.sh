#!/usr/bin/env bash
set -e

echo "Instalando dependencias do MINECIn..."

echo "Apt update ..."
sudo apt-get update -qq

echo "Instalando g++ e build-essential ..."
sudo apt-get install -y g++ build-essential

echo "Instalando libjsoncpp-dev ..."
sudo apt-get install -y libjsoncpp-dev

echo "Instalando libspdlog-dev ..."
sudo apt-get install -y libspdlog-dev

echo "Instalando bibliotecas OpenGL ..."
sudo apt-get install -y libglfw3-dev libgl-dev libglm-dev libglew-dev

echo "Dependencias instaladas com sucesso!"
