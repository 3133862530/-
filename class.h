#ifndef CLASS_H
#define CLASS_H

#include <iostream>
using namespace std;

extern int OpeningHour;
extern int OpeningMintue;
extern int MAXTIME;

class client {
private:
	string Name; // ����
	int Phone[11]; // �绰����
	bool Kind; // 0����ͨҵ��1������ҵ��
	string Id; // ���֤��
	int Arrtime; // ����ʱ��
	int Reqtime; // ����ʱ��
public:
	client() {}
	client(string name, int* phone, bool kind, string id, int arrtime, int reqtime);
	client(const client& c);
	~client() {}
	void infomation(client& c);
	void getName(string& n);
	void getPhone(int* p);
	void getKind(bool& k);
	void getId(string& i);
	void getArrtime(int& a);
	void getReqtime(int& r);
};

class windows :public client {
private:
	int Number; // ���ڱ��
	bool Kind; // 0����ͨҵ��1������ҵ��
	bool Available; // 0Ϊ���У�1Ϊ���ڰ���
	client Customer; // ���ڰ���ҵ��Ŀͻ�
public:
	windows() :Available(false) {}
	windows(int number, bool kind);
	~windows() {}
	void conduct(const client& c);
};

class node :public client {
public:
	client C;
	node* Next;
	node() :Next(nullptr) {}
	node(const client& c);
	node(const client& c, node* next);
	~node() {}
};

class queue :public node {
public:
	node* Head;
	node* Tail;
	queue() :Head(nullptr), Tail(nullptr) {}
	~queue();
	void init();
	bool empty();
	void enqueue(const client& c);
	void dequeue(client& c);
};

#endif
