# include "fileinput.h"

void getValidNumber(int& number) {
    while (true) {
        cin >> number;
        // ���������״̬���ж������Ƿ���Ч
        if (cin.fail() || number <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "������Ч����������������" << endl;
        }
        else break;
    }
}

void InputTime(int& h, int& m) {
    string time;
    bool OK = true;
    int t = 0;
    do {
        getline(cin, time);
        // ʹ�� stringstream �����ַ�������
        stringstream ss(time);
        char colon;
        if (!(ss >> h >> colon >> m)) {
            cout << "ʱ���ʽ�����밴�� 'HH:MM' �ĸ�ʽ����" << endl;
            OK = false;
        }
        else if (h < 0 || h > 23 || m < 0 || m > 59) {
            cout << "ʱ�����벻�Ϸ�������������" << endl;
            OK = false;
        }
        else {
            OK = true;
        }
    } while (!OK);
}

void inputPhone(int* phone) {
    do {
        string input;
        cin >> input; // ��ȡ��������

        if (input.length() != 11 || input[0] != '1') {
            cout << "�绰�������벻�Ϸ������������룺" << endl;
            
            
            
            continue;
        }
        bool flag = true;
        for (int j = 0; j < 11; ++j) {
            if (input[j] < '0' || input[j] > '9') {
                cout << "�绰�������벻�Ϸ������������룺" << endl;
                
                
                
                flag = false;
                break;
            }
            phone[j] = input[j] - '0'; // ���ַ�ת��Ϊ��Ӧ�����ֲ��洢
        }

        if (flag) {
            break; // �������Ϸ������˳�ѭ��
        }
    } while (true);
}

void inputId(string& id) {
    bool flag = false;
    do {
        flag = true;
        cin >> id; // ��ȡ��������
        if (id.size() == 18) {
            if (id[0] < '1' || id[0] > '9') {
                flag = false; // ��һ���ַ�����������1-9
            }

            for (int j = 1; j < 17; ++j) {
                if (id[j] < '0' || id[j] > '9') {
                    flag = false; // ��2����17λ����������
                    break;
                }
            }

            if (flag) {
                if ((id[17] < '0' || id[17] > '9') && id[17] != 'X') {
                    flag = false; // ��18λ���������ֻ�X
                }
            }

        }
        else {
            flag = false;
        }

        if (!flag) {
            cout << "���֤�����벻�Ϸ������������룺" << endl;
        }
    } while (!flag); // �������Ϸ������˳�ѭ��
}

void inputArrtime(int& arrtime, int& pretime) {
    int hours, minutes;
    bool Flag;
    do {
        cout << "�����뵽��ʱ�䣨��ʽ��HH:MM����" << endl;
        InputTime(hours, minutes);
        arrtime = (hours - OpeningHour) * 60 + (minutes - OpeningMintue);
        if (arrtime < 0 || arrtime >= MAXTIME) {
            Flag = true;
            cout << "ʱ�����벻�Ϸ�������������" << endl;
        }
        else if (arrtime < pretime) {
            Flag = true;
            cout << "����ʱ�䲻��С����һλ�ͻ�������������" << endl;
        }
        else {
            Flag = false;
            pretime = arrtime;
        }
    } while (Flag);
}

void inputReqtime(int& reqtime, const int& arrtime, const bool& kind) {
    bool Flag;
    int maxReq = kind ? 15 : 5;
    do {
        cout << "����������ʱ����" << endl;
        getValidNumber(reqtime);
        if (reqtime < 0 || reqtime > maxReq || reqtime + arrtime > MAXTIME) {
            Flag = true;
            cout << "ʱ�����벻�Ϸ�������������" << endl;
        }
        else Flag = false;
    } while (Flag);
}

void PrintTime(int h, int m) {
    cout << h << ":" << setw(2) << setfill('0') << m << endl;
}

