#include <iostream>

//-------------------------------//
//           OBJECTS             //
//-------------------------------//

class Member
{
public:
	Member *p;
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
		Member** nodes = new Member* [6];
		
		if (v == NULL) continue;

		// +/- n axis
		if (v->id % n < n - 1)
		{
			nodes[0] = G[v->id + 1];
		}
		else
		{
			nodes[0] = NULL;
		}
		if (v->id % n > 0)
		{
			nodes[1] = G[v->id - 1];
		}
		else
		{
			nodes[1] = NULL;
		}

		// +/- m axis
		if ((v->id / n % m) < m - 1)
		{
			nodes[2] = G[v->id + n];
		}
		else
		{
			nodes[2] = NULL;
		}
		if (v->id / n > 0)
		{
			nodes[3] = G[v->id - n];
		}
		else
		{
			nodes[3] = NULL;
		}

		// +/- k axis
		if ((v->id / m / n) % k < k - 1)
		{
			nodes[4] = G[v->id + m * n];
		}
		else
		{
			nodes[4] = NULL;
		}
		if (v->id / m / n > 0)
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
			if (u == NULL || v == NULL)
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
	int k, l, m, n;
	cin >> n >> m >> k>> l;

	int** monarchies = new int*[l];

	for (int i = 0; i < l; i++)
	{
		int p;
		cin >> p;
		monarchies[i] = new int[p];
		monarchies[i][0] = p;
		for (int j = 1; j <= p; j++)
		{
			cin >> monarchies[i][j];
		}
	}

	// build empire
	Member** empire = new Member*[n * m * k];
	for (int i = 0; i < n * m * k; i++)
	{
		Member* newMember = new Member;
		newMember->id = i;
		empire[i] = newMember;
	}

	for /* each monarchy */ (int i = 1; i < l; i++)
	{
		// remove pieces of empire one by one
		for /* each dominion per monarchy */ (int j = 1; j <= monarchies[i][0]; j++)
		{
			empire[monarchies[i][j]] = NULL;
		}

		// test if sets are disjoint
		connectedComponents(empire, n, m, k);
		Member* curr = NULL;
		for (int j = 0; j < n * m * k; j++)
		{
			if (empire[j] == NULL) continue;
			if (curr == NULL) curr = empire[j]->p;
			else if (curr != empire[j]->p)
			{
				cout << "[+] Broken at " << i << endl;
				break;
			}
		}
	}

	for (int i = 0; i < n * m * k; i++)
	{
		delete empire[i];
	}
	delete[] empire;

	return 0;
}
