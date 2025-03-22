@echo off
g++ -c main.cpp -Isrc/include
g++ main.o -o calculator -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system
echo Compilation complete!