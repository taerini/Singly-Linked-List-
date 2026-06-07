#include <iostream>
#include <string>
using namespace std;

struct Champion {
	string name;
	int hp;
	int mp;
	int speed;
	int range;
	string position;
};

struct Node {
	string name;
	int hp;
	int mp;
	int speed;
	int range;
	string position;
	Node* next;
};

struct List {
	Node* head;
	Node* tail;
};

void Insert(List* list, string name, int hp, int mp, int speed, int range, string position) {
	Node* newNode = new Node;
	newNode->name = name;
	newNode->hp = hp;
	newNode->mp = mp;
	newNode->speed = speed;
	newNode->range = range;
	newNode->position = position;

	list->tail->next = newNode;
	list->tail = newNode;
	newNode->next = NULL;
}

void Search(List list, string name) {
	Node* current = list.head->next;
	while (current != NULL) {
		if (current->name == name) {
			cout << current->name << endl
				<< current->hp << endl
				<< current->mp << endl
				<< current->speed << endl
				<< current->range << endl
				<< current->position << endl << endl;
			return;
		}current = current->next;
	} cout << "챔피언을 찾을 수 없습니다."<<endl;
}

void PrintAll(List list) {
	Node* current = list.head->next;
	while (current != NULL) {
		cout << current->name << endl
			<< current->hp << endl
			<< current->mp << endl
			<< current->speed << endl
			<< current->range << endl
			<< current->position << endl << endl;
		current = current->next;
	}
}

void toNode(int size, Champion champs[], List* list) {
	for (int i = 0; i < size; i++) {
		Insert(list, champs[i].name, champs[i].hp, champs[i].mp, champs[i].speed, champs[i].range, champs[i].position);
	}
}

void Delete(List*list, string name) {
	Node* current = list->head;
	while (current->next != NULL) {
		if (current->next->name == name) {
			Node* del = current->next;
			if (list->tail == del) {
				list->tail = current;
			}
			current->next = current->next->next;
			delete del;
			cout << "삭제완료" << endl;
			return;
		}current = current->next;
	} cout << "챔피언을 찾을 수 없습니다." << endl;
}

void DeleteAll(List* list, string position) {
	bool dele = false;
	Node* current = list->head;
	while (current->next != NULL) {
		if (current->next->position == position) {
			Node* del = current->next;
			if (list->tail == del) {
				list->tail = current;
			}
			current->next = current->next->next;
			delete del;
			dele = true;
		}
		else {
			current = current->next;
		}
	}if (dele) {
		cout << "삭제 완료" << endl;
		return;
	}
	else {
		cout << "포지션이 존재하지 않습니다." << endl;
	}

}

void FindMaxHp(List list) {
	Node* current = list.head->next;
	Node* max = current;
	while (current->next != NULL) {
		if (max->hp < current->next->hp) {
			max = current->next;
		}
		current = current->next;
	}
	cout << "가장 hp가 큰 챔피언은 " << max->name << "이고, hp는 " << max->hp << "입니다." << endl;
}


void SortByHp(List*list) {         //prev, current, current->next, current->next->next
	                               //prev, current->next, current, current->next->next
	                               //    , prev, current
	Node* boundary = NULL;
	bool swapped = true;

	while (swapped) {
		swapped = false;
		Node* prev = list->head;
		Node* current = prev->next;
		while (current->next != boundary) {
			if (current->hp < current->next->hp) {
				Node* lastNode = current->next->next;
				prev->next = current->next;
				current->next->next = current;
				current->next = lastNode;
				prev = prev->next;
				swapped = true;
			}
			else {
				prev = current;
				current = current->next;
			}
		} boundary = current;

	}
	cout << "정렬 완료" << endl;


}


int main() {

	List list;
	list.head = new Node();
	list.head->next = NULL;
	list.tail = list.head;

	
	Champion champs[] = {
		{"이태린", 10, 20, 30, 40, "runner" },
		{"홍길동", 20, 40, 30, 20, "magic"},
		{"손흥민", 4, 30, 20, 20, "soccer" },
		{"둘리", 50,20,30,1,"dino"},
		{"하니",20,30,1,30,"runner"}
	};

	int size = sizeof(champs) / sizeof(champs[0]);

	toNode(size, champs, &list);

	while (true) {
		string command;
		cout << "command >> ";
		cin >> command;
		if (command == "PrintAll")
			PrintAll(list);
		else if (command == "Search") {
			cout << "name>>";
			string name;
			cin >> name;
			Search(list, name);
		}
		else if ( command == "Insert") {
			cout << "name>>";
			string name;
			cin >> name;

			cout << "hp>>";
			int hp;
			while (!(cin >> hp)) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "숫자만 입력 가능합니다. hp>>";
			}

			cout << "mp>>";
			int mp;
			while (!(cin >> mp)) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "숫자만 입력 가능합니다. mp>>";
			}

			cout << "speed>>";
			int speed;
			while (!(cin >> speed)) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "숫자만 입력 가능합니다. speed>>";
			}

			cout << "range>>";
			int range;
			while (!(cin >> range)) {
				cin.clear();
				cin.ignore(10000,'\n');
				cout << "숫자만 입력 가능합니다. range>>";
			}

			cout << "position>>";
			string position;
			cin >> position;

			Insert(&list, name, hp, mp, speed, range, position);

		}
		else if (command == "Delete") {
			cout << "name>>";
			string name;
			cin >> name;
			Delete(&list, name);
		}
		else if (command == "DeleteAll") {
			cout << "position>>";
			string position;
			cin >> position;
			DeleteAll(&list, position);
		}
		else if (command == "FindMaxHp") {
			FindMaxHp(list);
		}
		else if (command == "SortByHp") {
			SortByHp(&list);
		}
		else if (command == "Exit") {
			break;
		}
	}

}
