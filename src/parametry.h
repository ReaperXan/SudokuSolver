#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "SudokuMap.h"
#include "parametry.cpp"
#include "SudokuElement.h"
bool Load_parameters(std::vector <std::string>& params, const int& Liczba_parametrow, char* parametry[]);
void wyswietlanie(int **table);
char* wczytywaniezpliku(char* filename);
void zapis(char*filename,std::vector<std::vector<SudokuElement*> > solvedTable);

