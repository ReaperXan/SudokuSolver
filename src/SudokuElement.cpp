#include "SudokuElement.h"

class SudokuElement
{
private:
    short number;
    bool found;

public:
    SudokuElement();
    SudokuElement(bool given, short number);
    void setNumber(short number);
    short getNumber();
    bool isFound();
    void setFound(bool decision);
    ~SudokuElement();
};

SudokuElement::SudokuElement(bool given, short number)
{
    found = given;
    this->number = number;
}

SudokuElement::SudokuElement()
{
    found = false;
}

bool SudokuElement::isFound()
{
    return found;
}

void SudokuElement::setNumber(short number)
{
    this->number = number;
}

void SudokuElement::setFound(bool decision)
{
    this->found = decision;
}

short SudokuElement::getNumber()
{
    return number;
}

SudokuElement::~SudokuElement()
{
}
