#include <glimac/MapTransformation.hpp>
#include <vector>

void transposeGrid(std::vector<std::vector<std::vector<int>>> &grid) {
	int length = grid.size();
	std::vector<std::vector<std::vector<int>>> temp(length, std::vector<std::vector<int>>(length, std::vector<int>(3)));
	for(int i = 0; i < length; i++) {
		temp[i][i] = grid[i][i];
		for(int j = 0; j < length; j++) {
			temp[i][j][0] = grid[j][i][0];
			temp[i][j][1] = grid[j][i][1];
			temp[i][j][2] = grid[j][i][2];
		}
	}
	grid = temp;
}

void invertCols(std::vector<std::vector<std::vector<int>>> &grid) {
	int length = grid.size();
	std::vector<std::vector<std::vector<int>>> temp(length, std::vector<std::vector<int>>(length, std::vector<int>(3)));
	for(int j = 0; j < length; j++) {
		for(int i = 0; i < length; i++) {
			temp[i][j][0] = grid[i][length-j-1][0];
			temp[i][j][1] = grid[i][length-j-1][1];
			temp[i][j][2] = grid[i][length-j-1][2];
		}
	}
	grid = temp;
}

void invertLines(std::vector<std::vector<std::vector<int>>> &grid) {
	int length = grid.size();
	std::vector<std::vector<std::vector<int>>> temp(length, std::vector<std::vector<int>>(length, std::vector<int>(3)));
	for(int i = 0; i < length; i++) {
		for(int j = 0; j < length; j++) {
			temp[i][j][0] = grid[length-i-1][j][0];
			temp[i][j][1] = grid[length-i-1][j][1];
			temp[i][j][2] = grid[length-i-1][j][2];
		}
	}
	grid = temp;
}

void rotateGridLeft(std::vector<std::vector<std::vector<int>>> &grid) {
	transposeGrid(grid);
	invertLines(grid);
}

void rotateGridRight(std::vector<std::vector<std::vector<int>>> &grid) {
	transposeGrid(grid);
	invertCols(grid);
}