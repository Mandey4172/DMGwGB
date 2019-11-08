#pragma once
#include <memory>

//				Cellular Automata
/// <summary>
// Class represents implementation of cellular automata system.
//
/// Cellular is system based on grid of cells. Cell can be in one of finite states.
/// Each cell has a set of cell called neighborhood. Next time step can be
/// calculated by a specific rule witch depends on actual cell state and neighborhood state.
/// </summary>
class CellularAutomata
{
public:

	CellularAutomata() noexcept;
	virtual ~CellularAutomata();

	/// <summary> Perform single time step </summary>
	/// <returns> Is cellular automata stable </returns>
	virtual bool step();
	/// <summary> Perform next time steps until cellular automata is stable </summary>
	void start();

	/// <summary>  </summary>
	void setCellularAutomataSpace(const std::shared_ptr< class CellularAutomataSpace > & cellularautomata);
	std::shared_ptr< class CellularAutomataSpace > getCellularAutomataSpace() const;
	/// <summary>  </summary>
	void setNeighborhood(const std::shared_ptr< class Neighborhood > & neighborhood);
	std::shared_ptr< class Neighborhood > getNeighborhood() const;
	/// <summary>  </summary>
	void setCellularAutomataRule(const std::shared_ptr< class CellularAutomataRule > & rule);
	std::shared_ptr< class CellularAutomataRule > getCellularAutomataRule() const;
protected:
	/// <summary> Field represent space of cellular automata </summary>
	std::shared_ptr< class CellularAutomataSpace > cellular_automata_space;
	/// <summary> Field contains interface with schema to get all neighborhood states </summary>
	std::shared_ptr< class Neighborhood > neighborhood;
	/// <summary> Field contains interface with rule for calculation of next time step </summary>
	std::shared_ptr< class CellularAutomataRule > rule;
};