void PrintClient(client c) {
    cout << "����Ϊ�ÿͻ�����Ϣ��" << endl;
    cout << "������" << c.getName() << endl;
    int phone[11];
    c.getPhone(phone);
    cout << "�绰���룺";
    for (int i = 0; i < 11; i++)
    {
        cout << phone[i];
    }
    cout << endl;
    cout << "���֤�ţ�" << c.getId() << endl;
    int hour = 0, minute = 0;
    minute = (c.getArrtime() % 60 + OpeningMintue);
    hour = (c.getArrtime() / 60 + OpeningHour);
    if (minute >= 60)
        minute -= 60, hour += 1;
    cout << "����ʱ�䣺";
    PrintTime(hour, minute);
    cout << "����ҵ�����ͣ�" << (c.getKind() ? "����" : "һ��") << "ҵ��" << endl;
    cout << "����ҵ������ʱ����" << c.getReqtime() << "��" << endl;
    if (c.getWaittime() >= 0) {
        cout << "����ʱ����" << c.getWaittime() << "��" << endl;
        cout << "����ҵ�񴰿ڣ�" << (c.getWinKind() ? "����" : "һ��") << "����";
        cout << c.getWinNum() << "��" << endl;
    }
    else {
        cout << "���û���δ����ҵ��" << endl;
    }
}

bool fileread(const string& filename, queue& cq, queue& sq) //��ȡ�ļ�����д�����
{
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "�޷����ļ����ж�ȡ��" << endl;
        return false;
    }
    client c;
    string name, id, boolStr;
    int phone[11];
    bool kind, winkind;
    int arrtime, reqtime, waittime, winnum;
    while (getline(inFile, name)) {
        c.setName(name);
        for (int i = 0; i < 11; ++i) {
            inFile >> phone[i];
        }
        c.setPhone(phone);
        inFile.ignore();
        inFile >> boolStr;
        kind = (boolStr == "true");
        c.setKind(kind);
        inFile.ignore();
        getline(inFile, id);
        c.setId(id);
        inFile >> arrtime;
        c.setArrtime(arrtime);
        inFile.ignore();
        inFile >> reqtime;
        c.setReqtime(reqtime);
        inFile.ignore();
        inFile >> waittime;
        c.setWaittime(waittime);
        inFile.ignore();
        inFile >> boolStr;
        winkind = (boolStr == "true");
        c.setWinKind(winkind);
        inFile.ignore();
        inFile >> winnum;
        c.setWinNum(winnum);
        inFile.ignore();
        if (c.getKind()) {
            sq.enqueue(c);
        }
        else {
            cq.enqueue(c);
        }
    }
    inFile.close();
    if (cq.empty() && sq.empty()) {
        system("cls");
        cout << "�ļ�Ϊ�գ�����������" << endl;
        return false;
    }
    else return true;
}

void filewrite(const string& filename, queue& q, bool overwrite)//��ȡ��������д���ļ�
{
	ofstream outFile;
	if (overwrite) {
		outFile.open(filename, ios::out | ios::trunc);
	}
	else {
		outFile.open(filename, ios::app);
	}
	if (!outFile) {
		cerr << "�޷����ļ�����д�룡" << endl;
		return;
	}
	node* current = q.Head;
	while (current != nullptr) {
		outFile << current->C.getName() << endl;
		int phone[11];
		current->C.getPhone(phone);
		for (int i = 0; i < 11; ++i) {
			outFile << phone[i];
			if (i < 10) outFile << ' '; // ������֮����ӿո�
		}
		outFile << endl;
		outFile << (current->C.getKind() ? "true" : "false") << endl; // д��boolֵ
		outFile << current->C.getId() << endl;
		outFile << current->C.getArrtime() << endl;
		outFile << current->C.getReqtime() << endl;
		outFile << current->C.getWaittime() << endl;
		outFile << (current->C.getWinKind() ? "true" : "false") << endl; // д��boolֵ
		outFile << current->C.getWinNum() << endl;
		current = current->Next;
	}
	outFile.close();
}

void fileclean(const string& filename) {
    char choice;
    do {
        cout << "�Ƿ���������" << endl;
        cout << "1.��";
        cout << setfill(' ') << setw(10) << "2.��" << endl;
        cin >> choice;
        switch (choice) {
        case'1': {
            system("cls");
            ofstream outFile(filename, ios::out | ios::trunc);
            if (!outFile) {
                cerr << "�޷����ļ�������գ�" << endl;
                return;
            }
            outFile.close();
            cout << "���������" << endl;
            break;
        }
        case'2':
            system("cls"); 
            break;
        default: {
            system("cls");
            cout << "��Ч��ѡ�����������" << endl;
            break;
        }
        }
    } while (choice != '1' && choice != '2');
}
