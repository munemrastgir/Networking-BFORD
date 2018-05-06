#include <iostream>
using namespace std;

class info {
public:
	//Default constructor
	info():visited_{false}, distance_{10000}, parent_{'x'}{}
	//Regular constructor
	info(char name, bool visited, int distance, char parent):
	name_{name}, visited_{visited}, distance_{distance}, parent_{parent}{}
	//Getters
	char getName(){return name_;}
	bool getVisit(){return visited_;}
	int getDist(){return distance_;}
	char getParent(){return parent_;}
	//Setters
	void setName(char name){this->name_ = name;}
	void setVisit(bool visited){this->visited_ = visited;}
	void setDist(int distance){this->distance_ = distance;}
	void setParent(char parent){this->parent_ = parent;}
private:
	char name_;
	bool visited_;
	int distance_;
	char parent_;
};

class adjListNode {
public:
	//Constructor
	adjListNode(char name, int weight):weight_{weight}, name_{name}, next_{nullptr}{}
	//Getters
	int getWeight(){return weight_;}
	char getName(){return name_;}
	adjListNode* getNext(){return next_;}
	//Setters
	void setName(char name){this->name_ = name;}
	void setWeight(int weight){this->weight_ = weight;}
	void setNext(adjListNode& next){this->next_ = &next;}
private:
	int weight_;
	char name_;
	adjListNode* next_;
};

struct adjList {
	adjListNode* head;
};

int find(info tarr[], size_t size, char nodeName) {
	size_t h = 0;
	while (tarr[h].getName() != nodeName)
		h++;
	if (tarr[h].getName() == nodeName)
		return h;
	else
		return -1;
}

info arr[50];


void recurs(adjList*x, char source){
	int r = find(arr, 50, source);
	int t = 0;
	while (x[t].head->getName() != source)	//finds current node on the adj list
		t++;

	adjListNode* tmp = x[t].head;
	tmp = tmp->getNext();

	while (tmp != NULL)		//traverses the nodes neighbors and for each neighbor checks if it's smaller
	{
		int h = find(arr, 50, tmp->getName());
		if (tmp->getWeight() + arr[r].getDist() < arr[h].getDist())	//update distance and parent name and intermediate nodes
		{
			arr[h].setDist(tmp->getWeight() + arr[r].getDist());
			arr[h].setParent(x[t].head->getName());
			if (arr[h].getVisit())
				recurs(x, tmp->getName());
		}
		tmp = tmp->getNext();
	}
}

void bFord(adjList*x, int size, char source) {
	int i = 0;
	while (arr[i].getName() != source && i < size)	//finds source node and marks it was visited
		i++;
	int pos = i;
	arr[i].setDist(0);
	arr[i].setVisit(true);
	cout << source << ": ";
	for (int p = 0; p < size; p++)
		cout << arr[p].getDist() << "\t";
	cout << endl;
	for (int j = 0; j < size; j++)		//loops n node times
	{
		int min = 10000;

		recurs(x, source);	//recurs function goes to current node, updates it's neighbors if smaller, and recurses through the intermediate nodes

		//Finds next min for next node
		for (int u = 0; u < size; u++)
		{
			if (arr[u].getVisit() == false && arr[u].getDist() < min)
			{
				min = arr[u].getDist();
				pos = u;
			}
		}

		//prints the known smallest distances after updating a node
		cout << source << ": ";
		for (int p = 0; p < size; p++)
			cout << arr[p].getDist() << "\t";

		cout << endl;
		source = arr[pos].getName();
		arr[pos].setVisit(true);
		//cout << arr[pos].name << " " <<arr[pos].distance <<endl;
	}

}

int main() {
	adjList* test;

	adjListNode S4('F', 5), S3('C', 6), S2('E', 6), S1('A', 7), S('S', 10000);
	S3.setNext(S4);
	S2.setNext(S3);
	S1.setNext(S2);
	S.setNext(S1);

	adjListNode A2('C', -2), A1('B', 4), A('A', 10000);
	A1.setNext(A2);
	A.setNext(A1);

	adjListNode B2('G', -2), B1('H', -4), B('B', 10000);
	B1.setNext(B2);
	B.setNext(B1);
	
	adjListNode C2('F', 1), C1('D', 2), C('C', 10000);
	C1.setNext(C2);
	C.setNext(C1);
	
	adjListNode D('D', 10000);

	adjListNode E2('F', -2), E1('H', 3), E('E', 10000);
	E1.setNext(E2);
	E.setNext(E1);
	
	adjListNode F1('D', 3), F('F', 10000);
	F.setNext(F1);

	adjListNode G1('I', -1), G('G', 10000);
	G.setNext(G1);

	adjListNode H1('G', 1), H('H', 10000);
	H.setNext(H1);

	adjListNode I1('H', 1), I('I', 10000);
	I.setNext(I1);

	test = new adjList[10];
	test[0].head = &S;
	test[1].head = &A;
	test[2].head = &B;
	test[3].head = &C;
	test[4].head = &D;
	test[5].head = &E;
	test[6].head = &F;
	test[7].head = &G;
	test[8].head = &H;
	test[9].head = &I;

	arr[0].setName('S');
	arr[1].setName('A');
	arr[2].setName('B');
	arr[3].setName('C');
	arr[4].setName('D');
	arr[5].setName('E');
	arr[6].setName('F');
	arr[7].setName('G');
	arr[8].setName('H');
	arr[9].setName('I');


	cout << "CN S\tA\tB\tC\tD\tE\tF\tG\tH\tI" <<endl;
	bFord(test, 10, 'S');

}
