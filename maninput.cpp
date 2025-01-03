#include "maninput.h"

void defaultSet() {
	char choice;
	do {
		cout << "=====================" << endl;
		cout << "       ����          " << endl;
		cout << "=====================" << endl;
		cout << "��ѡ��Ҫ�޸ĵ�����" << endl;
		cout << "1.��ҵʱ��" << endl;
		cout << "2.Ӫҵʱ��" << endl;
		cout << "3.һ�㴰������" << endl;
		cout << "4.���ⴰ������" <<  endl;
		cout << "5.����" << endl;
		cin >> choice;
		switch (choice) {
		case'1': {
			cout << "Ĭ�Ͽ�ҵʱ��Ϊ��";
			PrintTime(OpeningHour, OpeningMintue);
			cout << "�������µĿ�ҵʱ�䣨��ʽ��HH:MM����" << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			InputTime(OpeningHour, OpeningMintue);
			cout << "���޸Ŀ�ҵʱ��Ϊ��";
			PrintTime(OpeningHour, OpeningMintue);
			cout << "�����������..." << endl;
			_getch(); // �ȴ�����
			system("cls");
			break;
		}
		case'2': {
			cout << "Ĭ��Ӫҵʱ��Ϊ��" << MAXTIME << "��" << endl;
			cout << "�������µ�Ӫҵʱ������1��-1440�֣�" << endl;
			int t = 0;
			do {
				if (t++)cout << "Ӫҵʱ�����ó���1440�֣����������룺" << endl;
				getValidNumber(MAXTIME);
			} while (MAXTIME > 1440);
			cout << "���޸�Ӫҵʱ��Ϊ��" << MAXTIME << "��" << endl;
			cout << "�����������..." << endl;
			_getch(); // �ȴ�����
			system("cls");
			break;
		}
		case'3': {
			cout << "Ĭ��һ�㴰������Ϊ��" << cNum << endl;
			cout << "�������µ�һ�㴰��������" << endl;
			getValidNumber(cNum);
			cout << "���޸�һ�㴰������Ϊ��" << cNum << endl;
			cout << "�����������..." << endl;
			_getch(); // �ȴ�����
			system("cls");
			break;
		}
		case'4': {
			cout << "Ĭ�����ⴰ������Ϊ��" << sNum << endl;
			cout << "�������µ����ⴰ��������" << endl;
			getValidNumber(sNum);
			cout << "���޸����ⴰ������Ϊ��" << sNum << endl;
			cout << "�����������..." << endl;
			_getch(); // �ȴ�����
			system("cls");
			break;
		}
		case'5':break;
		default: {
			cout << "������Ϸ���ѡ��" << endl;
			cout << "�����������..." << endl;
			_getch(); // �ȴ�����
			system("cls");
		}
		}
	} while (choice != '5');
}

void startMenu() {
	char choice;
	do {
		cout << "=====================" << endl;
		cout << "       ��ʼ          " << endl;
		cout << "=====================" << endl;
		cout << "Ĭ�Ͽ�ҵʱ��Ϊ��";
		PrintTime(OpeningHour, OpeningMintue);
		cout << "Ĭ��Ӫҵʱ��Ϊ��" << MAXTIME << "��" << endl;
		cout << "Ĭ��һ�㴰������Ϊ��" << cNum  << endl;
		cout << "Ĭ�����ⴰ������Ϊ��" << sNum << endl;
		cout << endl;
		cout << "�Ƿ��޸�Ĭ������" << endl;
		cout << "1.��";
		cout << setfill(' ') << setw(10) << "2.��" << endl;
		cin >> choice;
		switch (choice) {
		case'1': {
			system("cls");
			defaultSet();
			break;
		}
		case'2': break;
		default: {
			cout << "������Ϸ���ѡ��" << endl;
		}
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
		int arrtime, reqtime, phone[11];
		bool kind;
		cout << "�������" << i << "���ͻ�����Ϣ��" << endl;
		cout << "������������" << endl;
		cin >> name;
		cout << "������绰���루11λ����" << endl;
		inputPhone(phone);
		cout << "���������֤�ţ�18λ����" << endl;
		inputId(id);
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
				cout << "�����������..." << endl;
				_getch(); // �ȴ�����
			}
		} while (choice != '1' && choice != '2');
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		inputArrtime(arrtime, pretime);
		inputReqtime(reqtime, arrtime, kind);
		client newc(name, phone, kind, id, arrtime, reqtime);
		if (kind)sq.enqueue(newc);
		else cq.enqueue(newc);
	}
	filewrite(InPut, cq, false);
	filewrite(InPut, sq, false);
}