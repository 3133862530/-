#include"class.h"

// 默认开业时间为8点，营业时长为480分，办理一般业务的客户人数是特殊业务的10倍，一般窗口10个，特殊窗口2个
int OpeningHour = 8;
int OpeningMintue = 0;
int MAXTIME = 480;
int Multiple = 10;
int cNum = 10;
int sNum = 2;
string InPut = "D:\\input.txt";

client::client(string name, int* phone, bool kind, string id, int arrtime, int reqtime):Waittime(-1), WinKind(false), WinNum(-1),
Name(name), Kind(kind), Id(id), Arrtime(arrtime), Reqtime(reqtime) {
	for (int i = 0; i < 11; i++) {
		Phone[i] = phone[i];
	}
}

client::client(const client& c):Waittime(-1), WinKind(false), WinNum(-1) {
	*this = c;
}

client& client::operator=(const client& other) {
	if (this == &other) {
		return *this;
	}
	this->Arrtime = other.Arrtime;
	this->Id = other.Id;
	this->Kind = other.Kind;
	this->Name = other.Name;
	this->Reqtime = other.Reqtime;
	this->Waittime = other.Waittime;
	this->WinNum = other.WinNum;
	this->WinKind = other.WinKind;
	for (int i = 0; i < 11; i++) {
		this->Phone[i] = other.Phone[i];
	}
}

string client::getName() const {
	return Name;
}

void client::getPhone(int* p) const {
	for (int i = 0; i < 11; i++) {
		p[i] = Phone[i];
	}
}

bool client::getKind() const {
	return Kind;
}

string client::getId() const {
	return Id;
}

int client::getArrtime() const {
	return Arrtime;
}

int client::getReqtime() const {
	return Reqtime;
}

int client::getWaittime() const {
	return Waittime;
}

bool client::getWinKind() const {
	return WinKind;
}

int client::getWinNum() const {
	return WinNum;
}

void client::setName(string name) {
	Name = name;
}

void client::setPhone(int* phone) {
	for (int i = 0; i < 11; i++) {
		Phone[i] = phone[i];
	}
}

void client::setKind(bool kind) {
	Kind = kind;
}

void client::setId(string id) {
	Id = id;
}

void client::setArrtime(int arrtime) {
	Arrtime = arrtime;
}

void client::setReqtime(int reqtime) {
	Reqtime = reqtime;
}

void client::setWaittime(int waittime) {
	Waittime = waittime;
}

void client::setWinKind(bool winkind) {
	WinKind = winkind;
}

void client::setWinNum(int winnum) {
	WinNum = winnum;
}

windows::windows(int number, bool kind) :Number(number), Kind(kind), AvailTime(0), Cusnum(0) {}

void windows::conduct(client& c,int time, int& num, double& totalTime) {
	Cusnum++;
	AvailTime = time + c.getReqtime();
	num++;
	c.setWaittime(AvailTime - c.getArrtime());
	totalTime += c.getWaittime();
	c.setWinKind(Kind);
	c.setWinNum(Number);
}

node::node(const client& c, node* next) :C(c), Next(next) {}

node::node(const client& c) :C(c), Next(nullptr) {}

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

client queue::front() {
	return Head->C;
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

nameList::nameList() : data(nullptr), capacity(0), length(0) {}
nameList::~nameList() {
	delete[] data;
}

void nameList::push_back(const string& value) {
	if (length == capacity) { // 如果当前长度等于容量，需要扩容
		resize(capacity == 0 ? 1 : capacity * 2); // 容量翻倍或初始化为1
	}
	data[length++] = value;
}

void nameList::pop_back() {
	if (length > 0) {
		--length;
	}
}

string& nameList::operator[](int index) {
	return data[index];
}

const string& nameList::operator[](int index) const {
	return data[index];
}

int nameList::size() const {
	return length;
}

void nameList::resize(int new_capacity) {
	string* new_data = new string[new_capacity];
	for (int i = 0; i < length; i++) {
		new_data[i] = data[i];
	}
	delete[] data;
	data = new_data;
	capacity = new_capacity;
}

winList::winList() : data(nullptr), capacity(0), length(0) {}
winList::~winList() {
	delete[] data;
}

void winList::push_back(const windows& value) {
	if (length == capacity) { // 如果当前长度等于容量，需要扩容
		resize(capacity == 0 ? 1 : capacity * 2); // 容量翻倍或初始化为1
	}
	data[length++] = value;
}

windows& winList::operator[](int index) {
	return data[index];
}

int winList::size() const {
	return length;
}

void winList::resize(int new_capacity) {
	windows* new_data = new windows[new_capacity];
	for (int i = 0; i < length; i++) {
		new_data[i] = data[i];
	}
	delete[] data;
	data = new_data;
	capacity = new_capacity;
}