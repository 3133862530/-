#include "maninput.h"

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
		if (++t == 1)cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

void PrintTime(int h, int m) {
	cout << h << ":" << setw(2) << setfill('0') << m << endl;
}

void setTime() {
	char choice;
	do {
		cout << "Ĭ�Ͽ�ҵʱ��Ϊ��";
		PrintTime(OpeningHour, OpeningMintue);
		cout << "�Ƿ��޸Ŀ�ҵʱ��" << endl;
		cout << "1.��" << endl;
		cout << "2.��" << endl;
		cin >> choice;
		switch (choice) {
		case '1':
			cout << "�����뿪ҵʱ�䣨��ʽ��HH:MM����" << endl;
			InputTime(OpeningHour, OpeningMintue);
			cout << "���޸Ŀ�ҵʱ��Ϊ��";
			PrintTime(OpeningHour, OpeningMintue);
			break;
		case '2':break;
		default:cout << "������Ϸ���ѡ��" << endl;
		}
	} while (choice != '1' && choice != '2');
	do {
		cout << "Ĭ��Ӫҵʱ��Ϊ��" << MAXTIME << "��" << endl;
		cout << "�Ƿ��޸�Ӫҵʱ��" << endl;
		cout << "1.��" << endl;
		cout << "2.��" << endl;
		cin >> choice;
		switch (choice) {
		case '1':
			cout << "������Ӫҵʱ�������֣�" << endl;
			getValidNumber(MAXTIME);
			cout << "���޸Ŀ�ҵʱ��Ϊ��" << MAXTIME << "��" << endl;
			break;
		case '2':break;
		default:cout << "������Ϸ���ѡ��" << endl;
		}
	} while (choice != '1' && choice != '2');
}

// �˹�����
void maninput(queue& cq, queue& sq) {
	// �ͻ�����
	cout << "������ͻ�������" << endl;
	int num, pretime = 0;
	getValidNumber(num);
	for (int i = 1; i <= num; i++) {
		string name, id;
		int arrtime, reqtime, phone[11], hours, minutes;
		bool kind;
		cout << "�������" << i << "���ͻ�����Ϣ��" << endl;
		cout << "������������" << endl;
		cin >> name;
		cout << "������绰���루11λ����" << endl;
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
		cout << "���������֤�ţ�18λ����" << endl;
		bool flag;
		do {
			flag = true;
			cin >> id; // ��ȡ��������
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

			if (!flag) {
				cout << "���֤�����벻�Ϸ������������룺" << endl;
			}
		} while (!flag); // �������Ϸ������˳�ѭ��
		char choice;
		do {
			cout << "������ҵ�����ͣ�" << endl;
			cout << "1.��ͨҵ��" << endl;
			cout << "2.����ҵ��" << endl;
			cin >> choice;
			switch (choice) {
			case '1':
				kind = false;
				break;
			case '2':
				kind = true;
				break;
			default:cout << "������Ϸ���ѡ��" << endl;
			}
		} while (choice != '1' && choice != '2');

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
		Flag;
		do {
			cout << "����������ʱ����" << endl;
			getValidNumber(reqtime);
			if (reqtime < 0 || reqtime + arrtime > MAXTIME) {
				Flag = true;
				cout << "ʱ�����벻�Ϸ�������������" << endl;
			}
			else Flag = false;
		} while (Flag);
		client newc(name, phone, kind, id, arrtime, reqtime);
		if (kind)sq.enqueue(newc);
		else cq.enqueue(newc);
	}
	filewrite(InPut, cq, false);
	filewrite(InPut, sq, false);
}