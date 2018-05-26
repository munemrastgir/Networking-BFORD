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
void populate(adjList* test, info* arr, double a,double b,double c,double d,double e, double f, double g, double h);
int find(info* tarr, size_t size, std::string nodeName);

int main() {
	adjList test[ADJ_SIZE];
	info arr[INFO_SIZE];
	int choice;
	double a = 27.637, b = 141.632, c = 142.675, d = 125.654, e = 196.626, f = 105.593, g = 127.624, h = 118.631;
	std::cout << "Press 1 to run the code on our Values, or press 2 enter your own values" << std::endl;
	while (std::cin >> choice) {
		if (choice == 1)
		{
			populate(test, arr,a,b,c,d,e,f,g,h);
			break;
		}
		else if (choice == 2)
		{
			std::cout << "Enter distance from bellman-ford to baran" << std::endl;
			std::cin >> a;
			std::cout << "Enter distance from bellman-ford to lovelace" << std::endl;
			std::cin >> b;
			std::cout << "Enter distance from lovelace to hopper" << std::endl;
			std::cin >> c;
			std::cout << "Enter distance from lovelace to knuth" << std::endl;
			std::cin >> d;
			std::cout << "Enter distance from knuth to cerf" << std::endl;
			std::cin >> e;
			std::cout << "Enter distance from knuth to hopper" << std::endl;
			std::cin >> f;
			std::cout << "Enter distance from hopper to cerf" << std::endl;
			std::cin >> g;
			std::cout << "Enter distance from cerf to baran" << std::endl;
			std::cin >> h;
			populate(test, arr, a, b, c, d, e, f, g, h);
			break;
		}
	}
	bFord(test, arr, ADJ_SIZE, INFO_SIZE, "bellman-ford");
}


void populate(adjList* test, info* arr, double a, double b, double c, double d, double e, double f, double g, double h) {
	adjListNode
		*B2 = new adjListNode("baran", a),
		*B1 = new adjListNode("lovelace", b),
		*B = new adjListNode("bellman-ford", MAX_INT);
	B1->setNext(B2);
	B->setNext(B1);


	adjListNode
		*L2 = new adjListNode("hopper", c),
		*L1 = new adjListNode("knuth", d),
		*L = new adjListNode("lovelace", MAX_INT);
	L1->setNext(L2);
	L->setNext(L1);


	adjListNode
		*K3 = new adjListNode("cerf", e),
		*K2 = new adjListNode("hopper", f),
		*K1 = new adjListNode("lovelace", d),
		*K = new adjListNode("knuth", MAX_INT);
	K2->setNext(K3);
	K1->setNext(K2);
	K->setNext(K1);


	adjListNode
		*H3 = new adjListNode("lovelace", c),
		*H2 = new adjListNode("knuth", f),
		*H1 = new adjListNode("cerf", g),
		*H = new adjListNode("hopper", MAX_INT);
	H2->setNext(H3);
	H1->setNext(H2);
	H->setNext(H1);


	adjListNode
		*C3 = new adjListNode("hopper", g),
		*C2 = new adjListNode("knuth", e),
		*C1 = new adjListNode("baran", h),
		*C = new adjListNode("cerf", MAX_INT);
	C2->setNext(C3);
	C1->setNext(C2);
	C->setNext(C1);


	adjListNode
		*X1 = new adjListNode("cerf", h),
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

int find(info* tarr, size_t size, std::string nodeName) {
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
	std::cout << "Current Node  B-Ford\t\tLovelace\tBaran\t\tKnuth\t\tHopper\t\tCerf" << std::endl;
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
	std::cout << "Enter a node name to get its path" << std::endl;
	std::string location;
	std::string arrloc[50];
	while (std::cin >> location)
	{
		int arrp = 0;
		int atmp = find(arr, 50, location);
		if (atmp == -1) std::cout << "Not a valid location, try again" << std::endl;
		else {
			arrloc[arrp] = arr[atmp].getName();
			arrp++;
			while (arr[atmp].getParent() != "x") {
				arrloc[arrp] = arr[atmp].getParent();
				arrp++;
				atmp = find(arr, 50, arr[atmp].getParent());
			}
			for (int q = arrp-1; q >= 0; q--)
				std::cout << arrloc[q] << "->";
			std::cout << std::endl;
		}
		std::cout << "Enter another location" << std::endl;
	}
	/*std::ofstream filer;
	filer.open("temp.txt");
	for (int k = 0; k < INFO_SIZE; k++)
		filer << arr[k].getName() << " " <<arr[k].getParent() << " " << arr[k].getDist() << std::endl;

	filer.close();*/

}
