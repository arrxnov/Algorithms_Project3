#include <iostream>

//-------------------------------//
//  POSITIONAL HELPER FUNCTIONS  //
//-------------------------------//

// ------------------------------//
//     ALGORITHMIC FUNCTIONS     // 
// ------------------------------//

//-------------------------------//
//             MAIN              //
//-------------------------------//

int main()
{
	using namespace std;
	int k, l, m, n, numProblems;
	cin >> numProblems;
	cin >> n >> m >> l >> k;

	int** monarchies = new int*[l];

	for (int i = 0; i < l; i++)
	{
		int p;
		cin >> p;
		monarchies[i] = new int[p];
		for (int j = 0; j < p; j++)
		{
			cin >> monarchies[i][j];
		}
	}



	return 0;
}