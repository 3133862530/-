#include "search.h"

bool samePhone(int* phone1, int* phone2) {
    for (int i = 0; i < 11; i++) {
        if (phone1[i] != phone2[i])return false;
    }
    return true;
}


    void PrintSearchMenu()
    {
        cout << "=============================" << endl;
        cout << "        查询数据" << endl;
        cout << "=============================" << endl;
        cout << "请选择查询数据的方式：" << endl;
        cout << "1. 按姓名查询" << endl;
        cout << "2. 按身份证号查询" << endl;
        cout << "3. 按电话号码查询" << endl;
        cout << "4. 返回" << endl;
        cout << "=============================" << endl;
    }


void filesearch(string filename) // 根据姓名查询办理事项与个人信息
{
    node* current = nullptr;
    node* prenode = nullptr;
    queue cq, sq;
    if (!fileread(filename, cq, sq))return;
    char choice;
    do {
        system("cls");
        PrintSearchMenu();
        cin >> choice;
        switch (choice) {
        case'1': {
            prenode = current = cq.Head;
            string Name;
            cout << "输入姓名：" << endl;
            cin >> Name;
            while (current != nullptr && current->C.getName() != Name) {
                prenode = current;
                current = current->Next;
            }
            if (current == nullptr) {
                prenode = current = sq.Head;
                while (current != nullptr && current->C.getName() != Name) {
                    prenode = current;
                    current = current->Next;
                }
            }
            if (current == nullptr) {
                system("cls");
                cout << "未找到该客户的信息。" << endl;
                cout << "按任意键继续..." << endl;
                _getch(); // 等待按键
                system("cls");
                return;
            }
            else
            {
                system("cls");
                PrintClient(current->C);
            }
            break;
        }
        case'2': {
            prenode = current = cq.Head;
            string Id;
            cout << "输入身份证号：" << endl;
            inputId(Id);
            while (current != nullptr && current->C.getId() != Id) {
                prenode = current;
                current = current->Next;
            }
            if (current == nullptr) {
                prenode = current = sq.Head;
                while (current != nullptr && current->C.getId() != Id) {
                    prenode = current;
                    current = current->Next;
                }
            }
            if (current == nullptr) {
                system("cls");
                cout << "未找到该客户的信息。" << endl;
                cout << "按任意键继续..." << endl;
                _getch(); // 等待按键
                system("cls");
                return;
            }
            else
            {
                system("cls");
                PrintClient(current->C);
            }
            break;
        }
        case'3': {
            prenode = current = cq.Head;
            int Phone[11], cphone[11];
            cout << "输入电话号码：" << endl;
            inputPhone(Phone);            
            while (current != nullptr && (current->C.getPhone(cphone), !samePhone(Phone, cphone))) {
                prenode = current;
                current = current->Next;
            }
            if (current == nullptr) {
                prenode = current = sq.Head;
                while (current != nullptr && (current->C.getPhone(cphone), !samePhone(Phone, cphone))) {
                    prenode = current;
                    current = current->Next;
                }
            }
            if (current == nullptr) {
                system("cls");
                cout << "未找到该客户的信息。" << endl;
                cout << "按任意键继续..." << endl;
                _getch(); // 等待按键
                system("cls");
                return;
            }
            else
            {
                system("cls");
                PrintClient(current->C);
            }
            break;
        }
        case'4':
            system("cls"); 
            return;
        default:
            system("cls"); 
            cout << "无效的选项，请重新输入" << endl;
        }
    } while (choice != '1' && choice != '2' && choice != '3' && choice != '4');
    do {
        cout << endl;
        cout << "是否修改该客户信息" << endl;
        cout << "1.是";
        cout << setfill(' ') << setw(10) << "2.否" << endl;
        cin >> choice;
        switch (choice) {
        case'1': {
            system("cls");
            fileReset(filename, cq, sq, prenode, current);
        }
        case'2':system("cls"); break;
        default:system("cls"); cout << "请重新输入合法的选项" << endl;
        }
    } while (choice != '1'&&choice != '2');
}

void fileReset(const string& filename,  queue& cq, queue& sq, node* prenode, node* current)//更改队列数据
{
    cout << "=============================" << endl;
    cout << "        更改项目：" << endl;
    cout << "=============================" << endl;
    char choice;
    cout << "1. 修改姓名" << endl;
    cout << "2. 修改电话号码" << endl;
    cout << "3. 修改业务种类" << endl;
    cout << "4. 修改身份证号" << endl;
    cout << "5. 删除该客户" << endl;
    cout << "6. 返回" << endl;
    cout << "=============================" << endl;
    cout << "请输入选项: ";
    cin >> choice;

    do {
        switch (choice)
        {
        case '1': {
            string newName;
            cout << "输入新的姓名: ";
            cin >> newName;
            current->C.setName(newName);
            cout << "已修改姓名为：" << newName << endl;
            cout << "按任意键继续..." << endl;
            _getch(); // 等待按键
            system("cls");
            break;
        }
        case '2': {
            int newPhone[11];
            cout << "输入新的电话号码: ";
            inputPhone(newPhone);
            current->C.setPhone(newPhone);
            cout << "已修改电话号码为：";
            for (int i = 0; i < 11; i++) {
                cout << newPhone[i];
            }
            cout << endl;
            cout << "按任意键继续..." << endl;
            _getch(); // 等待按键
            system("cls");
            break;
        }
        case '3': {
            bool newKind;
            char choice;
            do {
                cout << "请输入更改的业务类型：" << endl;
                cout << "1.普通业务";
                cout << setfill(' ') << setw(10) << "2.特殊业务" << endl;
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
            cout << "已修改业务类型为：" << (newKind ? "特殊" : "一般") << "业务" << endl;
            cout << "按任意键继续..." << endl;
            _getch(); // 等待按键
            system("cls");
            break;
        }
        case '4': {
            string newId;
            cout << "输入新的身份证号（18位）: ";
            inputId(newId);
            current->C.setId(newId);
            cout << "已修改身份证号为：" << newId << endl;

            cout << "按任意键继续..." << endl;
            _getch(); // 等待按键
            system("cls");

            break;
        }
        case '5': {
            if (prenode != current) {
                prenode->Next = current->Next;
            }
            else if (current->C.getKind() == false) {
                cq.Head = current->Next;
            }
            else {
                sq.Head = current->Next;
            }
            delete current;
            cout << "已删除该客户" << endl;
            cout << "按任意键继续..." << endl;
            _getch(); // 等待按键
            system("cls");
            break;
        }
        case '6': return;
        default:
            cout << "请输入合法的选项" << endl;
            cout << "按任意键继续..." << endl;
            _getch(); // 等待按键
        }
    } while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6');

    //覆写再追加
    filewrite(InPut, cq, true);
    filewrite(InPut, sq, false);
}