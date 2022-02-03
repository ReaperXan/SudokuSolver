#include "SudokuMap.h"
//TODO Gdzieś się sypie - lecz gdzie? Do znalezienia
class SudokuMap
{
private:
    std::vector<std::vector<SudokuElement *> > tableOriginal;
    std::vector<std::vector<SudokuElement *> > tableSolved;
    bool solved;
    bool solveSudokuRecursion(std::vector<std::vector<SudokuElement *> > table);
    bool checkIfSudokuIsSolved(std::vector<std::vector<SudokuElement *> > table); //Sudoku is filled completelly
    bool checkIfSudokuMapIsFull(std::vector<std::vector<SudokuElement *> > table);
    bool checkIfSudokuIsCorrect(std::vector<std::vector<SudokuElement *> > table); //Sudoku is partly solved correctly
    bool checkIfIsCorrectVertical(std::vector<std::vector<SudokuElement *> > table);
    bool checkElementVertical(std::vector<std::vector<SudokuElement *> > table, int j);
    bool checkIfIsCorrectHorizontal(std::vector<std::vector<SudokuElement *> > table);
    bool checkElementHorizontal(std::vector<std::vector<SudokuElement *> > table, int i);
    bool checkIfIsCorrectInGrid(std::vector<std::vector<SudokuElement *> > table);
    bool checkIfOneGridIsCorrect(std::vector<std::vector<SudokuElement *> > table, int iMin, int iMax, int jMin, int jMax);
    int countPossibilities(std::vector<std::vector<SudokuElement *> > table, int i, int j);
    bool *findPossibilities(std::vector<std::vector<SudokuElement *> > table, int i, int j);

    std::vector<std::vector<SudokuElement *> > copyMap(std::vector<std::vector<SudokuElement *> > table);

public:
    SudokuMap(char givenTab[]);
    int **getTableValues();
    int **getTableSolvedValues();
    std::vector<std::vector<SudokuElement *> > getTable();
    std::vector<std::vector<SudokuElement *> > getTableSolved();
    
    void solveSudoku();
    ~SudokuMap();
};

SudokuMap::SudokuMap(char givenTab[])
{
    solved = false;
    tableOriginal.resize(9);
    tableSolved.resize(9);

    //Creating tableOriginal of our sudoku
    for (int i = 0; i < 9; i++)
    {
        tableOriginal[i].resize(9);
        tableSolved[i].resize(9);

        for (int j = 0; j < 9; j++)
        {

            char temp = givenTab[i * 9 + j];
            if (temp == 'X')
            {
                tableOriginal[i][j] = new SudokuElement();
            }
            else
            {
                tableOriginal[i][j] = new SudokuElement(true, temp - '0');
            }
        }
    }
}

int **SudokuMap::getTableValues()
{
    int **tab = new int *[9];
    for (int i = 0; i < 9; i++)
    {
        tab[i] = new int[9];
        for (int j = 0; j < 9; j++)
        {
            if ((*tableOriginal[i][j]).isFound())
            {
                tab[i][j] = (*tableOriginal[i][j]).getNumber();
            }
            else
            {
                tab[i][j] = 0;
            }
        }
    }

    return tab;
}

int **SudokuMap::getTableSolvedValues()
{
    int **tab = new int *[9];
    for (int i = 0; i < 9; i++)
    {
        tab[i] = new int[9];
        for (int j = 0; j < 9; j++)
        {
            if ((*tableSolved[i][j]).isFound())
            {
                tab[i][j] = (*tableSolved[i][j]).getNumber();
            }
            else
            {
                tab[i][j] = 0;
            }
        }
    }

    return tab;
}

bool SudokuMap::checkIfSudokuIsSolved(std::vector<std::vector<SudokuElement *> > table)
{
    if (!checkIfSudokuMapIsFull(table))
    {
        return false;
    }

    return checkIfSudokuIsCorrect(table);
}

bool SudokuMap::checkIfSudokuMapIsFull(std::vector<std::vector<SudokuElement *> > table)
{

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            SudokuElement *tempElement = table[i][j];
            if (!(*tempElement).isFound())
            {
                return false;
            }
        }
    }
    return true;
}

bool SudokuMap::checkIfSudokuIsCorrect(std::vector<std::vector<SudokuElement *> > table)
{
    //TODO Prawdopodobnie wywalić pętle

    //vert
    if (!checkIfIsCorrectVertical(table))
    {
        return false;
    }
    //hor
    if (!checkIfIsCorrectHorizontal(table))
    {
        return false;
    }
    //grid
    if (!checkIfIsCorrectInGrid(table))
    {
        return false;
    }

    return true;
}

bool SudokuMap::checkIfIsCorrectVertical(std::vector<std::vector<SudokuElement *> > table)
{
    for (int j = 0; j < 9; j++)
    {
        if (!checkElementVertical(table, j))
        {
            return false;
        }
    }
    return true;
}

