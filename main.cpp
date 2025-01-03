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
		cerr << "无法获取控制台窗口句柄。" << endl;
		return -1;
	}
	RECT rect;
	if (!GetWindowRect(consoleWindow, &rect)) {
		cerr << "无法获取控制台窗口的矩形区域。" << endl;
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
	cout << "   窗口数据统计      " << endl;
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
	cout << "比例尺为1：" << scale << endl;
	for (int i = 0; i < cw.size(); i++) {
		cout << "普通窗口" << setw(Wsize) << setfill(' ') << cw[i].Number << "号：" 
			<< setw(Csize) << setfill(' ') << cw[i].Cusnum << "位";
		PrintBarchart(cw[i].Cusnum, scale);
	}
	cout << endl;
	for (int i = 0; i < sw.size(); i++) {
		cout << "特殊窗口" << setw(Wsize) << setfill(' ') << sw[i].Number << "号：" 
			<< setw(Csize) << setfill(' ') << sw[i].Cusnum << "位";
		PrintBarchart(sw[i].Cusnum, scale);
	}
	cout << endl;
	cout << "接待客户人数最多的普通窗口为：";
	for (int i = 0; i < cw.size(); i++) {
		if (cw[i].Cusnum == cMax)cout << cw[i].Number << "号";
	}
	cout << endl;
	cout << "接待客户人数最多的特殊窗口为：";
	for (int i = 0; i < sw.size(); i++) {
		if (sw[i].Cusnum == sMax)cout << sw[i].Number << "号";
	}
	cout << endl;
}

void cusStatistics(int cn, int sn, double ct, double st) {
	cout << "=====================" << endl;
	cout << "   客户数据统计      " << endl;
	cout << "=====================" << endl;
	double c, s;
	c = (cn == 0) ? 0 : ct / cn;
	s = (sn == 0) ? 0 : st / sn;
	cout << "一般业务客户平均逗留时间为：" << fixed << setprecision(2) << c << "分钟" << endl;
	cout << "一般业务客户人数为：" << cn << endl;
	cout << "特殊业务客户平均逗留时间为：" << fixed << setprecision(2) << s << "分钟" << endl;
	cout << "特殊业务客户人数为：" << sn << endl;
}

void PrintStatistics(winList& cw, winList& sw, int cn, int sn, double ct, double st) {
	char choice;
	do {
		cout << "=====================" << endl;
		cout << "     分类统计        " << endl;
		cout << "=====================" << endl;
		cout << "请选择需要统计的信息：" << endl;
		cout << "1. 客户数据统计" << endl;
		cout << "2. 窗口数据统计" << endl;
		cout << "3. 返回" << endl;
		cout << "=====================" << endl;
		cin >> choice;
		switch (choice) 
		{
		case'1': 
		{
			system("cls");
			cusStatistics(cn, sn, ct, st);
			cout << "按任意键继续..." << endl;
			_getch(); // 等待按键
			system("cls");
			break;
		}
		case'2': 
		{
			system("cls");
			winStatistics(cw, sw);
			cout << "按任意键继续..." << endl;
			_getch(); // 等待按键
			system("cls");
			break;
		}
		case'3':
			system("cls"); 
			break;
		default: 
		{
			system("cls");
			cout << "请输入合法的选项" << endl;
			break;
		}
		}
	} while (choice != '3');
}

void PrintInputMenu() {
	cout << "=====================" << endl;
	cout << "     输入数据        " << endl;
	cout << "=====================" << endl;
	cout << "请选择输入数据的方式：" << endl;
	cout << "1. 随机生成" << endl;
	cout << "2. 文件输入" << endl;
	cout << "3. 人工输入" << endl;
	cout << "4. 返回" << endl;
	cout << "=====================" << endl;
}

void PrintMenu() {
    cout << "=====================" << endl;
    cout << "       菜单          " << endl;
    cout << "=====================" << endl;
    cout << "请选择操作：" << endl;
    cout << "1. 输入数据" << endl;
    cout << "2. 查询数据" << endl;
    cout << "3. 清空数据" << endl;
    cout << "4. 分类统计" << endl;
    cout << "5. 退出" << endl;
    cout << "=====================" << endl;
}

void input() 
{
	system("cls");
	queue cq, sq;
	char choice;
	bool flag = true; // 判断文件输入是否有效
	do {
		
		PrintInputMenu();
		cin >> choice;
		switch (choice) {
		case'1': // 随机生成
			randinput(cq, sq);
			system("cls");
			cout << "输入成功" << endl;
			cout << "按任意键继续..." << endl;
			_getch(); // 等待按键
			system("cls");
			break;
		case'2': // 文件输入
			flag = fileread(InPut, cq, sq); // 若文件输入无效，则将flag设为false
			system("cls");
			if(flag)cout << "输入成功" << endl;
			cout << "按任意键继续..." << endl;
			_getch(); // 等待按键
			system("cls");
			break;
		case'3': // 人工输入
			maninput(cq, sq);
			system("cls");
			cout << "输入成功" << endl;
			cout << "按任意键继续..." << endl;
			_getch(); // 等待按键
			system("cls");
			break;
		case'4':
			system("cls"); 
			break;
		default:
			system("cls");
			cout << "请输入合法的选项" << endl;
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
		case'1': // 输入数据
		{
			input();
			break;
		}
		case'2': // 查询数据
		{
			filesearch(InPut);
			break;
		}
		case'3': // 清空数据
		{
			fileclean(InPut);
			break;
		}
		case'4': // 分类统计
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
		default:cout << "请输入合法的选项" << endl;
		}
	} while (choice != '5');
	return 0;
}