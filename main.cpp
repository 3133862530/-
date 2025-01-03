#include <windows.h>
#include "class.h"
#include "rand.h"
#include "fileinput.h"
#include "maninput.h"
#include "search.h"

void Time(queue& cq, queue& sq, winList& cw, winList& sw, int& cn, int& sn, double& ct, double& st) {
	queue q;
	int time = 0;
	int num, start;
	for (int i = 0; i < sw.size() && !sq.empty(); i++) {
		sw[i].AvailTime = 0;
		sw[i].Cusnum = 0;
	}
	for (int i = 0; i < cw.size() && !sq.empty(); i++) {
		cw[i].AvailTime = 0;
		cw[i].Cusnum = 0;
	}
	while (time < MAXTIME) {
		start = randnum(0, sw.size() - 1);
		for (int i = 0; i < sw.size() && !sq.empty(); i++) {
			num = (i + start) % sw.size();
			if (sw[num].AvailTime <= time&&sq.front().getArrtime() <= time) {
				client c;
				sq.dequeue(c);
				sw[num].conduct(c, time, sn, st);
				q.enqueue(c);
			}
		}
		start = randnum(0, cw.size() - 1);
		for (int i = 0; i < cw.size() && !cq.empty(); i++) {
			num = (i + start) % cw.size();
			if (cw[num].AvailTime <= time && cq.front().getArrtime() <= time) {
				client c;
				cq.dequeue(c);
				cw[num].conduct(c, time, cn, ct);
				q.enqueue(c);
			}
		}
		start = randnum(0, sw.size() - 1);
		for (int i = 0; i < sw.size() && !cq.empty(); i++) {
			num = (i + start) % sw.size();
			if (sw[num].AvailTime <= time && cq.front().getArrtime() <= time) {
				client c;
				cq.dequeue(c);
				sw[num].conduct(c, time, cn, st);
				q.enqueue(c);
			}
		}
		time++;
	}
	filewrite(InPut, q, true);
}

int lg(int num) {
	return log(num) / log(10);
}

int getwindowWidth() {
	HWND consoleWindow = GetConsoleWindow();
	if (consoleWindow == NULL) {
		cerr << "�޷���ȡ����̨���ھ����" << endl;
		return -1;
	}
	RECT rect;
	if (!GetWindowRect(consoleWindow, &rect)) {
		cerr << "�޷���ȡ����̨���ڵľ�������" << endl;
		return -1;
	}
	return rect.right - rect.left;
}

void PrintBarchart(int num, int scale) {
	cout << " |";
	for (int i = 0; i < num; i += scale) {
		cout << "*";
	}
	cout << endl;
}

void  winStatistics(winList& cw, winList& sw) {
	cout << "=====================" << endl;
	cout << "   ��������ͳ��      " << endl;
	cout << "=====================" << endl;
	int cMax = 0, sMax = 0, Wsize, Csize, scale;
	int windowWidth = getwindowWidth();
	for (int i = 0; i < cw.size(); i++) {
		if (cw[i].Cusnum > cMax)cMax = cw[i].Cusnum;
	}
	for (int i = 0; i < sw.size(); i++) {
		if (sw[i].Cusnum > sMax)sMax = sw[i].Cusnum;
	}
	Wsize = (cw.size() > sw.size()) ? lg(cw.size()) + 1 : lg(sw.size()) + 1;
	Csize = (cMax > sMax) ? lg(cMax) + 1 : lg(sMax) + 1;
	scale = (cMax > sMax) ? cMax / windowWidth : sMax / windowWidth;
	scale = (scale > 1) ? scale : 1;
	cout << "������Ϊ1��" << scale << endl;
	for (int i = 0; i < cw.size(); i++) {
		cout << "��ͨ����" << setw(Wsize) << setfill(' ') << cw[i].Number << "�ţ�" 
			<< setw(Csize) << setfill(' ') << cw[i].Cusnum << "λ";
		PrintBarchart(cw[i].Cusnum, scale);
	}
	cout << endl;
	for (int i = 0; i < sw.size(); i++) {
		cout << "���ⴰ��" << setw(Wsize) << setfill(' ') << sw[i].Number << "�ţ�" 
			<< setw(Csize) << setfill(' ') << sw[i].Cusnum << "λ";
		PrintBarchart(sw[i].Cusnum, scale);
	}
	cout << endl;
	cout << "�Ӵ��ͻ�����������ͨ����Ϊ��";
	for (int i = 0; i < cw.size(); i++) {
		if (cw[i].Cusnum == cMax)cout << cw[i].Number << "��";
	}
	cout << endl;
	cout << "�Ӵ��ͻ������������ⴰ��Ϊ��";
	for (int i = 0; i < sw.size(); i++) {
		if (sw[i].Cusnum == sMax)cout << sw[i].Number << "��";
	}
	cout << endl;
}

