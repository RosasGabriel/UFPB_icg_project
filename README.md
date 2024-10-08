# UFPB_icg_project
Repositório para o projeto final da disciplina de Introdução à Computação Gráfica

Este é um projeto de introdução à computação gráfica, onde implementamos um Ray Casting utilizando C++ e OpenGL.

## Estrutura do Projeto


## Requisitos

Antes de compilar, certifique-se de que as bibliotecas necessárias estão instaladas:

```bash
sudo apt update
sudo apt install freeglut3 freeglut3-dev
sudo apt install mesa-utils


## Compilação 

g++ -I./include src/*.cpp main.cpp -o icg_project -lGL -lGLU -lglut

## Execução

./icg_project