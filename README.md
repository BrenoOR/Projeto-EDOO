# Projeto-EDOO

Este repositório contém a implementação do Projeto da disciplina de Estruturas de Dados Orientada à Objetos.
O objetivo do projeto é analisar o código de um projeto da disciplina de Introdução à Programação escrito originalmente em Python e traduzi-lo para C++, respeitando as regras do jogo e aplicando conceitos de orientação à objetos ao código.

## Índice

- [Projeto base](#projeto-base)
- [Instalação das dependências](#instalação-das-dependências)
- [Compilando o projeto](#compilando-o-projeto)
- [Configurando a simulação](#configurando-a-simulação)
- [Executando o game](#executando-o-game)

## Projeto base

O projeto base é o game [MineCIn](https://github.com/UirajanJS/Projeto-IP) feito por:

- João Victor Presbytero
- Maria Rosicler Lúcia de Lima
- Pierre Antônio da Silva
- Rafael Cardoso Clementino de Siqueira
- Uirajan José da Silva

## Instalação das dependências

O projeto foi originalmente escrito no SO Ubuntu 26.04, porém é possível que funcione em versões anteriores ao OS, como 20.04 ou 22.04.
Obs.: Todos os comandos à seguir são executados a partir da raíz do projeto.
Para instalar as dependências basta executar os seguintes comandos:

```bash
chmod +x ./install.sh
./instal.sh
```

## Compilando o projeto

Para compilar todo o projeto basta executar os seguintes comandos:

```bash
chmod +x ./build.sh
./build.sh
```

Será gerado o arquivo `/bin/minecin`.

## Configurando a simulação

Para configurar uma simulação basta cria um arquivo json:

```bash
cd assets/scripts
touch <filename>.json
```

A simulação roda o jogo frame a frame, sem esperar por gráficos. Então a descrição contém a ação do player realizada em determinados frames da simulação.

```json
{
    "modo": "",
    "frames": [
        {
            "frame": 0,
            "held": [],
            "pressed": [] 
        },
    ]
}
```

Escolher modo entre: `Tempo` ou `Blocos`.
Exemplo de comandos para `held` e `pressed`:

```json
{
    "W": Cima,
    "A": Esquerda,
    "S": Baixo,
    "D": Direita,
    "F": Minerar,
    "G": Restaurar
}
```

## Executando o game

Para executar o jogo basta executar o binário gerado:

```bash
./bin/minecin
```

Use a flag `--simulacao <filename>.json` para simular o jogo.

```bash
./bin/minecin --simulacao <filename>.json
```