void cusStatistics(int cn, int sn, double ct, double st) {
	cout << "=====================" << endl;
	cout << "   �ͻ�����ͳ��      " << endl;
	cout << "=====================" << endl;
	double c, s;
	c = (cn == 0) ? 0 : ct / cn;
	s = (sn == 0) ? 0 : st / sn;
	cout << "һ��ҵ��ͻ�ƽ������ʱ��Ϊ��" << fixed << setprecision(2) << c << "����" << endl;
	cout << "һ��ҵ��ͻ�����Ϊ��" << cn << endl;
	cout << "����ҵ��ͻ�ƽ������ʱ��Ϊ��" << fixed << setprecision(2) << s << "����" << endl;
	cout << "����ҵ��ͻ�����Ϊ��" << sn << endl;
}

void PrintStatistics(winList& cw, winList& sw, int cn, int sn, double ct, double st) {
	char choice;
	do {
		cout << "=====================" << endl;
		cout << "     ����ͳ��        " << endl;
		cout << "=====================" << endl;
		cout << "��ѡ����Ҫͳ�Ƶ���Ϣ��" << endl;
		cout << "1. �ͻ�����ͳ��" << endl;
		cout << "2. ��������ͳ��" << endl;
		cout << "3. ����" << endl;
		cout << "=====================" << endl;
		cin >> choice;
		switch (choice) 
		{
		case'1': 
		{
			system("cls");
			cusStatistics(cn, sn, ct, st);
			cout << "�����������..." << endl;
			_getch(); // �ȴ�����
			system("cls");
			break;
		}
		case'2': 
		{
			system("cls");
			winStatistics(cw, sw);
			cout << "�����������..." << endl;
			_getch(); // �ȴ�����
			system("cls");
			break;
		}
		case'3':
			system("cls"); 
			break;
		default: 
		{
			system("cls");
			cout << "������Ϸ���ѡ��" << endl;
			break;
		}
		}
	} while (choice != '3');
}

void PrintInputMenu() {
	cout << "=====================" << endl;
	cout << "     ��������        " << endl;
	cout << "=====================" << endl;
	cout << "��ѡ���������ݵķ�ʽ��" << endl;
	cout << "1. �������" << endl;
	cout << "2. �ļ�����" << endl;
	cout << "3. �˹�����" << endl;
	cout << "4. ����" << endl;
	cout << "=====================" << endl;
}

void PrintMenu() {
    cout << "=====================" << endl;
    cout << "       �˵�          " << endl;
    cout << "=====================" << endl;
    cout << "��ѡ�������" << endl;
    cout << "1. ��������" << endl;
    cout << "2. ��ѯ����" << endl;
    cout << "3. �������" << endl;
    cout << "4. ����ͳ��" << endl;
    cout << "5. �˳�" << endl;
    cout << "=====================" << endl;
}

void input() 
{
	system("cls");
	queue cq, sq;
	char choice;
	bool flag = true; // �ж��ļ������Ƿ���Ч
	do {
		
		PrintInputMenu();
		cin >> choice;
		switch (choice) {
		case'1': // �������
			randinput(cq, sq);
			system("cls");
			cout << "����ɹ�" << endl;
			cout << "�����������..." << endl;
			_getch(); // �ȴ�����
			system("cls");
			break;
		case'2': // �ļ�����
			flag = fileread(InPut, cq, sq); // ���ļ�������Ч����flag��Ϊfalse
			system("cls");
			if(flag)cout << "����ɹ�" << endl;
			cout << "�����������..." << endl;
			_getch(); // �ȴ�����
			system("cls");
			break;
		case'3': // �˹�����
			maninput(cq, sq);
			system("cls");
			cout << "����ɹ�" << endl;
			cout << "�����������..." << endl;
			_getch(); // �ȴ�����
			system("cls");
			break;
		case'4':
			system("cls"); 
			break;
		default:
			system("cls");
			cout << "������Ϸ���ѡ��" << endl;
		}
	} while (choice != '1' && (choice != '2' || !flag) && choice != '3' && choice != '4');
	
}

int main() {
	startMenu();
	int cCusNum = 0, sCusNum = 0;
	double cTotalTime = 0.0, sTotalTime = 0.0;
	winList cWin;
	for (int i = 1; i < cNum + 1; i++) {
		windows newwin(i, 0);
		cWin.push_back(newwin);
	}
	winList sWin;
	for (int i = 1; i < sNum + 1; i++) {
		windows newwin(i, 1);
		sWin.push_back(newwin);
	}
	char choice;
	system("cls");
	do {
		//system("cls");
		PrintMenu();
		cin >> choice;
		switch (choice) {
		case'1': // ��������
		{
			input();
			break;
		}
		case'2': // ��ѯ����
		{
			filesearch(InPut);
			break;
		}
		case'3': // �������
		{
			fileclean(InPut);
			break;
		}
		case'4': // ����ͳ��
		{
			cCusNum = sCusNum = 0;
			cTotalTime = sTotalTime = 0.0;
			queue Cqueue, Squeue;
			if (fileread(InPut, Cqueue, Squeue)) 
			{
				system("cls");
				Time(Cqueue, Squeue, cWin, sWin, cCusNum, sCusNum, cTotalTime, sTotalTime);
				PrintStatistics(cWin, sWin, cCusNum, sCusNum, cTotalTime, sTotalTime);
			}
			break;
		}
		case '5':break;
		default:cout << "������Ϸ���ѡ��" << endl;
		}
	} while (choice != '5');
	return 0;
}