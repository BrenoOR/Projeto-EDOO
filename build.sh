#!/usr/bin/env bash
set -e

SRC="src"
OUT="bin/minecin"
CXX="${CXX:-g++}"
CXXFLAGS="-std=c++17 -Wall -Wextra -I${SRC} -I/usr/include/jsoncpp -Iinclude"
LDFLAGS="-ljsoncpp -lspdlog -lfmt -lglfw -lGLEW -lGL"

mkdir -p bin

SOURCES=(
    "${SRC}/main.cpp"
    "${SRC}/mundo/Pedra.cpp"
    "${SRC}/mundo/Magnetita.cpp"
    "${SRC}/mundo/Cobre.cpp"
    "${SRC}/mundo/Ouro.cpp"
    "${SRC}/mundo/Muro.cpp"
    "${SRC}/mundo/Mapa.cpp"
    "${SRC}/entidades/Personagem.cpp"
    "${SRC}/sistemas/SistemaColisao.cpp"
    "${SRC}/telas/TelaFinal.cpp"
    "${SRC}/telas/TelaJogo.cpp"
    "${SRC}/telas/TelaHistoria.cpp"
    "${SRC}/telas/TelaInicio.cpp"
    "${SRC}/core/Jogo.cpp"
    "${SRC}/sim/ProvedorInputSim.cpp"
    "${SRC}/renderer/ShaderProgram.cpp"
    "${SRC}/renderer/SpriteBatch.cpp"
    "${SRC}/renderer/OpenGLRenderer.cpp"
    "${SRC}/renderer/Janela.cpp"
    "${SRC}/input/ManipuladorInputGLFW.cpp"
)

echo "Compilando MINECIn..."

echo "Criando folder de logs..."
mkdir -p logs

echo "Executando compilacao..."
${CXX} ${CXXFLAGS} "${SOURCES[@]}" -o "${OUT}" ${LDFLAGS}

echo "Binario gerado em: ${OUT}!"
