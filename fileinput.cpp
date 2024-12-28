# include "fileinput.h"
# include "maninput.h"
void fileread(const string& filename, queue& cq, queue& sq) //��ȡ�ļ�����д�����
{
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "�޷����ļ����ж�ȡ��" << endl;
        return;
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

node* filesearch(const string& filename, const string& Name)//����������ѯ���������������Ϣ
{
    //
    queue cq, sq;
    fileread(filename, cq, sq);

    node* current = cq.Head;
    while (current != nullptr && current->C.getName() != Name)
    {
        current = current->Next;
    }

    if (current == nullptr) {
        cout << "δ�ҵ��ÿͻ�����Ϣ��" << endl;
        return nullptr;
    }
    else
    {
        cout << "����Ϊ�ÿͻ�����Ϣ��" << endl;
        cout << current->C.getName() << endl;

        int phone[11];
        current->C.getPhone(phone);
        for (int i = 0; i < 11; i++)
        {
            cout << phone[i];
        }
        cout << endl;

        cout << current->C.getId() << endl;
        int hour = 0, mintue = 0;

        mintue = (current->C.getArrtime() % 60 + OpeningMintue);
        hour = (current->C.getArrtime() / 60 + OpeningHour);
        if (mintue >= 60)
            mintue -= 60, hour += 1;

        cout << hour << ":" << mintue << endl;
        cout << current->C.getReqtime() << endl;
        cout << current->C.getWaittime() << endl;
        cout << (current->C.getWinKind() ? "true" : "false") << endl;
        cout << current->C.getWinNum() << endl;
        return current;
    }

    current = sq.Head;
    while (current != nullptr && current->C.getName() != Name)
    {
        current = current->Next;
    }

    if (current == nullptr) {
        cout << "δ�ҵ��ÿͻ�����Ϣ��" << endl;
        return nullptr;
    }
    else
    {
        cout << "����Ϊ�ÿͻ�����Ϣ��" << endl;
        cout << current->C.getName() << endl;

        int phone[11];
        current->C.getPhone(phone);
        for (int i = 0; i < 11; i++)
        {
            cout << phone[i];
        }
        cout << endl;

        cout << current->C.getId() << endl;
        int hour = 0, mintue = 0;

        mintue = (current->C.getArrtime() % 60 + OpeningMintue);
        hour = (current->C.getArrtime() / 60 + OpeningHour);
        if (mintue >= 60)
            mintue -= 60, hour += 1;

        cout << hour << ":" << mintue << endl;
        cout << current->C.getReqtime() << endl;
        cout << current->C.getWaittime() << endl;
        cout << (current->C.getWinKind() ? "true" : "false") << endl;
        cout << current->C.getWinNum() << endl;
        return current;
    }
    
}

node* filesearchPrev(const string& filename, const string& Name)//��һ�ڵ�
{
    queue cq, sq;
    fileread(filename, cq, sq);
    node* Prev = nullptr;

    node* current = cq.Head;
    while (current != nullptr && current->C.getName() != Name)
    {
        Prev = current;
        current = current->Next;
    }
    if (Prev == nullptr)
        return nullptr;
    else
        return
        Prev;

    current = sq.Head;
    while (current != nullptr && current->C.getName() != Name)
    {
        Prev = current;
        current = current->Next;
    }
    if (Prev == nullptr)
        return nullptr;
    else
        return
        Prev;
}


void fileReset(const string& filename, const string& Name, queue& q)//���Ķ�������
{
    queue cq, sq;
    fileread(filename, cq, sq);

    node* current = filesearch(filename, Name);
    if (current == nullptr) {
        return;
    }

    cout << "������Ŀ��" << endl;
    char choice;
    cout << "1.����" << endl;
    cout << "2.�绰����" << endl;
    cout << "3.ҵ������" << endl;
    cout << "4.���֤��" << endl;
    cout << "5.����ʱ��" << endl;
    cout << "6.����ʱ��" << endl;
    cout << "7.����ʱ��" << endl;
    cout << "8.����ҵ�񴰿�����" << endl;
    cout << "9.����ҵ�񴰿ڱ��" << endl;
    cin >> choice;

    switch (choice)
    {
    case '1': {
        string newName;
        cout << "�����µ�����: ";
        cin >> newName;
        current->C.setName(newName);
        break;
    }
    case '2': {
        int newPhone[11];
        cout << "�����µĵ绰����: ";
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
                newPhone[j] = input[j] - '0'; // ���ַ�ת��Ϊ��Ӧ�����ֲ��洢
            }

            if (flag) {
                break; // �������Ϸ������˳�ѭ��
            }
        } while (true);
        current->C.setPhone(newPhone);
        break;
    }
    case '3': {
        bool newKind;
        char choice;
        do {
            cout << "��������ĵ�ҵ�����ͣ�" << endl;
            cout << "1.��ͨҵ��" << endl;
            cout << "2.����ҵ��" << endl;
            cin >> choice;
            switch (choice) {
            case '1':
                newKind = false;
                break;
            case '2':
                newKind = true;
                break;
            default:cout << "������Ϸ���ѡ��" << endl;
            }
        } while (choice != '1' && choice != '2');
        current->C.setKind(newKind);
        break;
    }
    case '4': {
        string newId;
        cout << "�����µ����֤�ţ�18λ��: ";
        
        bool flag;
        do {
            flag = true;
            cin >> newId; // ��ȡ��������
            if (newId[0] < '1' || newId[0] > '9') {
                flag = false; // ��һ���ַ�����������1-9
            }

            for (int j = 1; j < 17; ++j) {
                if (newId[j] < '0' || newId[j] > '9') {
                    flag = false; // ��2����17λ����������
                    break;
                }
            }

            if (flag) {
                if ((newId[17] < '0' || newId[17] > '9') && newId[17] != 'X') {
                    flag = false; // ��18λ���������ֻ�X
                }
            }

            if (!flag) {
                cout << "���֤�����벻�Ϸ������������룺" << endl;
            }
        } while (!flag); // �������Ϸ������˳�ѭ��
        current->C.setId(newId);
        break;
    }
    case '5': {
        int hours, minutes;
        int newArrtime;
        node* prev = filesearch(filename, Name);
 
        int pretime = (prev != nullptr) ? prev->C.getArrtime() : 0;
        bool Flag;

        do {
            cout << "�����뵽��ʱ�䣨��ʽ��HH:MM����" << endl;
            InputTime(hours, minutes);
            newArrtime = (hours - OpeningHour) * 60 + (minutes - OpeningMintue);
            if (newArrtime < 0 || newArrtime >= MAXTIME) {
                Flag = true;
                cout << "ʱ�����벻�Ϸ�������������" << endl;
            }
            else if (newArrtime < pretime) {
                Flag = true;
                cout << "����ʱ�䲻��С����һλ�ͻ�������������" << endl;
            }
        } while (Flag);
        current->C.setArrtime(newArrtime);
        break;
    }
    case '6': {
        bool Flag;
        int newReqtime;
        int arrtime = current->C.getArrtime();
        do {
            cout << "����������ʱ����" << endl;
            getValidNumber(newReqtime);
            if (newReqtime < 0 || newReqtime + arrtime > MAXTIME) {
                Flag = true;
                cout << "ʱ�����벻�Ϸ�������������" << endl;
            }
            else Flag = false;
        } while (Flag);
        current->C.setReqtime(newReqtime);
        break;
    }
    case '7': {
        int newWaittime;
        cout << "�����µĶ���ʱ��: ";
        cin >> newWaittime;
        current->C.setWaittime(newWaittime);
        break;
    }
    case '8': {
        bool newWinKind;
        cout << "�����µİ���ҵ�񴰿����� (0: ��ͨ����, 1: ���ⴰ��): ";
        cin >> newWinKind;
        current->C.setWinKind(newWinKind);
        break;
    }
    case '9': {
        int newWinNum;
        cout << "�����µİ���ҵ�񴰿ڱ��: ";
        cin >> newWinNum;
        current->C.setWinNum(newWinNum);
        break;
    }
    default:
        cout << "������Ϸ���ѡ��" << endl;
    }

    //��д��׷��
    filewrite(InPut, cq, true);
    filewrite(InPut, sq, false);
}

