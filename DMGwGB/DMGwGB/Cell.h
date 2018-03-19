#pragma once
#include<vector>
#include "SPoint.h"

class Cell
{
public:
	Cell();
	Cell(Cell & c);
	~Cell();

	/* Ustal stan */
	void setState(unsigned int state);
	void setCheck(bool check);
	/* Pobierz stan */
	unsigned int getState();
	bool Check();

	class SPoint position;
	class std::vector<unsigned int> neighborhoods;
private:

	//Ew. numer ziarna;
	
	unsigned int state; 
	bool check;
};

