#include<vector>
using std::vector;

vector<vector<vector<int>>> simplify(vector<vector<int>> const& sudoku)
{
	//for each cell with value x
	// if x > 0: possible at this poisition: <x>
	// else: possible at this position: <1,2,3... n²>

	// e.g.:	<3,7,9> in cell (0,0)
	//			<3,5,7> in cell (1,1)
	return vector<vector<vector<int>>>();
}