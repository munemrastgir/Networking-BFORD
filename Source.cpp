#include <iostream>
#include <stdlib.h>

#define ADJ_SIZE 10
#define INFO_SIZE 10
#define MAX_INT 999999

class info {
public:
	//Default constructor
	info():visited_{false}, distance_{MAX_INT}, parent_{'x'}{}
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
	void setNext(adjListNode* next){this->next_ = next;}
private:
	int weight_;
	char name_;
	adjListNode* next_;
};

struct adjList {
	adjListNode* head;
};

void recurs(adjList*x, info* arr, int adjSize, int infoSize, char source);
void bFord(adjList*x, info* arr, int adjSize, int infoSize, char source);
void populate(adjList* test, info* arr);
int find(info* tarr, size_t size, char nodeName);

int main() {
	adjList test[ADJ_SIZE];
	info arr[INFO_SIZE];
	populate(test, arr);
	bFord(test, arr, ADJ_SIZE, INFO_SIZE, 'S');
}


void populate(adjList* test, info* arr){
	adjListNode
		*S4 = new adjListNode('F', 5),
		*S3 = new adjListNode('C', 6),
		*S2 = new adjListNode('E', 6),
		*S1 = new adjListNode('A', 7),
		*S = new adjListNode('S', MAX_INT);
	S3->setNext(S4);
	S2->setNext(S3);
	S1->setNext(S2);
	S->setNext(S1);

	adjListNode
		*A2 = new adjListNode('C', -2),
		*A1 = new adjListNode('B', 4),
		*A = new adjListNode('A', MAX_INT);
	A1->setNext(A2);
	A->setNext(A1);

	adjListNode
		*B2 = new adjListNode('G', -2),
		*B1 = new adjListNode('H', -4),
		*B = new adjListNode('B', MAX_INT);
	B1->setNext(B2);
	B->setNext(B1);

	adjListNode
		*C2 = new adjListNode('F', 1),
		*C1 = new adjListNode('D', 2),
		*C = new adjListNode('C', MAX_INT);
	C1->setNext(C2);
	C->setNext(C1);

	adjListNode
		*D = new adjListNode('D', MAX_INT);

	adjListNode
		*E2 = new adjListNode('F', -2),
		*E1 = new adjListNode('H', 3),
		*E = new adjListNode('E', MAX_INT);
	E1->setNext(E2);
	E->setNext(E1);

	adjListNode
		*F1 = new adjListNode('D', 3),
		*F = new adjListNode('F', MAX_INT);
	F->setNext(F1);

	adjListNode
		*G1 = new adjListNode('I', -1),
		*G = new adjListNode('G', MAX_INT);
	G->setNext(G1);

	adjListNode
		*H1 = new adjListNode('G', 1),
		*H = new adjListNode('H', MAX_INT);
	H->setNext(H1);

	adjListNode
		*I1 = new adjListNode('H', 1),
		*I = new adjListNode('I', MAX_INT);
	I->setNext(I1);

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
	return;
}

int find(info tarr[], size_t size, char nodeName) {
	size_t h = 0;
	while (tarr[h].getName() != nodeName)
		h++;
	if (tarr[h].getName() == nodeName)
		return h;
	else
		return -1;
}

void recurs(adjList*x, info* arr, int adjSize, int infoSize, char source){
	int r = find(arr, 50, source);
	if(r == -1)
		exit(-1);
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
				recurs(x, arr, adjSize, infoSize, tmp->getName());
		}
		tmp = tmp->getNext();
	}
}

void bFord(adjList*x, info* arr, int adjSize, int infoSize, char source) {
	std::cout << "CN S\tA\tB\tC\tD\tE\tF\tG\tH\tI" << std::endl;
	int i = 0;
	while (arr[i].getName() != source && i < adjSize)	//finds source node and marks it was visited
		i++;
	int pos = i;
	arr[i].setDist(0);
	arr[i].setVisit(true);
	std::cout << source << ": ";
	for (int p = 0; p < adjSize; p++)
		std::cout << arr[p].getDist() << "\t";
	std::cout << std::endl;
	//loops n node times
	for (int j = 0; j < adjSize; j++){
		int min = MAX_INT;
		//recurs function goes to current node, updates it's neighbors if smaller,
		//and recurses through the intermediate nodes
		recurs(x, arr, adjSize, infoSize, source);
		//Finds next min for next node
		for (int u = 0; u < adjSize; u++){
			if (arr[u].getVisit() == false && arr[u].getDist() < min){
				min = arr[u].getDist();
				pos = u;
			}
		}
		//prints the known smallest distances after updating a node
		std::cout << source << ": ";
		for (int p = 0; p < adjSize; p++)
			std::cout << arr[p].getDist() << "\t";

		std::cout << std::endl;
		source = arr[pos].getName();
		arr[pos].setVisit(true);
		//cout << arr[pos].name << " " <<arr[pos].distance <<endl;
	}

}
