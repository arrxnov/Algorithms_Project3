#include <iostream>

//-------------------------------//
//           OBJECTS             //
//-------------------------------//

class Member
{
public:
	Member* p;
	int rank;
	int id;
};

//-------------------------------//
//  POSITIONAL HELPER FUNCTIONS  //
//-------------------------------//

void makeSet(Member* x)
{
	x->p = x;
	x->rank = 0;
}

Member* findSet(Member* x)
{
	if (x != x->p)
	{
		x->p = findSet(x->p);
	}
	return x->p;
}

void linkSets(Member* x, Member* y)
{
	if (x->rank > y->rank)
	{
		y->p = x;
	}
	else
	{
		if (x->rank == y->rank)
		{
			y->rank++;
		}
	}
}

void unionSets(Member* x, Member* y)
{
	linkSets(findSet(x), findSet(y));
}

// ------------------------------//
//     ALGORITHMIC FUNCTIONS     // 
// ------------------------------//

bool sameComponent(Member* u, Member* v)
{
	if (findSet(u) == findSet(v))
		return true;
	else
		return false;
}

void connectedComponents(Member** G, int n, int m, int k)
{
	for (int i = 0; i < n * m * k; i++)
	{
		Member* v = G[i];
		if (v != NULL) makeSet(v);
	}

	for (int i = 0; i < n * m * k; i++)
	{
		Member* v = G[i];
		Member** nodes = new Member * [6];

		if (v == NULL) continue;

		int local_height = v->id / (m * n);
		int temp = v->id;
		temp = v->id % (m * n);
		int local_column = temp / n;
		int local_row = temp % n;

		// +/- n axis
		if (local_row < n - 1)
		{
			nodes[0] = G[v->id + 1];
		}
		else
		{
			nodes[0] = NULL;
		}
		if (local_row > 0)
		{
			nodes[1] = G[v->id - 1];
		}
		else
		{
			nodes[1] = NULL;
		}

		// +/- m axis
		if (local_column < m - 1)
		{
			nodes[2] = G[v->id + n];
		}
		else
		{
			nodes[2] = NULL;
		}
		if (local_column > 0)
		{
			nodes[3] = G[v->id - n];
		}
		else
		{
			nodes[3] = NULL;
		}

		// +/- k axis
		if (local_height < k - 1)
		{
			nodes[4] = G[v->id + m * n];
		}
		else
		{
			nodes[4] = NULL;
		}
		if (local_height > 0)
		{
			nodes[5] = G[v->id - m * n];
		}
		else
		{
			nodes[5] = NULL;
		}

		for (int j = 0; j < 6; j++)
		{
			Member* u = nodes[j];
			if (u == NULL)
			{
				continue;
			}
			if (findSet(u) != findSet(v))
			{
				unionSets(u, v);
			}
		}
	}
}

//-------------------------------//
//             MAIN              //
//-------------------------------//

int main()
{
	using namespace std;
	int k, l, m, n, setCount = 0, numMonthsDisconnectedFromTheMainCOBOLCluster = 0;
	cin >> n >> m >> k >> l;
	int** monarchies = new int* [l];

	for (int i = l - 1; i >= 0; i--)
	{
		int p, input;
		cin >> p;
		monarchies[i] = new int[p + 1];
		monarchies[i][0] = p;
		for (int j = 1; j <= p; j++)
		{
			cin >> input;
			monarchies[i][j] = input;
		}
	}

	// build empire
	Member** empire = new Member * [n * m * k];

	for (int i = 0; i < n * m * k; i++)
	{
		empire[i] = NULL;
	}

	for /* each monarchy */ (int i = 0; i < l; i++)
	{
		// add pieces of empire one by one
		for /* each dominion per monarchy */ (int j = 1; j <= monarchies[i][0]; j++)
		{
			Member* newNode = new Member;
			newNode->id = monarchies[i][j];
			empire[newNode->id] = newNode;
			makeSet(newNode);
			setCount++;
			// Check neighbors
			int local_height = newNode->id / (m * n);
			int temp = newNode->id;
			temp = newNode->id % (m * n);
			int local_column = temp / n;
			int local_row = temp % n;
			Member** nodes = new Member * [6];
			// +/- n axis
			if (local_row < n - 1)
			{
				if (empire[newNode->id + 1] != NULL
					&& findSet(newNode) != findSet(empire[newNode->id + 1]))
				{
					unionSets(newNode, empire[newNode->id + 1]);
					setCount--;
				}
			}

			if (local_row > 0)
			{
				if (empire[newNode->id - 1] != NULL
					&& findSet(newNode) != findSet(empire[newNode->id - 1]))
				{
					unionSets(newNode, empire[newNode->id - 1]);
					setCount--;
				}
			}

			// +/- m axis
			if (local_column < m - 1)
			{
				if (empire[newNode->id + n] != NULL
					&& findSet(newNode) != findSet(empire[newNode->id + n]))
				{
					unionSets(newNode, empire[newNode->id + n]);
					setCount--;
				}
			}

			if (local_column > 0)
			{
				if (empire[newNode->id - n] != NULL
					&& findSet(newNode) != findSet(empire[newNode->id - n]))
				{
					unionSets(newNode, empire[newNode->id - n]);
					setCount--;
				}
			}

			// +/- k axis
			if (local_height < k - 1)
			{
				if (empire[newNode->id + n * m] != NULL
					&& findSet(newNode) != findSet(empire[newNode->id + m * n]))
				{
					unionSets(newNode, empire[newNode->id + m * n]);
					setCount--;
				}
			}

			if (local_height > 0)
			{
				if (empire[newNode->id - n * m] != NULL
					&& findSet(newNode) != findSet(empire[newNode->id - m * n]))
				{
					unionSets(newNode, empire[newNode->id - m * n]);
					setCount--;
				}
			}

			empire[monarchies[i][j]] = newNode;
		}
		if (setCount > 1)
		{
			numMonthsDisconnectedFromTheMainCOBOLCluster++;
		}
	}

	cout << numMonthsDisconnectedFromTheMainCOBOLCluster << endl;

	for (int i = 0; i < n * m * k; i++)
	{
		delete empire[i];
	}
	delete[] empire;

	return 0;
}
