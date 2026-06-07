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
	list->tail->next = newNode;
	list->tail = newNode;
	newNode->next = list->head;

	newNode->name = name;
	newNode->hp = hp;
	newNode->mp = mp;
	newNode->speed = speed;
	newNode->range = range;
	newNode->position = position;

	return;
	
}

void toNode(List* list, int size, Champion champs[]) {
	for (int i = 0; i < size; i++) {
		Insert(list, champs[i].name, champs[i].hp, champs[i].mp, champs[i].speed, champs[i].range, champs[i].position);
	}
}

void PrintAll(List list) {
	Node* current = list.head->next;
	while (current!= list.head) {
		cout << current->name << endl
		<< current->hp << endl
		<< current->mp << endl
		<< current->speed << endl
		<< current->range << endl
		<< current->position << endl<<endl;
		current = current->next;
	}
}

void Search(List list, string name) {
	Node* current = list.head->next;
	while (current != list.head) {
		if (current->name == name) {
			cout << current->name << endl
				<< current->hp << endl
				<< current->mp << endl
				<< current->speed << endl
				<< current->range << endl
				<< current->position << endl << endl;
			return;
		}current = current->next;
	}cout << "챔피언이 존재하지 않습니다.";
}

void Delete(List* list, string name) {
	Node* current = list->head;
	while (current->next != list->head) {
		if (current->next->name == name) {
			Node* del = current->next;
			if (list->tail == del) {
				list->tail = current;
			}
			current->next = current->next->next;
			delete del;
			cout << "삭제완료";
			return;
		}current = current->next;
	}cout << "챔피언이 존재하지 않습니다.";
}

void DeleteAll(List* list, string position) {
	bool dele = false;
	Node* current = list->head;
	while (current->next != list->head) {
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
	}
	else {
		cout << "삭제할 챔피언이 없습니다." << endl;
	}
}

void FindMaxHp(List list) {
	Node* current = list.head->next;
	Node* max = current;
	while (current->next != list.head) {
		if (max->hp < current->next->hp) {
			max = current->next;
		}current = current->next;
	}
	cout << "가장 hp가 높은 챔피언은 " << max->name << "이고 hp는 " << max->hp << "입니다." << endl;
}

void SortByHp(List* list) {        // prev current current->next current->next->next
	bool swapped = true;
	Node* boundary = list->head;

	while (swapped) {
		swapped = false;
		Node* prev = list->head;
		Node* current = prev->next;
		while (current->next != boundary) {
			if (current->hp < current->next->hp) {
				Node* final = current->next->next;
				prev->next = current->next;
				current->next->next = current;
				current->next = final;
				prev = prev->next;
				swapped = true;
			}
			else {
				prev = current;
				current = current->next;
			}
		}boundary = current;
	}cout << "정렬 완료" << endl;
}





int main(){
	List list;
	list.head = new Node;
	list.tail = list.head;
	list.head->next = list.head;

	Champion champs[] = {
		{"이름1", 10, 20, 30, 40, "runner"},
		{"이름2", 30, 20, 10, 30, "soccer"},
		{"이름3", 20, 30, 20, 10, "runner"},
		{"이름4", 50, 20, 30, 20, "singer"},
		{"이름5", 15, 20, 30, 20, "artist"}
	};

	int size = sizeof(champs) / sizeof(champs[0]);

	toNode(&list, size, champs);

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
		else if (command == "Insert") {
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
				cin.ignore(10000, '\n');
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
		else {
			cout << "잘못된 명령어 입니다." << endl;
		}
	}
}