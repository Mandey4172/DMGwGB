#pragma once
class Cell
{
public:
	Cell();
	~Cell();

	/* Ustal stan */
	void setState(unsigned int state);
	/* Pobierz stan */
	unsigned int getState();
private:
	//Ew. numer ziarna;
	unsigned int state; 
};

