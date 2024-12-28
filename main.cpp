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
	cout << "一般业务客户平均逗留时间为" << fixed << setprecision(2) << ct / cn << "分钟" << endl;
	cout << "一般业务客户人数为" << cn << endl;
	cout << "特殊业务客户平均逗留时间为" << fixed << setprecision(2) << st / sn << "分钟" << endl;
	cout << "特殊业务客户人数为" << sn << endl;
}

void PrintInputMenu() {
	cout << "请选择输入数据的方式：" << endl;
	cout << "1.随机生成" << endl;
	cout << "2.文件输入" << endl;
	cout << "3.人工输入" << endl;
}

void PrintMenu() {
	cout << "请选择操作：" << endl;
	cout << "1.查询数据" << endl;
	cout << "2.更新数据" << endl;
	cout << "3.清空数据" << endl;
	cout << "4.分类统计" << endl;
	cout << "5.退出" << endl;
}

int main() {
	setTime();
	int cNum, sNum;
	int cCusNum = 0, sCusNum = 0;
	double cTotalTime = 0.0, sTotalTime = 0.0;
	queue Cqueue, Squeue;
	cout << "请输入一般业务窗口数量：" << endl;
	getValidNumber(cNum);
	winList cWin;
	for (int i = 1; i < cNum + 1; i++) {
		windows newwin(i, 0);
		cWin.push_back(newwin);
	}
	cout << "请输入特殊业务窗口数量：" << endl;
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
		case'1': // 随机生成
			randinput(Cqueue, Squeue);
			break;
		case'2': // 文件输入
			fileread(InPut, Cqueue, Squeue);
			break;
		case'3': // 人工输入
			maninput(Cqueue, Squeue);
			break;
		default:cout << "请输入合法的选项" << endl;
		}
	} while (choice != '1'&&choice != '2'&&choice != '3');
	do {
		PrintMenu();
		cin >> choice;
		switch (choice) {
		case'1': // 查询数据
			
			break;
		case'2': // 更新数据

			break;
		case'3': // 清空数据
		{
			ofstream outFile(InPut, ios::out | ios::trunc);
			if (!outFile) {
				cerr << "无法打开文件进行清空！" << endl;
				return -1;
			}
			outFile.close();
			outFile.open(OutPut, ios::out | ios::trunc);
			if (!outFile) {
				cerr << "无法打开文件进行清空！" << endl;
				return -1;
			}
			outFile.close();
			cout << "已清空数据" << endl;
			break;
		}
		case'4': // 分类统计
		{
			Time(Cqueue, Squeue, cWin, sWin, cCusNum, sCusNum, cTotalTime, sTotalTime);
			PrintStatistics(cCusNum, sCusNum, cTotalTime, sTotalTime);
			break;
		}
		case '5':break;
		default:cout << "请输入合法的选项" << endl;
		}
	} while (choice != '5');
	return 0;
}