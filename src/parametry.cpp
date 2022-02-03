#include "parametry.h"

bool Load_parameters(std::vector <std::string>& params, const int& Liczba_parametrow, char* parametry[])
{
		std::cout<<"Podaj \n-i wejsciowy plik z diragramem \n-o wyjsciowy plik z rozwiazaniem"<<std::endl;
	std::vector <std::string> temp;
	if (Liczba_parametrow != 5) 
	{
		std::cout << "Podano bledna liczbe parametrow! Prosze podac 2 parametry\n";
		return false;
	}
	for (int i = 0; i < Liczba_parametrow; i++)
		temp.push_back(std::string(parametry[i]));
	return true;
}
void wyswietlanie(int **table){ //wyswietlanie table dwuwymiarowa tabela liczb(Wartosci sudoku)
	   for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            std::cout << table[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
char* wczytywaniezpliku(char* filename){ //wczytywanie z pliku filename nazwa pliku
		char *temp = new char[81];

 	std::ifstream indata;
	indata.open(filename);
    int iteration = 0;
    while (!indata.eof())
    {
        char buff;
        indata >> buff;
        if (buff != 'X' && (buff < '0' || buff > '9'))
        {
            indata.close();
            std::cout<<"Zly znak";
        }
        temp[iteration] = buff;
        iteration++;
    }
    return temp;
}
void zapis(char*filename,std::vector<std::vector<SudokuElement*> > solvedTable){ //zapisuje do pliku filename-nazwa pliku wysciwoego solvedtable-rozwiazane sudoku
	std::ofstream zapis(filename);
    for(int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++)
        {
            SudokuElement *tempElement = solvedTable[i][j];
            zapis<<(*tempElement).getNumber() << " ";
        }
        zapis<< std::endl;
    }
	zapis.close();
}
