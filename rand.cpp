#include "rand.h"

int randnum(int lower, int upper) {
    // ���������������
    mt19937 rng;
    // ʹ��ϵͳʱ����Ϊ����
    auto seed = chrono::steady_clock::now().time_since_epoch().count();
    rng.seed(static_cast<unsigned long>(seed));
    // ���������
    uniform_int_distribution<int> dist(lower, upper); // ����ֲ���Χ
    return dist(rng);
}

// ����绰����
void randphone(int* phone) {
    // ��һλΪ1
    phone[0] = 1;
    // ����ʣ���10������
    for (int i = 1; i < 11; i++) {
        // �������������
        phone[i] = randnum(0, 9);
    }
}

// ����������֤��
string randid() {
    string id;
    id = '0' + randnum(1, 9);
    for (int i = 1; i < 17; i++) {
        id += '0' + randnum(0, 9);
    }
    int x = rand();
    if (x % 11) {
        id += '0' + randnum(0, 9);
    }
    else {
        id += 'X';
    }
    return id;
}

// �������
void randinput(queue& cq, queue& sq) {
    int pretime = 0; // ��һλ�ͻ������ʱ��
    // ���ļ�
    ifstream file("names.txt");
    if (!file.is_open()) {
        cerr << "�޷����ļ�" << endl;
    }
    // ��ȡ�ļ��е���������
    nameList names;
    string name;
    while (getline(file, name)) {
        names.push_back(name);
    }
    file.close();
    for (int i = 0; pretime < MAXTIME; i++) {
        int index = randnum(0, names.size() - 1);
        string randName = names[index];
        int phone[11];
        randphone(phone);
        bool kind = randnum(0, Multiple) ? false : true; // �����Ϊ0��kindΪtrue
        string id = randid();
        int arrtime = randnum(0, 1); // ����1����֮�ڱض�������һλ�ͻ�
        arrtime += pretime;
        pretime = arrtime;
        int reqtime;
        if (kind) {
            reqtime = randnum(1, 15);
        }
        else {
            reqtime = randnum(1, 5);
        }
        client newc(randName, phone, kind, id, arrtime, reqtime);
        if (kind)sq.enqueue(newc);
        else cq.enqueue(newc);
    }
    filewrite(InPut, cq, false);
    filewrite(InPut, sq, false);
}