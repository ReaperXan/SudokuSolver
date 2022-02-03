#include "SudokuMap.h"
#include "SudokuElement.h"
#include "parametry.h"
#include "sudoku_solver.h"

int main(int argc, char* argv[])
{
	std::vector <std::string> parameters;
	std::vector <int> varibles;
	parameters.resize(2);
	if (!Load_parameters(parameters, argc, argv))
		return -1;
    
	char *temp = wczytywaniezpliku(argv[2]);
	
    SudokuMap *sudokuMap = new SudokuMap(temp);
    int **table = sudokuMap->getTableValues();

    std::cout << "Nieroziwazane sudoku\n";
   wyswietlanie(table);
sudokuMap->solveSudoku();
 std::vector<std::vector<SudokuElement*> > solvedTable = sudokuMap->getTableSolved();


    std::cout << "Rozwiazane sudoku\n";
zapis(argv[4],solvedTable);
wyswietlanie(sudokuMap->getTableSolvedValues());

    delete[] temp; 
    delete sudokuMap;


    std::cout << "Koncze dzialanie!\n";
    return 0;
}
