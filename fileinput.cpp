# include "fileinput.h"

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

void inputPhone(int* phone) {
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
}

void inputId(string& id) {
    bool flag = false;
    do {
        flag = true;
        cin >> id; // 读取整行输入
        if (id.size() == 18) {
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

        }
        else {
            flag = false;
        }

        if (!flag) {
            cout << "身份证号输入不合法，请重新输入：" << endl;
        }
    } while (!flag); // 如果输入合法，则退出循环
}

void inputArrtime(int& arrtime, int& pretime) {
    int hours, minutes;
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
}

void inputReqtime(int& reqtime, const int& arrtime, const bool& kind) {
    bool Flag;
    int maxReq = kind ? 15 : 5;
    do {
        cout << "请输入所需时长：" << endl;
        getValidNumber(reqtime);
        if (reqtime < 0 || reqtime > maxReq || reqtime + arrtime > MAXTIME) {
            Flag = true;
            cout << "时间输入不合法，请重新输入" << endl;
        }
        else Flag = false;
    } while (Flag);
}

void PrintTime(int h, int m) {
    cout << h << ":" << setw(2) << setfill('0') << m << endl;
}

void PrintClient(client c) {
    cout << "以下为该客户的信息：" << endl;
    cout << "姓名：" << c.getName() << endl;
    int phone[11];
    c.getPhone(phone);
    cout << "电话号码：";
    for (int i = 0; i < 11; i++)
    {
        cout << phone[i];
    }
    cout << endl;
    cout << "身份证号：" << c.getId() << endl;
    int hour = 0, minute = 0;
    minute = (c.getArrtime() % 60 + OpeningMintue);
    hour = (c.getArrtime() / 60 + OpeningHour);
    if (minute >= 60)
        minute -= 60, hour += 1;
    cout << "到达时间：";
    PrintTime(hour, minute);
    cout << "办理业务类型：" << (c.getKind() ? "特殊" : "一般") << "业务" << endl;
    cout << "办理业务所需时长：" << c.getReqtime() << "分" << endl;
    if (c.getWaittime() >= 0) {
        cout << "逗留时长：" << c.getWaittime() << "分" << endl;
        cout << "办理业务窗口：" << (c.getWinKind() ? "特殊" : "一般") << "窗口";
        cout << c.getWinNum() << "号" << endl;
    }
    else {
        cout << "该用户尚未办理业务" << endl;
    }
}

bool fileread(const string& filename, queue& cq, queue& sq) //读取文件数据写入队列
{
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "无法打开文件进行读取！" << endl;
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
        cout << "文件为空，请重新输入" << endl;
        return false;
    }
    else return true;
}

void filewrite(const string& filename, queue& q, bool overwrite)//读取队列数据写入文件
{
	ofstream outFile;
	if (overwrite) {
		outFile.open(filename, ios::out | ios::trunc);
	}
	else {
		outFile.open(filename, ios::app);
	}
	if (!outFile) {
		cerr << "无法打开文件进行写入！" << endl;
		return;
	}
	node* current = q.Head;
	while (current != nullptr) {
		outFile << current->C.getName() << endl;
		int phone[11];
		current->C.getPhone(phone);
		for (int i = 0; i < 11; ++i) {
			outFile << phone[i];
			if (i < 10) outFile << ' '; // 在数字之间添加空格
		}
		outFile << endl;
		outFile << (current->C.getKind() ? "true" : "false") << endl; // 写入bool值
		outFile << current->C.getId() << endl;
		outFile << current->C.getArrtime() << endl;
		outFile << current->C.getReqtime() << endl;
		outFile << current->C.getWaittime() << endl;
		outFile << (current->C.getWinKind() ? "true" : "false") << endl; // 写入bool值
		outFile << current->C.getWinNum() << endl;
		current = current->Next;
	}
	outFile.close();
}

void fileclean(const string& filename) {
    char choice;
    do {
        cout << "是否清理数据" << endl;
        cout << "1.是";
        cout << setfill(' ') << setw(10) << "2.否" << endl;
        cin >> choice;
        switch (choice) {
        case'1': {
            system("cls");
            ofstream outFile(filename, ios::out | ios::trunc);
            if (!outFile) {
                cerr << "无法打开文件进行清空！" << endl;
                return;
            }
            outFile.close();
            cout << "已清空数据" << endl;
            break;
        }
        case'2':
            system("cls"); 
            break;
        default: {
            system("cls");
            cout << "无效的选项，请重新输入" << endl;
            break;
        }
        }
    } while (choice != '1' && choice != '2');
}
