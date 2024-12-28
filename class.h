#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

extern int OpeningHour;
extern int OpeningMintue;
extern int MAXTIME;
extern string InPut;
extern string OutPut;

class client {
private:
	string Name; // ����
	int Phone[11]; // �绰����
	bool Kind; // false����ͨҵ��true������ҵ��
	string Id; // ���֤��
	int Arrtime; // ����ʱ��
	int Reqtime; // ����ʱ��
	int Waittime; // ����ʱ��
	bool WinKind; // ����ҵ��Ĵ�������
	int WinNum; // ����ҵ��Ĵ��ڱ��
public:
	client() {}
	client(string name, int* phone, bool kind, string id, int arrtime, int reqtime);
	client(const client& c);
	~client() {}
	client& operator=(const client& other);
	string getName();
	void getPhone(int* p);
	bool getKind();
	string getId();
	int getArrtime();
	int getReqtime();
	int getWaittime();
	bool getWinKind();
	int getWinNum();
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
	int Number; // ���ڱ��
	int AvailTime; // �����굱ǰ�û�ҵ���ʱ��
	bool Kind; // false����ͨҵ��true������ҵ��
	client Customer; // ���ڰ���ҵ��Ŀͻ�
	windows() :AvailTime(0) {}
	windows(int number, bool kind);
	~windows() {}
	void conduct(client c, int time, int& num, double& totalTime);
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
	string* data; // ָ��̬���������ָ��
	int capacity; // ���������
	int length;   // �����е�ǰ�洢��Ԫ������
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
	windows* data;// ָ��̬���������ָ��
	int capacity; // ���������
	int length;   // �����е�ǰ�洢��Ԫ������
public:
	winList();
	~winList();
	void push_back(const windows& value);
	windows& operator[](int index);
	int size() const;
	void resize(int new_capacity);
};

#endif
