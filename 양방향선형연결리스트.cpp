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
	Node* prev;
};

struct List {
	Node* head;
};

void Insert(List* list, string name, int hp, int mp, int speed, int range, string position) {
	Node* newNode = new Node;
	newNode->next = list->head;
	newNode->prev = list->head->prev;
	list->head->prev->next = newNode;
	list->head->prev = newNode;

	newNode->name = name;
	newNode->hp = hp;
	newNode->mp = mp;
	newNode->speed = speed;
	newNode->range = range;
	newNode->position = position;
}


void toNode(List*list, int size, Champion champs[]) {
	for (int i = 0; i < size; i++) {
		Insert(list, champs[i].name, champs[i].hp, champs[i].mp, champs[i].speed, champs[i].range, champs[i].position);
	}
}

void PrintAll(List list) {
	Node* current = list.head->next;
	while (current != list.head) {
		cout << current->name << endl
			<< current->hp << endl
			<< current->mp << endl
			<< current->speed << endl
			<< current->range << endl
			<< current->position << endl << endl;
		current = current->next;
	}
}

void Delete(List* list, string name) {
	Node* current = list->head->next;
	while (current != list->head) {
		if (current->name == name) {
			Node* del = current;
			current->prev->next = current->next;
			current->next->prev = current->prev;
			delete del;
			cout << "삭제 완료";
			return;
		}current = current->next;
	}cout << "삭제할 챔피언을 찾을 수 없습니다.";
}

void DeleteAll(List* list, string position) {
	Node* current = list->head->next;
	bool dele = false;
	while (current != list->head) {
		if (current->position == position) {
			Node* del = current;
			current->prev->next = current->next;
			current->next->prev = current->prev;
			current = current->next;
			delete del;
			dele = true;
		}
		else { current = current->next; }
	}
	if (dele) {
		cout << "해당 포지션 삭제 완료" << endl;
	}
	else {
		cout << "해당 포지션을 찾을 수 없습니다." << endl;
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

	cout << "hp가 가장 높은 챔피언은 " << max->name << "이고 hp는 " << max->hp << "입니다." << endl;
}


void SortByHp(List* list) {                 // current->prev, current, next, final
	                                        // current->prev, next, current, final
	bool swapped = true;
	Node* boundary = list->head;

	while (swapped) {
		swapped = false;
		Node* current = list->head->next;
		Node* next = current->next;
		while (next != boundary) {
			if (current->hp < next->hp) {
				Node* final = next->next;
				current->prev->next = next;
				next->prev = current->prev;
				next->next = current;
				current->prev = next;
				current->next = final;
				final->prev = current;
				next = current->next;
				swapped = true;
			}
			else {
				current = current->next;
				next = current->next;
			}
		}boundary = current;
	}cout << "정렬이 완료되었습니다." << endl;
}




int main() {

	List list;
	list.head = new Node;
	list.head->next = list.head;
	list.head->prev = list.head;

	Champion champs[] = {
		{"이름1", 10, 20, 30, 40, "runner"},
		{"이름2", 50,30, 20, 3, "soccer"},
		{"이름3", 20, 20,20, 20, "soccer"},
		{"이름4", 60,20,20,20, "artist"},
		{"이름5", 70, 20, 20, 20, "runner"}
	};

	int size = sizeof(champs) / sizeof(champs[0]);

	toNode(&list, size, champs);


	string command;
	
	while (true) {
		cout << "command>>";
		cin >> command;
		if (command == "PrintAll") {
			PrintAll(list);
			continue;
		}
		if (command == "Insert") {
			cout << "name>>";
			string name;
			cin >> name;

			cout << "hp>>";
			int hp;
			while (!(cin >> hp)) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력 가능합니다. hp>>";
			}

			cout << "mp>>";
			int mp;
			while (!(cin >> mp)) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력 가능합니다. mp>>";
			}

			cout << "speed>>";
			int speed;
			while (!(cin >> speed)) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력 가능합니다. speed>>";
			}

			cout << "range>>";
			int range;
			while (!(cin >> range)) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력 가능합니다. range>>";
			}

			cout << "position>>";
			string position;
			cin >> position;

			Insert(&list, name, hp, mp, speed, range, position);
			continue;
		}
		else if (command == "Delete") {
			cout << "name>>";
			string name;
			cin >> name;
			Delete(&list, name);
			continue;
		}
		else if (command == "DeleteAll") {
			cout << "position>>";
			string position;
			cin >> position;
			DeleteAll(&list, position);
			continue;
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
			cout << "잘못된 입력입니다.";
		}


	}
	


}