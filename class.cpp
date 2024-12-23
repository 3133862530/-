#include"class.h"


// 默认开业时间为8点，营业时长为480分
int OpeningHour = 8;
int OpeningMintue = 0;
int MAXTIME = 480;

client::client(string name, int* phone, bool kind, string id, int arrtime, int reqtime)
	: Name(name), Kind(kind), Id(id), Arrtime(arrtime), Reqtime(reqtime) {
	for (int i = 0; i < 11; i++) {
		Phone[i] = phone[i];
	}
}

client::client(const client& c) {
	this->Arrtime = c.Arrtime;
	this->Id = c.Id;
	this->Kind = c.Kind;
	this->Name = c.Name;
	this->Reqtime = c.Reqtime;
	for (int i = 0; i < 11; i++) {
		this->Phone[i] = c.Phone[i];
	}
}

void client::infomation(client& c) {
	c.Arrtime = this->Arrtime;
	c.Id = this->Id;
	c.Kind = this->Kind;
	c.Name = this->Name;
	c.Reqtime = this->Reqtime;
	for (int i = 0; i < 11; i++) {
		c.Phone[i] = this->Phone[i];
	}
}

void client::getName(string& n) {
	n = Name;
}

void client::getPhone(int* p) {
	for (int i = 0; i < 11; i++) {
		p[i] = Phone[i];
	}
}

void client::getKind(bool& k) {
	k = Kind;
}

void client::getId(string& i) {
	i = Id;
}

void client::getArrtime(int& a) {
	a = Arrtime;
}

void client::getReqtime(int& r) {
	r = Reqtime;
}

windows::windows(int number, bool kind) :Number(number), Kind(kind) {}

void windows::conduct(const client& c) {
	Customer = c;
	Available = 1;
}

node::node(const client& c, node* next) :Next(next) {
	C = c;
}

node::node(const client& c) :Next(nullptr) {
	C = c;
}

void queue::init() {
	while (Head != nullptr) {
		node* p = Head;
		Head = Head->Next;
		delete p;
	}
	Tail = nullptr;
}

bool queue::empty() {
	return Head == nullptr;
}

void queue::enqueue(const client& c) {
	node* newnode = new node(c);
	if (empty()) {
		Head = newnode;
		Tail = newnode;
	}
	else {
		Tail->Next = newnode;
		Tail = newnode;
	}
}

void queue::dequeue(client& c) {
	if (empty()) {
		return;
	}
	c = Head->C;
	node* p = Head;
	Head = Head->Next;
	if (Head == nullptr) {
		Tail = nullptr; // 队列现在为空
	}
	delete p;
}

queue::~queue() {
	init();
}

void queue::writeToFile(const string& filename) 
{
	std::ofstream outFile(filename, std::ios::out);
	if (!outFile) {
		cerr << "无法打开文件进行写入！" << endl;
		return;
	}
	node* current = Head;
	while (current != nullptr) {
		outFile << current->C.Name << '\n';
		for (int i = 0; i < 11; ++i) {
			outFile << current->C.Phone[i];
		}
		outFile << '\n';
		outFile << current->C.Kind << '\n';
		outFile << current->C.Id << '\n';
		outFile << current->C.Arrtime << '\n';
		outFile << current->C.Reqtime << '\n';
		current = current->Next;
	}
	outFile.close();
}

void queue::readFromFile(const string& filename) {
	std::ifstream inFile(filename, std::ios::in);
	if (!inFile) {
		cerr << "无法打开文件进行读取！" << endl;
		return;
	}
	init(); // 清空现有队列
	while (!inFile.eof()) {
		client tempClient;
		string name;
		string phoneStr;
		int phone[11];
		bool kind = false;
		string id;
		int arrtime, reqtime;

		if (!std::getline(inFile, name)) break;
		tempClient.Name = name;

		std::getline(inFile, phoneStr);
		for (int i = 0; i < 11; ++i) {
			phone[i] = phoneStr[i] - '0'; // 转换为整数
		}
		tempClient.Kind = kind;

		inFile >> kind;
		inFile.ignore(); // 忽略换行符


	}
}