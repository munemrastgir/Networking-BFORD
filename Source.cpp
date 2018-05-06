#include <iostream>
using namespace std;

struct info {
	char name;
	bool visited = false;
	int distance = 10000;
	char parent = 'x';
};

info arr[50];

struct adjListNode {
	//int position;
	int weight;
	char name;
	adjListNode* next;
};

struct adjList {
	adjListNode* head;
};


int find(info tarr[], char nodeName) {
	int h = 0;
	while (tarr[h].name != nodeName)
		h++;
	return h;
}



void recurs(adjList*x, char source)
{
	int min = 10000;
	int r = find(arr, source);
	int t = 0;
	while (x[t].head->name != source)	//finds current node on the adj list
		t++;

	adjListNode* tmp = x[t].head;
	tmp = tmp->next;

	while (tmp != NULL)		//traverses the nodes neighbors and for each neighbor checks if it's smaller
	{
		int h = find(arr, tmp->name);
		if (tmp->weight + arr[r].distance < arr[h].distance)	//update distance and parent name and intermediate nodes
		{
			arr[h].distance = tmp->weight + arr[r].distance;
			arr[h].parent = x[t].head->name;
			if (arr[h].visited)
				recurs(x, tmp->name);
		}
		tmp = tmp->next;
	}
}

void bFord(adjList*x, int size, char source) {
	int i = 0;
	
	
	while (arr[i].name != source && i < size)	//finds source node and marks it was visited
		i++;
	int pos = i;
	arr[i].distance = 0;
	arr[i].visited = true;
	cout << source << ": ";
	for (int p = 0; p < size; p++)
		cout << arr[p].distance << " ";
	cout << endl;
	for (int j = 0; j < size; j++)		//loops n node times
	{
		int min = 10000;
		int t = 0;
		while (x[t].head->name != source)	//finds current node on the adj list
			t++;

		adjListNode* tmp = x[t].head;
		tmp = tmp->next;
		
		while (tmp != NULL)		//traverses the nodes neighbors and for each neighbor checks if it's smaller
		{
			int h = find(arr, tmp->name);
			if (tmp->weight + arr[pos].distance  < arr[h].distance)	//update distance and parent name and intermediate nodes
			{	
				arr[h].distance = tmp->weight + arr[pos].distance;
				arr[h].parent = x[t].head->name;
				if(arr[h].visited)
					recurs(x, tmp->name);
			}
			
			tmp = tmp->next;
		}

		//Finds next min
		for (int u = 0; u < size; u++)
		{
			if (arr[u].visited == false && arr[u].distance < min)
			{
				min = arr[u].distance;
				pos = u;
			}
		}
		cout << source << ": ";
		for (int p = 0; p < size; p++)
			cout << arr[p].distance << " ";
		
		cout << endl;
		source = arr[pos].name;
		arr[pos].visited = true;
		//cout << arr[pos].name << " " <<arr[pos].distance <<endl;
	}
	
}

int main() {
	adjList* test;

	/////////////////////////////////////
	adjListNode* S4 = new adjListNode;
	S4->name = 'F';
	S4->weight = 5;
	S4->next = NULL;


	adjListNode* S3 = new adjListNode;
	S3->name = 'C';
	S3->weight = 6;
	S3->next = S4;


	adjListNode* S2 = new adjListNode;
	S2->name = 'E';
	S2->weight = 6;
	S2->next = S3;

	adjListNode* S1 = new adjListNode;
	S1->name = 'A';
	S1->weight = 7;
	S1->next = S2;

	adjListNode* S = new adjListNode;
	S->name = 'S';
	S->next = S1;
	/////////////////////////////////////////////////


	adjListNode* A2 = new adjListNode;
	A2->name = 'C';
	A2->weight = -2;
	A2->next = NULL;

	adjListNode* A1 = new adjListNode;
	A1->name = 'B';
	A1->weight = 4;
	A1->next = A2;

	adjListNode* A = new adjListNode;
	A->name = 'A';
	A->next = A1;
	/////////////////////////////////

	adjListNode* B2 = new adjListNode;
	B2->name = 'G';
	B2->weight = -2;
	B2->next = NULL;

	adjListNode* B1 = new adjListNode;
	B1->name = 'H';
	B1->weight = -4;
	B1->next = B2;

	adjListNode* B = new adjListNode;
	B->name = 'B';
	B->next = B1;

	///////////////////////////////////////////

	adjListNode* C2 = new adjListNode;
	C2->name = 'F';
	C2->weight = 1;
	C2->next = NULL;

	adjListNode* C1 = new adjListNode;
	C1->name = 'D';
	C1->weight = 2;
	C1->next = C2;

	adjListNode* C = new adjListNode;
	C->name = 'C';
	C->next = C1;
	/////////////////////////////////////////////

	adjListNode* D = new adjListNode;
	D->name = 'D';
	D->next = NULL;
	/////////////////////////////

	adjListNode* E2 = new adjListNode;
	E2->name = 'F';
	E2->weight = -2;
	E2->next = NULL;

	adjListNode* E1 = new adjListNode;
	E1->name = 'H';
	E1->weight = 3;
	E1->next = E2;

	adjListNode* E = new adjListNode;
	E->name = 'E';
	E->next = E1;
	///////////////////////////////////////////////

	adjListNode* F1 = new adjListNode;
	F1->name = 'D';
	F1->weight = 3;
	F1->next = NULL;

	adjListNode* F = new adjListNode;
	F->name = 'F';
	F->next = F1;

	//////////////////////////////

	adjListNode* G1 = new adjListNode;
	G1->name = 'I';
	G1->weight = -1;
	G1->next = NULL;

	adjListNode* G = new adjListNode;
	G->name = 'G';
	G->next = G1;

	////////////////////////////////

	adjListNode* H1 = new adjListNode;
	H1->name = 'G';
	H1->weight = 1;
	H1->next = NULL;

	adjListNode* H = new adjListNode;
	H->name = 'H';
	H->next = H1;
	////////////////////////////////

	adjListNode* I1 = new adjListNode;
	I1->name = 'H';
	I1->weight = 1;
	I1->next = NULL;

	adjListNode* I = new adjListNode;
	I->name = 'I';
	I->next = I1;

	test = new adjList[10];
	test[0].head = S;
	test[1].head = A; 
	test[2].head = B;
	test[3].head = C;
	test[4].head = D;
	test[5].head = E;
	test[6].head = F;
	test[7].head = G;
	test[8].head = H;
	test[9].head = I;

	arr[0].name = 'S';
	arr[1].name = 'A';
	arr[2].name = 'B';
	arr[3].name = 'C';
	arr[4].name = 'D';
	arr[5].name = 'E';
	arr[6].name = 'F';
	arr[7].name = 'G';
	arr[8].name = 'H';
	arr[9].name = 'I';


	cout << "CN S A B C D E F G H I" <<endl;
	bFord(test, 10, 'S');
	
}