bool SudokuMap::checkElementVertical(std::vector<std::vector<SudokuElement *> > table, int j)
{
    for (int i = 0; i < 9; i++)
    {
        if ((*table[i][j]).isFound())
        {
            short number = (*table[i][j]).getNumber();
            for (int k = i + 1; k < 9; k++)
            {

                if (number == (*table[k][j]).getNumber())
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool SudokuMap::checkIfIsCorrectHorizontal(std::vector<std::vector<SudokuElement *> > table)
{
    for (int i = 0; i < 9; i++)
    {
        if (!checkElementHorizontal(table, i))
        {
            return false;
        }
    }
    return true;
}

bool SudokuMap::checkElementHorizontal(std::vector<std::vector<SudokuElement *> > table, int i)
{
    for (int j = 0; j < 9; j++)
    {
        if ((*table[i][j]).isFound())
        {
            short number = (*table[i][j]).getNumber();
            for (int k = j + 1; k < 9; k++)
            {

                if (number == (*table[i][k]).getNumber())
                {
                    return false;
                }
            }
        }
    }
    return true;
}
bool SudokuMap::checkIfIsCorrectInGrid(std::vector<std::vector<SudokuElement *> > table)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (!checkIfOneGridIsCorrect(table, i * 3, i * 3 + 3, j * 3, j * 3 + 3))
            {
                return false;
            }
        }
    }
    return true;
}

bool SudokuMap::checkIfOneGridIsCorrect(std::vector<std::vector<SudokuElement *> > table, int iMin, int iMax, int jMin, int jMax)
{
    //TODO potencjalnie do poprawienia argumenty
    short occurances[9];
    for (int i = 0; i < 9; i++)
    {
        occurances[i] = 0;
    }

    for (int i = iMin; i < iMax; i++)
    {
        for (int j = jMin; j < jMax; j++)
        {
            if ((*table[i][j]).isFound())
            {
                occurances[(*table[i][j]).getNumber() - 1]++;
            }
        }
    }

    for (int i = 0; i < 9; i++)
    {
        if (occurances[i] > 1)
        {
            return false;
        }
    }
    return true;
}

void SudokuMap::solveSudoku()
{
    solved = solveSudokuRecursion(tableOriginal);
}

bool SudokuMap::solveSudokuRecursion(std::vector<std::vector<SudokuElement *> > table)
{
    if (checkIfSudokuIsSolved(table))
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                tableSolved[i][j] = new SudokuElement(true, (*(table[i][j])).getNumber());
            }
        }
        return true;
    }
    if (!checkIfSudokuIsCorrect(table))
    {
        return false;
    }
    std::vector<std::vector<SudokuElement *> > tempTable = table;

    int possibilities[9][9];
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            possibilities[i][j] = 0;
        }
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            possibilities[i][j] = countPossibilities(table, i, j);
        }
    }

    int iMin = 0;
    int jMin = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (possibilities[i][j] < possibilities[iMin][jMin])
            {
                iMin = i;
                jMin = j;
            }
        }
    }

    bool *possibleNumbers = findPossibilities(table, iMin, jMin);

    for (int i = 0; i < 9; i++)
    {
        if (possibleNumbers[i])
        {
            (*tempTable[iMin][jMin]).setNumber(i + 1);
            (*tempTable[iMin][jMin]).setFound(true);
            bool isSolved = solveSudokuRecursion(tempTable);
            if (isSolved)
            {
                return true;
            }
            else
            {
                (*tempTable[iMin][jMin]).setFound(false);
            }
        }
    }
    return false;
}

bool *SudokuMap::findPossibilities(std::vector<std::vector<SudokuElement *> > table, int i, int j)
{

    bool *possibleNumbers = new bool[9];
    for (int a = 0; a < 9; a++)
    {
        possibleNumbers[a] = true;
    }

    //vert
    for (int a = 0; a < 9; a++)
    {
        if (a != i && (*table[a][j]).isFound())
        {
            possibleNumbers[(*table[a][j]).getNumber() - 1] = false;
        }
    }
    //hori
    for (int a = 0; a < 9; a++)
    {
        if (a != j && (*table[i][a]).isFound())
        {
            possibleNumbers[(*table[i][a]).getNumber() - 1] = false;
        }
    }
    //grid
    int topLeftIGrid;
    int topLeftJGrid;

    if (i < 3)
    {
        topLeftIGrid = 0;
    }
    else if (i < 6)
    {
        topLeftIGrid = 3;
    }
    else
    {
        topLeftIGrid = 6;
    }

    if (j < 3)
    {
        topLeftJGrid = 0;
    }
    else if (j < 6)
    {
        topLeftJGrid = 3;
    }
    else
    {
        topLeftJGrid = 6;
    }

    for (int a = topLeftIGrid; a < topLeftIGrid + 3; a++)
    {
        for (int b = topLeftJGrid; b < topLeftJGrid + 3; b++)
        {
            if (a != i && b != j && (*table[a][b]).isFound())
            {
                possibleNumbers[(*table[a][b]).getNumber() - 1] = false;
            }
        }
    }
    return possibleNumbers;
}

int SudokuMap::countPossibilities(std::vector<std::vector<SudokuElement *> > table, int i, int j)
{
    if ((*table[i][j]).isFound())
    {
        return 10; //10 means its found
    }

    bool *possibleNumbers = findPossibilities(table, i, j);

    int result = 0;
    for (int a = 0; a < 9; a++)
    {
        if (possibleNumbers[a])
        {
            result++;
        }
    }

    return result;
}

// std::vector<std::vector<SudokuElement*> > SudokuMap::copyMap(std::vector<std::vector<SudokuElement*> > tableGiven)
// {
//     std::vector<std::vector<SudokuElement*> > table = tableGiven;

//     for (int i = 0; i < 9; i++)
//     {
//         for (int j = 0; j < 9; j++)
//         {
//             SudokuElement *element = table[i][j];
//             if ((*element).isFound())
//             {
//                 SudokuElement *tempElement = new SudokuElement(true, (*element).getNumber());
//                 tempTable[i][j] = tempElement;
//             }
//             else
//             {
//                 SudokuElement *tempElement = new SudokuElement();
//                 tempTable[i][j] = tempElement;
//             }
//         }
//     }
//     return table;
// }

std::vector<std::vector<SudokuElement *> > SudokuMap::getTable()
{
    return tableOriginal;
}

std::vector<std::vector<SudokuElement *> > SudokuMap::getTableSolved()
{
    return tableSolved;
}

SudokuMap::~SudokuMap()
{
    //TODO Dopisać destruktor
}
