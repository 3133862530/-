#include "maninput.h"

void getValidNumber(int& number) {
	while (true) {
		cin >> number;
		// 检查输入流状态，判断输入是否有效
		if (cin.fail() || number <= 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "输入无效，请输入正整数：" << endl;
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
		// 使用 stringstream 进行字符串解析
		stringstream ss(time);
		char colon;
		if (!(ss >> h >> colon >> m)) {
			cout << "时间格式错误，请按照 'HH:MM' 的格式输入" << endl;
			OK = false;
		}
		else if (h < 0 || h > 23 || m < 0 || m > 59) {
			cout << "时间输入不合法，请重新输入" << endl;
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
		cout << "默认开业时间为：";
		PrintTime(OpeningHour, OpeningMintue);
		cout << "是否修改开业时间" << endl;
		cout << "1.是" << endl;
		cout << "2.否" << endl;
		cin >> choice;
		switch (choice) {
		case '1':
			cout << "请输入开业时间（格式：HH:MM）：" << endl;
			InputTime(OpeningHour, OpeningMintue);
			cout << "已修改开业时间为：";
			PrintTime(OpeningHour, OpeningMintue);
			break;
		case '2':break;
		default:cout << "请输入合法的选项" << endl;
		}
	} while (choice != '1' && choice != '2');
	do {
		cout << "默认营业时长为：" << MAXTIME << "分" << endl;
		cout << "是否修改营业时长" << endl;
		cout << "1.是" << endl;
		cout << "2.否" << endl;
		cin >> choice;
		switch (choice) {
		case '1':
			cout << "请输入营业时长：（分）" << endl;
			getValidNumber(MAXTIME);
			cout << "已修改开业时间为：" << MAXTIME << "分" << endl;
			break;
		case '2':break;
		default:cout << "请输入合法的选项" << endl;
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
		int arrtime, reqtime, phone[11], hours, minutes;
		bool kind;
		cout << "请输入第" << i << "个客户的信息：" << endl;
		cout << "请输入姓名：" << endl;
		cin >> name;
		cout << "请输入电话号码（11位）：" << endl;
		do {
			string input;
			cin >> input; // 读取整行输入

			if (input.length() != 11 || input[0] != '1') {
				cout << "电话号码输入不合法，请重新输入：" << endl;
				continue;
			}

			bool flag = true;
			for (int j = 0; j < 11; ++j) {
				if (input[j] < '0' || input[j] > '9') {
					cout << "电话号码输入不合法，请重新输入：" << endl;
					flag = false;
					break;
				}
				phone[j] = input[j] - '0'; // 将字符转换为对应的数字并存储
			}

			if (flag) {
				break; // 如果输入合法，则退出循环
			}
		} while (true);
		cout << "请输入身份证号（18位）：" << endl;
		bool flag;
		do {
			flag = true;
			cin >> id; // 读取整行输入
			if (id[0] < '1' || id[0] > '9') {
				flag = false; // 第一个字符必须是数字1-9
			}

			for (int j = 1; j < 17; ++j) {
				if (id[j] < '0' || id[j] > '9') {
					flag = false; // 第2到第17位必须是数字
					break;
				}
			}

			if (flag) {
				if ((id[17] < '0' || id[17] > '9') && id[17] != 'X') {
					flag = false; // 第18位必须是数字或X
				}
			}

			if (!flag) {
				cout << "身份证号输入不合法，请重新输入：" << endl;
			}
		} while (!flag); // 如果输入合法，则退出循环
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
			}
		} while (choice != '1' && choice != '2');

		bool Flag;
		do {
			cout << "请输入到达时间（格式：HH:MM）：" << endl;
			InputTime(hours, minutes);
			arrtime = (hours - OpeningHour) * 60 + (minutes - OpeningMintue);
			if (arrtime < 0 || arrtime >= MAXTIME) {
				Flag = true;
				cout << "时间输入不合法，请重新输入" << endl;
			}
			else if (arrtime < pretime) {
				Flag = true;
				cout << "到达时间不得小于上一位客户，请重新输入" << endl;
			}
			else {
				Flag = false;
				pretime = arrtime;
			}
		} while (Flag);
		Flag;
		do {
			cout << "请输入所需时长：" << endl;
			getValidNumber(reqtime);
			if (reqtime < 0 || reqtime + arrtime > MAXTIME) {
				Flag = true;
				cout << "时间输入不合法，请重新输入" << endl;
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