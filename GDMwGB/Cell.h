#pragma once
class Cell
{
public:
	Cell();
	~Cell();

	/* Ustal stan */
	void setState(unsigned int state);
	void setCheck(bool check);
	void Fill();
	/* Pobierz stan */
	unsigned int getState();
	bool Check();

	class SPoint * position;
private:

	//Ew. numer ziarna;
	
	unsigned int state; 
	bool check;
	int fill;
};

