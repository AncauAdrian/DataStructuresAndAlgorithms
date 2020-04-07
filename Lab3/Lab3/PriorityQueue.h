#include <utility>

typedef int TElem;

typedef int TPriority;



typedef std::pair<TElem, TPriority> Element;



typedef bool (*Relation)(TPriority p1, TPriority p2);


struct Node {
	Element e;
	Node *next = nullptr;
};


class PriorityQueue {

private:

	//representation of PriorityQueue

	Relation rel;
	Node *head;

public:

	//implicit constructor

	PriorityQueue(Relation r);



	//adds an element with priority to the queue

	void push(TElem e, TPriority p);



	//returns the element with the highest priority with respect to the order relation

	//throws exception if the queue is empty

	Element top()  const;



	//removes and returns the element with the highest priority

	//throws exception if the queue is empty

	Element pop();



	//checks if the queue is empty

	bool isEmpty() const;



	//destructor

	~PriorityQueue();



};