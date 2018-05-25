#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

#define ADJ_SIZE 6
#define INFO_SIZE 6
#define MAX_INT 999999

class info {
public:
	//Default constructor
	info() :visited_{ false }, distance_{ MAX_INT }, parent_{ "x" } {}
	//Regular constructor
	info(std::string name, bool visited, float distance, std::string parent) :
		name_{ name }, visited_{ visited }, distance_{ distance }, parent_{ parent } {}
	//Getters
	std::string getName() { return name_; }
	bool getVisit() { return visited_; }
	float getDist() { return distance_; }
	std::string getParent() { return parent_; }
	//Setters
	void setName(std::string name) { this->name_ = name; }
	void setVisit(bool visited) { this->visited_ = visited; }
	void setDist(float distance) { this->distance_ = distance; }
	void setParent(std::string parent) { this->parent_ = parent; }
private:
	std::string name_;
	bool visited_;
	float distance_;
	std::string parent_;
};

class adjListNode {
public:
	//Constructor
	adjListNode(std::string name, float weight) :weight_{ weight }, name_{ name }, next_{ nullptr } {}
	//Getters
	float getWeight() { return weight_; }
	std::string getName() { return name_; }
	adjListNode* getNext() { return next_; }
	//Setters
	void setName(std::string name) { this->name_ = name; }
	void setWeight(int weight) { this->weight_ = weight; }
	void setNext(adjListNode* next) { this->next_ = next; }
private:
	float weight_;
	std::string name_;
	adjListNode* next_;
};

struct adjList {
	adjListNode* head;
};

void recurs(adjList*x, info* arr, int adjSize, int infoSize, std::string source);
void bFord(adjList*x, info* arr, int adjSize, int infoSize, std::string source);
void populate(adjList* test, info* arr);
int find(info* tarr, size_t size, std::string nodeName);

int main() {
	adjList test[ADJ_SIZE];
	info arr[INFO_SIZE];
	populate(test, arr);
	bFord(test, arr, ADJ_SIZE, INFO_SIZE, "bellman-ford");
}


void populate(adjList* test, info* arr) {

	adjListNode
		*B2 = new adjListNode("baran", 27.637),
		*B1 = new adjListNode("lovelace", 141.632),
		*B = new adjListNode("bellman-ford", MAX_INT);
	B1->setNext(B2);
	B->setNext(B1);


	adjListNode
		*L2 = new adjListNode("hopper", 142.675),
		*L1 = new adjListNode("knuth", 125.654),
		*L = new adjListNode("lovelace", MAX_INT);
	L1->setNext(L2);
	L->setNext(L1);


	adjListNode
		*K3 = new adjListNode("cerf", 196.626),
		*K2 = new adjListNode("hopper", 105.593),
		*K1 = new adjListNode("lovelace", 125.654),
		*K = new adjListNode("knuth", MAX_INT);
	K2->setNext(K3);
	K1->setNext(K2);
	K->setNext(K1);


	adjListNode
		*H3 = new adjListNode("lovelace", 142.675),
		*H2 = new adjListNode("knuth", 105.593),
		*H1 = new adjListNode("cerf", 127.624),
		*H = new adjListNode("hopper", MAX_INT);
	H2->setNext(H3);
	H1->setNext(H2);
	H->setNext(H1);


	adjListNode
		*C3 = new adjListNode("hopper", 127.624),
		*C2 = new adjListNode("knuth", 196.626),
		*C1 = new adjListNode("baran", 118.631),
		*C = new adjListNode("cerf", MAX_INT);
	C2->setNext(C3);
	C1->setNext(C2);
	C->setNext(C1);


	adjListNode
		*X1 = new adjListNode("cerf", 118.631),
		*X = new adjListNode("baran", MAX_INT);
	X->setNext(X1);
	
	test[0].head = B;
	test[1].head = L;
	test[2].head = X;
	test[3].head = K;
	test[4].head = H;
	test[5].head = C;

	arr[0].setName("bellman-ford");
	arr[1].setName("lovelace");
	arr[2].setName("baran");
	arr[3].setName("knuth");
	arr[4].setName("hopper");
	arr[5].setName("cerf");
	return;
}

int find(info tarr[], size_t size, std::string nodeName) {
	size_t h = 0;
	while (tarr[h].getName() != nodeName)
		h++;
	if (tarr[h].getName() == nodeName)
		return h;
	else
		return -1;
}

void recurs(adjList*x, info* arr, int adjSize, int infoSize, std::string source) {
	int r = find(arr, 50, source);
	if (r == -1)
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

void bFord(adjList*x, info* arr, int adjSize, int infoSize, std::string source) {
	std::cout << "CN           B-Ford\t\tLovelace\tBaran\t\tKnuth\t\tHopper\t\tCerf" << std::endl;
	int i = 0;
	while (arr[i].getName() != source && i < adjSize)	//finds source node and marks it was visited
		i++;
	int pos = i;
	arr[i].setDist(0);
	arr[i].setVisit(true);
	std::cout << source << ": ";
	for (int p = 0; p < adjSize; p++)
		std::cout << "\t"<< arr[p].getDist() << "\t";
	std::cout << std::endl;
	//loops n node times
	for (int j = 0; j < adjSize; j++) {
		int min = MAX_INT;
		//recurs function goes to current node, updates it's neighbors if smaller,
		//and recurses through the intermediate nodes
		recurs(x, arr, adjSize, infoSize, source);
		//Finds next min for next node
		for (int u = 0; u < adjSize; u++) {
			if (arr[u].getVisit() == false && arr[u].getDist() < min) {
				min = arr[u].getDist();
				pos = u;
			}
		}
		//prints the known smallest distances after updating a node
		if(source == "baran" || source == "knuth" || source == "cerf")
			std::cout << source << ":     ";
		else
		std::cout << source << ": ";
		for (int p = 0; p < adjSize; p++)
			std::cout<<"\t" << arr[p].getDist() << "\t";

		std::cout << std::endl;
		source = arr[pos].getName();
		arr[pos].setVisit(true);
		//cout << arr[pos].name << " " <<arr[pos].distance <<endl;
	}
	std::ofstream filer;
	filer.open("temp.txt");
	for (int k = 0; k < INFO_SIZE; k++)
		filer << arr[k].getName() << " " <<arr[k].getParent() << " " << arr[k].getDist() << std::endl;

	filer.close();

}
