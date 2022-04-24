#include <iostream>
#include<ctime>
#include<stack>

using namespace std;

class Node {
public:
	int value;
	Node *next, *lower;
	Node(int val) {
		value = val;
		next = NULL;
		lower = NULL;
	}
};

class Skiplist {
private:
	Node *head;
	int Nnodes, level;
public:
	Skiplist() {
		head = new Node(-1);
		Nnodes = 0;
		level = 1;
		srand(time(0));
	}

	void insert(int num) {
		stack<Node*> s;
		Node *ptr = head;
		while (ptr) {
			while (ptr->next && ptr->next->value <= num)
				ptr = ptr->next;
			s.push(ptr);
			ptr = ptr->lower;
		}
		Node *last = NULL;
		while (!s.empty()) {
			ptr = s.top();
			s.pop();
			Node *node = new Node(num);
			node->lower = last;
			node->next = ptr->next;
			ptr->next = node;
			last = node;
			int p = rand() % 2;
			if (p==0)
				break;
		}
		Nnodes++;
		if (s.empty()) {
			float max = log2(Nnodes) + 1;
			while (level <= max) {
				//int p = rand() % 2;
				//if (p==0) 
				//	break;
				Node *nhead = new Node(-1);
				nhead->lower = head;
				head = nhead;
				Node *node = new Node(num);
				node->lower = last;
				last = node;
				nhead->next = node;
				level++;
			}
		}
	}

	void printLayers(int lay) {
		int v=level-lay;
		Node *node = head;
		while (v > 0) {
			node = node->lower;
			v--;
		}
		if (lay > 0 && lay <= level) {
			while (node->next) {
				node = node->next;
				cout << node->value << " ";
			}
			cout << "\n";
		}
		else
			cout<<"invalid number of layers\n";
	}

	void display() {
		Node *node = head,*ptr=head;
		while (node&&ptr) {
			node = ptr;
			cout << endl << node->value << "---";
			while (node->next) {
				node = node->next;
				cout << node->value<<"---";
			}
			ptr = ptr->lower;
		}
		cout << endl;
	}

	int search(int target) {
		int steps = 0;
		Node *node = head;
		while (node) {
			while (node->next && node->next->value < target) {
				steps++;
				node = node->next;
			}
			if (node->next && node->next->value == target) {
				steps++;
				cout << "the number of steps taken to find " << target << " are: " << steps << endl;
				return steps;
			}
			steps++;
			node = node->lower;
		}
		cout << "element doesn't exist\n";
		return -1;
	}

	void getLayers() {
		cout << level << endl;
	}

	bool erase(int num) {
		Node *node = head;
		bool ans = false;
		while (node) {
			while (node->next && node->next->value < num)
				node = node->next;
			if (node->next && node->next->value == num) {
				node->next = node->next->next;
				ans = true;
			}
			node = node->lower;
		}
		return ans;
	}
};
int main()
{
	Skiplist* mylist = new Skiplist();
	int choice = 0, num = 0,f;
	bool  p = false;
	while (choice != 7) {
		cout << "main menu:\n1-insert element\n2-delete element\n3-find an element\n4-print the number of layers\n5-print the numbers of certain layer\n6-display\n7-exit\n";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "enter the number you want to add\n";
			cin >> num;
			mylist->insert(num);
			choice = 0;
			break;
		case 2:
			cout << "enter the number you want to delete\n";
			cin >> num;
			p = mylist->erase(num);
			if (p == false)
				cout << "failed\n";
			else
				cout << "Deleted successfully\n";
			choice = 0;
			break;
		case 3:
			cout << "enter the number you want to search for\n";
			cin >> num;
			f= mylist->search(num);
			choice = 0;
			break;
		case 4:
			mylist->getLayers();
			choice = 0;
			break;
		case 5:
			cout << "enter the value of the certain layer that you want its numbers:\n";
			cin >> f;
			mylist->printLayers(f);
			choice = 0;
			break;
		case 6:
			mylist->display();
			choice = 0;
			break;
		case 7:
			break;
		default:
			cout << "invalid, please enter a number from the range{0,7}\n";
			choice = 0;
			break;
		}
	}
}