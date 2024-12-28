#include "class.h"
#include "rand.h"
#include "fileinput.h"
#include "maninput.h"

void Time(queue& cq, queue& sq, winList& cw, winList& sw, int& cn, int& sn, double& ct, double& st) {
	int time = 0;
	while (time < MAXTIME) {
		for (int i = 0; i < sw.size() && !sq.empty(); i++) {
			if (sw[i].AvailTime <= time&&sq.front().getArrtime() <= time) {
				client c;
				sq.dequeue(c);
				sw[i].conduct(c, time, sn, st);
			}
		}
		for (int i = 0; i < cw.size() && !cq.empty(); i++) {
			if (cw[i].AvailTime <= time && cq.front().getArrtime() <= time) {
				client c;
				cq.dequeue(c);
				cw[i].conduct(c, time, cn, ct);
			}
		}
		for (int i = 0; i < sw.size() && !cq.empty(); i++) {
			if (sw[i].AvailTime <= time && cq.front().getArrtime() <= time) {
				client c;
				cq.dequeue(c);
				sw[i].conduct(c, time, cn, st);
			}
		}
		time++;
	}
}

void PrintStatistics(int cn, int sn, double ct, double st) {
	cout << "һ��ҵ��ͻ�ƽ������ʱ��Ϊ" << fixed << setprecision(2) << ct / cn << "����" << endl;
	cout << "һ��ҵ��ͻ�����Ϊ" << cn << endl;
	cout << "����ҵ��ͻ�ƽ������ʱ��Ϊ" << fixed << setprecision(2) << st / sn << "����" << endl;
	cout << "����ҵ��ͻ�����Ϊ" << sn << endl;
}

void PrintInputMenu() {
	cout << "��ѡ���������ݵķ�ʽ��" << endl;
	cout << "1.�������" << endl;
	cout << "2.�ļ�����" << endl;
	cout << "3.�˹�����" << endl;
}

void PrintMenu() {
	cout << "��ѡ�������" << endl;
	cout << "1.��ѯ����" << endl;
	cout << "2.��������" << endl;
	cout << "3.�������" << endl;
	cout << "4.����ͳ��" << endl;
	cout << "5.�˳�" << endl;
}

int main() {
	setTime();
	int cNum, sNum;
	int cCusNum = 0, sCusNum = 0;
	double cTotalTime = 0.0, sTotalTime = 0.0;
	queue Cqueue, Squeue;
	cout << "������һ��ҵ�񴰿�������" << endl;
	getValidNumber(cNum);
	winList cWin;
	for (int i = 1; i < cNum + 1; i++) {
		windows newwin(i, 0);
		cWin.push_back(newwin);
	}
	cout << "����������ҵ�񴰿�������" << endl;
	getValidNumber(sNum);
	winList sWin;
	for (int i = 1; i < sNum + 1; i++) {
		windows newwin(i, 1);
		sWin.push_back(newwin);
	}
	char choice;
	do {
		PrintInputMenu();
		cin >> choice;
		switch (choice) {
		case'1': // �������
			randinput(Cqueue, Squeue);
			break;
		case'2': // �ļ�����
			fileread(InPut, Cqueue, Squeue);
			break;
		case'3': // �˹�����
			maninput(Cqueue, Squeue);
			break;
		default:cout << "������Ϸ���ѡ��" << endl;
		}
	} while (choice != '1'&&choice != '2'&&choice != '3');
	do {
		PrintMenu();
		cin >> choice;
		switch (choice) {
		case'1': // ��ѯ����
			
			break;
		case'2': // ��������

			break;
		case'3': // �������
		{
			ofstream outFile(InPut, ios::out | ios::trunc);
			if (!outFile) {
				cerr << "�޷����ļ�������գ�" << endl;
				return -1;
			}
			outFile.close();
			outFile.open(OutPut, ios::out | ios::trunc);
			if (!outFile) {
				cerr << "�޷����ļ�������գ�" << endl;
				return -1;
			}
			outFile.close();
			cout << "���������" << endl;
			break;
		}
		case'4': // ����ͳ��
		{
			Time(Cqueue, Squeue, cWin, sWin, cCusNum, sCusNum, cTotalTime, sTotalTime);
			PrintStatistics(cCusNum, sCusNum, cTotalTime, sTotalTime);
			break;
		}
		case '5':break;
		default:cout << "������Ϸ���ѡ��" << endl;
		}
	} while (choice != '5');
	return 0;
}