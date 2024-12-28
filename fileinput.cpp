# include "fileinput.h"
# include "maninput.h"
void fileread(const string& filename, queue& cq, queue& sq) //读取文件数据写入队列
{
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "无法打开文件进行读取！" << endl;
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

node* filesearch(const string& filename, const string& Name)//根据姓名查询办理事项与个人信息
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
        cout << "未找到该客户的信息。" << endl;
        return nullptr;
    }
    else
    {
        cout << "以下为该客户的信息：" << endl;
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
        cout << "未找到该客户的信息。" << endl;
        return nullptr;
    }
    else
    {
        cout << "以下为该客户的信息：" << endl;
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

node* filesearchPrev(const string& filename, const string& Name)//上一节点
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


void fileReset(const string& filename, const string& Name, queue& q)//更改队列数据
{
    queue cq, sq;
    fileread(filename, cq, sq);

    node* current = filesearch(filename, Name);
    if (current == nullptr) {
        return;
    }

    cout << "更改项目：" << endl;
    char choice;
    cout << "1.姓名" << endl;
    cout << "2.电话号码" << endl;
    cout << "3.业务种类" << endl;
    cout << "4.身份证号" << endl;
    cout << "5.到达时间" << endl;
    cout << "6.所需时长" << endl;
    cout << "7.逗留时间" << endl;
    cout << "8.办理业务窗口类型" << endl;
    cout << "9.办理业务窗口编号" << endl;
    cin >> choice;

    switch (choice)
    {
    case '1': {
        string newName;
        cout << "输入新的姓名: ";
        cin >> newName;
        current->C.setName(newName);
        break;
    }
    case '2': {
        int newPhone[11];
        cout << "输入新的电话号码: ";
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
                newPhone[j] = input[j] - '0'; // 将字符转换为对应的数字并存储
            }

            if (flag) {
                break; // 如果输入合法，则退出循环
            }
        } while (true);
        current->C.setPhone(newPhone);
        break;
    }
    case '3': {
        bool newKind;
        char choice;
        do {
            cout << "请输入更改的业务类型：" << endl;
            cout << "1.普通业务" << endl;
            cout << "2.特殊业务" << endl;
            cin >> choice;
            switch (choice) {
            case '1':
                newKind = false;
                break;
            case '2':
                newKind = true;
                break;
            default:cout << "请输入合法的选项" << endl;
            }
        } while (choice != '1' && choice != '2');
        current->C.setKind(newKind);
        break;
    }
    case '4': {
        string newId;
        cout << "输入新的身份证号（18位）: ";
        
        bool flag;
        do {
            flag = true;
            cin >> newId; // 读取整行输入
            if (newId[0] < '1' || newId[0] > '9') {
                flag = false; // 第一个字符必须是数字1-9
            }

            for (int j = 1; j < 17; ++j) {
                if (newId[j] < '0' || newId[j] > '9') {
                    flag = false; // 第2到第17位必须是数字
                    break;
                }
            }

            if (flag) {
                if ((newId[17] < '0' || newId[17] > '9') && newId[17] != 'X') {
                    flag = false; // 第18位必须是数字或X
                }
            }

            if (!flag) {
                cout << "身份证号输入不合法，请重新输入：" << endl;
            }
        } while (!flag); // 如果输入合法，则退出循环
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
            cout << "请输入到达时间（格式：HH:MM）：" << endl;
            InputTime(hours, minutes);
            newArrtime = (hours - OpeningHour) * 60 + (minutes - OpeningMintue);
            if (newArrtime < 0 || newArrtime >= MAXTIME) {
                Flag = true;
                cout << "时间输入不合法，请重新输入" << endl;
            }
            else if (newArrtime < pretime) {
                Flag = true;
                cout << "到达时间不得小于上一位客户，请重新输入" << endl;
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
            cout << "请输入所需时长：" << endl;
            getValidNumber(newReqtime);
            if (newReqtime < 0 || newReqtime + arrtime > MAXTIME) {
                Flag = true;
                cout << "时间输入不合法，请重新输入" << endl;
            }
            else Flag = false;
        } while (Flag);
        current->C.setReqtime(newReqtime);
        break;
    }
    case '7': {
        int newWaittime;
        cout << "输入新的逗留时间: ";
        cin >> newWaittime;
        current->C.setWaittime(newWaittime);
        break;
    }
    case '8': {
        bool newWinKind;
        cout << "输入新的办理业务窗口类型 (0: 普通窗口, 1: 特殊窗口): ";
        cin >> newWinKind;
        current->C.setWinKind(newWinKind);
        break;
    }
    case '9': {
        int newWinNum;
        cout << "输入新的办理业务窗口编号: ";
        cin >> newWinNum;
        current->C.setWinNum(newWinNum);
        break;
    }
    default:
        cout << "请输入合法的选项" << endl;
    }

    //覆写再追加
    filewrite(InPut, cq, true);
    filewrite(InPut, sq, false);
}

