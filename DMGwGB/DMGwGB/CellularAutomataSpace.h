#pragma once

#include<vector>
#include<string>

//				BoundaryContidionTypes
/// <summary>
// Enum for each boundary type for cellular automata
//
/// </summary>
enum class BoundaryContidionTypes
{
	Blocking,
	Periodic,
	Reflecting
};

//				Cellular Automata Space
/// <summary>
/// Implements cellular automata grid of cells with description of boundary condition.
/// </summary>
class CellularAutomataSpace
{
public:
	CellularAutomataSpace(unsigned int m = 1, unsigned int n = 1, unsigned int o = 1) noexcept;
	//Copy constructor
	CellularAutomataSpace(const CellularAutomataSpace & ca);
	//Move constructor
	CellularAutomataSpace(CellularAutomataSpace && ca) noexcept;
	//Copy assigment
	CellularAutomataSpace& operator=(const CellularAutomataSpace & ca);
	//Move assigment
	CellularAutomataSpace& operator=(CellularAutomataSpace&& ca) noexcept;
	//Destruktor
	~CellularAutomataSpace();

	//Save to string
	std::string save() const;
	//Load from path
	void load(const std::string &path);

	//Get cells
	unsigned int *** getCells() const;

	//Get boundary type
	BoundaryContidionTypes getBoundatyConditionType() const;
	//Set boundary type
	void setBoundaryContidion(BoundaryContidionTypes type);

	unsigned int getNucleonsCount() const;
	void setNucleonsCount(unsigned int count);

	unsigned int getSizeOnXAxis() const;
	unsigned int getSizeOnYAxis() const;
	unsigned int getSizeOnZAxis() const;


private:
	unsigned int *** cells;

	//Cells per axis
	unsigned int m;	//X
	unsigned int n;	//Y
	unsigned int o;	//Z

	BoundaryContidionTypes boundary_contidion;
	unsigned int nucleons_count;

	void constructSpace(unsigned int m, unsigned int n, unsigned int o);
	void destroySpace();
};
