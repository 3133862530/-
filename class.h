#ifndef CLASS_H
#define CLASS_H
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h> 
using namespace std;

extern int OpeningHour;
extern int OpeningMintue;
extern int MAXTIME;
extern int Multiple;
extern int cNum;
extern int sNum;
extern string InPut;

class client {
private:
	string Name; // 姓名
	int Phone[11]; // 电话号码
	bool Kind; // false是普通业务，true是特殊业务
	string Id; // 身份证号
	int Arrtime; // 到达时间
	int Reqtime; // 所需时长
	int Waittime; // 逗留时间
	bool WinKind; // 办理业务的窗口类型
	int WinNum; // 办理业务的窗口编号
public:
	client():Waittime(-1), WinKind(false), WinNum(-1) {}
	client(string name, int* phone, bool kind, string id, int arrtime, int reqtime);
	client(const client& c);
	~client() {}
	client& operator=(const client& other);
	string getName()const;
	void getPhone(int* p)const;
	bool getKind()const;
	string getId()const;
	int getArrtime()const;
	int getReqtime()const;
	int getWaittime()const;
	bool getWinKind()const;
	int getWinNum()const;
	void setName(string name);
	void setPhone(int* phone);
	void setKind(bool kind);
	void setId(string id);
	void setArrtime(int arrtime);
	void setReqtime(int reqtime);
	void setWaittime(int waittime);
	void setWinKind(bool winkind);
	void setWinNum(int winnum);
};

class windows {
public:
	int Number; // 窗口编号
	int AvailTime; // 办理完当前用户业务的时间
	bool Kind; // false是普通业务，true是特殊业务
	int Cusnum; // 在此窗口办理业务的客户人数
	windows() :AvailTime(0), Cusnum(0) {}
	windows(int number, bool kind);
	~windows() {}
	void conduct(client& c, int time, int& num, double& totalTime);
};

class node {
public:
	client C;
	node* Next;
	node() :Next(nullptr) {}
	node(const client& c);
	node(const client& c, node* next);
	~node() {}
};

class queue {
public:
	node* Head;
	node* Tail;
	queue() :Head(nullptr), Tail(nullptr) {}
	~queue();
	void init();
	bool empty();
	client front();
	void enqueue(const client& c);
	void dequeue(client& c);
};

class nameList {
private:
	string* data; // 指向动态分配数组的指针
	int capacity; // 数组的容量
	int length;   // 数组中当前存储的元素数量
public:
	nameList();
	~nameList();
	void push_back(const string& value);
	void pop_back();
	string& operator[](int index);
	const string& operator[](int index) const;
	int size() const;
	void resize(int new_capacity);
};

class winList {
private:
	windows* data;// 指向动态分配数组的指针
	int capacity; // 数组的容量
	int length;   // 数组中当前存储的元素数量
public:
	winList();
	~winList();
	void push_back(const windows& value);
	windows& operator[](int index);
	int size() const;
	void resize(int new_capacity);
};

#endif
