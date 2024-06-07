#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Passenger
{
	int age;
	string date;
	float weight;
};

void print2D(Passenger** P, int m, int n)
{
	if(!P) return;
	for( int i = 0; i < m; i++)
	{
		for( int j = 0; j < n; j++) cout << P[i][j].age << " ";
		cout << endl;
	}
}

Passenger*** readFile(string filename, int &p , int &m, int&n)
{
	
	ifstream file_in;
	file_in.open(filename.c_str());
	
	if(!file_in.is_open())
	{
		cout << "File can't be opened.";
		return NULL;
	}
	
	file_in >> p;
	file_in >> m;
	file_in >> n;
	
	file_in.ignore();
	
	Passenger*** P = new Passenger**[p];
	
	for( int i = 0; i < p; i++)
	{
		P[i]  = new Passenger*[m];
		for( int j = 0; j < m; j++)
			P[i][j] = new Passenger[n];
	}
	
	for( int i = 0; i < p; i++)
	{
		for( int j = 0; j < m; j++)
		{
			for( int k = 0; k < n; k++)
			{
				string temp;
				getline(file_in, temp, ' ');
				P[i][j][k].age = stoi(temp);
				getline(file_in, P[i][j][k].date, ' ');
				getline(file_in, temp);
				P[i][j][k].weight = stof(temp);
			}
		}
	}
	
	return P;
}

void print3D(Passenger*** P, int p, int m, int n)
{
	if(!P) return;
	for( int i = 0; i < p; i++)
	{
		for( int j = 0; j < m; j++)
		{
			for( int k = 0; k < n; k++) cout << P[i][j][k].weight << " ";
			cout << endl;
		}
		cout << endl;
	}
}

Passenger** findMinWeight(Passenger*** P, int p, int m, int n, int x, int y)
{
	if(!P) return NULL;
	
	float minSum = 1e9;
	int minPidx = 0;
	int minMidx = 0;
	int minNidx = 0;
	for( int i = 0; i < p; i++)
	{
		for( int j = 0; j + x <= m; j++)
		{
			for( int k = 0; k + y <= n; k++)
			{
				float sum = 0;
				for( int a = j; a < j + x; a++)
				{
					for( int b = k; b < k + y; b++)
					{
						sum += P[i][a][b].weight;
					}
				}
				if(sum < minSum)
				{
					minSum = sum;
					minPidx = i;
					minMidx = j;
					minNidx = k;
				}
			}
		}
	}
	
	Passenger** res = new Passenger*[x];
	
	for( int i = 0; i < x; i++)
		res[i] = new Passenger[y];
		
	for( int i = 0; i < x; i++)
	{
		for( int j = 0; j < y; j++)
			res[i][j] = P[minPidx][minMidx + i][minNidx + j];	
	}
	
	return res;
}

struct PaxNode
{
	int age;
	string date;
	float weight;
	PaxNode* pNext;
};

struct PaxList
{
	PaxNode* pHead = NULL;
	PaxNode* pTail = NULL;
};

PaxList readFromFile(string filename)
{
	ifstream file_in;
	file_in.open(filename.c_str());
	
	PaxList l;
	if(!file_in.is_open())
	{
		cout << "File can't be opened.";
		return l;
	}
	
	
	string tmp;
	getline(file_in, tmp);
	PaxNode* cur;
	while(!file_in.eof())
	{
		if(!l.pHead)
		{
			l.pHead = new PaxNode;
			l.pHead->pNext = NULL;
			cur = l.pHead;
			l.pTail = cur;
		}
		else 
		{
			cur->pNext = new PaxNode;
			cur = cur->pNext;
			cur->pNext = NULL;
			l.pTail = cur;
		}
		getline(file_in, tmp, ' ');
		cur->age = stoi(tmp);
		getline(file_in, cur->date, ' ');
		getline(file_in, tmp);
		cur->weight = stof(tmp);
	}
	
	cur = l.pHead;
	
	while(cur)
	{
		PaxNode* cur1 = cur;
		while(cur1)
		{
			if(cur1->age < cur->age)
			{
				int tmp1 = cur1->age;
				string tmp2 = cur1->date;
				float tmp3 = cur1->weight;
				cur1->age = cur->age;
				cur1->date = cur->date;
				cur1->weight = cur->weight;
				cur->age = tmp1;
				cur->date = tmp2;
				cur->weight = tmp3;
			}
			cur1 = cur1->pNext;
		}
		cur = cur->pNext;
	}

	
	return l;
}

void printList(PaxList L)
{
	PaxNode* cur = L.pHead;
	while(cur)
	{
		cout << cur->age << " " << cur->date <<  " " << cur->weight << endl;
		cur = cur->pNext;
	}
}

void deletePaxList(PaxList &L)
{
	if(L.pHead == NULL) return;
	
	PaxNode* cur = L.pHead;
	PaxNode* cur1;
	
	while(cur->pNext)
	{
		cur1 = cur->pNext;
		while(cur1->age % 2 == 0 && cur->age % 2 == 0)
		{
			PaxNode* tmp = cur1;
			cur1 = cur1->pNext;
			cur->pNext = cur1->pNext;
			delete tmp;
		} 
		cur = cur->pNext;
	}
}

int main()
{
	int p, m, n;
	//Passenger*** P = readFile("inp.txt", p, m, n);
	
	//Passenger** res = findMinWeight( P, p, m, n, 2, 2);
	//print2D(res, 2, 2);
	
	PaxList L = readFromFile("inp.txt");
	
	
	deletePaxList(L);
	printList(L);
	return 0;
}
