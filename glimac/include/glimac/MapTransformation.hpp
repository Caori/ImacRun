#include <vector>

namespace glimac {
	/*! 
	* \fn void transposeGrid(std::vector<std::vector<std::vector<int>>> &grid)
	* \brief Applie a transposition to the game grid
	* \param grid Reference to the game grid
	*/
	void transposeGrid(std::vector<std::vector<std::vector<int>>>& grid);

	/*! 
	* \fn void invertCols(std::vector<std::vector<std::vector<int>>>& grid)
	* \brief Invert the grid's columns
	* \param grid Reference to the game grid
	*/
	void invertCols(std::vector<std::vector<std::vector<int>>>& grid);

	/*! 
	* \fn void invertLines(std::vector<std::vector<std::vector<int>>>& grid)
	* \brief Invert the grid's lines
	* \param grid Reference to the game grid
	*/
	void invertLines(std::vector<std::vector<std::vector<int>>>& grid);

	/*! 
	* \fn void rotateGridLeft(std::vector<std::vector<std::vector<int>>>& grid);
	* \brief Rotates the game grid 90 degrees to the left.
	* \param grid Reference to the game grid
	*/
	void rotateGridLeft(std::vector<std::vector<std::vector<int>>>& grid);

	/*! 
	* \fn void rotateGridRight(std::vector<std::vector<std::vector<int>>>& grid);
	* \brief Rotates the game grid 90 degrees to the right.
	* \param grid Reference to the game grid
	*/
	void rotateGridRight(std::vector<std::vector<std::vector<int>>>& grid);
}