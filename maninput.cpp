#include "maninput.h"

void defaultSet() {
	char choice;
	do {
		cout << "=====================" << endl;
		cout << "       设置          " << endl;
		cout << "=====================" << endl;
		cout << "请选择要修改的设置" << endl;
		cout << "1.开业时间" << endl;
		cout << "2.营业时长" << endl;
		cout << "3.一般窗口数量" << endl;
		cout << "4.特殊窗口数量" <<  endl;
		cout << "5.返回" << endl;
		cin >> choice;
		switch (choice) {
		case'1': {
			cout << "默认开业时间为：";
			PrintTime(OpeningHour, OpeningMintue);
			cout << "请输入新的开业时间（格式：HH:MM）：" << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			InputTime(OpeningHour, OpeningMintue);
			cout << "已修改开业时间为：";
			PrintTime(OpeningHour, OpeningMintue);
			cout << "按任意键继续..." << endl;
			_getch(); // 等待按键
			system("cls");
			break;
		}
		case'2': {
			cout << "默认营业时长为：" << MAXTIME << "分" << endl;
			cout << "请输入新的营业时长：（1分-1440分）" << endl;
			int t = 0;
			do {
				if (t++)cout << "营业时长不得超过1440分，请重新输入：" << endl;
				getValidNumber(MAXTIME);
			} while (MAXTIME > 1440);
			cout << "已修改营业时长为：" << MAXTIME << "分" << endl;
			cout << "按任意键继续..." << endl;
			_getch(); // 等待按键
			system("cls");
			break;
		}
		case'3': {
			cout << "默认一般窗口数量为：" << cNum << endl;
			cout << "请输入新的一般窗口数量：" << endl;
			getValidNumber(cNum);
			cout << "已修改一般窗口数量为：" << cNum << endl;
			cout << "按任意键继续..." << endl;
			_getch(); // 等待按键
			system("cls");
			break;
		}
		case'4': {
			cout << "默认特殊窗口数量为：" << sNum << endl;
			cout << "请输入新的特殊窗口数量：" << endl;
			getValidNumber(sNum);
			cout << "已修改特殊窗口数量为：" << sNum << endl;
			cout << "按任意键继续..." << endl;
			_getch(); // 等待按键
			system("cls");
			break;
		}
		case'5':break;
		default: {
			cout << "请输入合法的选项" << endl;
			cout << "按任意键继续..." << endl;
			_getch(); // 等待按键
			system("cls");
		}
		}
	} while (choice != '5');
}

void startMenu() {
	char choice;
	do {
		cout << "=====================" << endl;
		cout << "       开始          " << endl;
		cout << "=====================" << endl;
		cout << "默认开业时间为：";
		PrintTime(OpeningHour, OpeningMintue);
		cout << "默认营业时长为：" << MAXTIME << "分" << endl;
		cout << "默认一般窗口数量为：" << cNum  << endl;
		cout << "默认特殊窗口数量为：" << sNum << endl;
		cout << endl;
		cout << "是否修改默认设置" << endl;
		cout << "1.是";
		cout << setfill(' ') << setw(10) << "2.否" << endl;
		cin >> choice;
		switch (choice) {
		case'1': {
			system("cls");
			defaultSet();
			break;
		}
		case'2': break;
		default: {
			cout << "请输入合法的选项" << endl;
		}
		}
	} while (choice != '1' && choice != '2');
}

// 人工输入
void maninput(queue& cq, queue& sq) {
	// 客户人数
	cout << "请输入客户人数：" << endl;
	int num, pretime = 0;
	getValidNumber(num);
	for (int i = 1; i <= num; i++) {
		string name, id;
		int arrtime, reqtime, phone[11];
		bool kind;
		cout << "请输入第" << i << "个客户的信息：" << endl;
		cout << "请输入姓名：" << endl;
		cin >> name;
		cout << "请输入电话号码（11位）：" << endl;
		inputPhone(phone);
		cout << "请输入身份证号（18位）：" << endl;
		inputId(id);
		char choice;
		do {
			cout << "请输入业务类型：" << endl;
			cout << "1.普通业务" << endl;
			cout << "2.特殊业务" << endl;
			cin >> choice;
			switch (choice) {
			case '1':
				kind = false;
				break;
			case '2':
				kind = true;
				break;
			default:cout << "请输入合法的选项" << endl;
				cout << "按任意键继续..." << endl;
				_getch(); // 等待按键
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