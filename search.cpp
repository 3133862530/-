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
        cout << "        ��ѯ����" << endl;
        cout << "=============================" << endl;
        cout << "��ѡ���ѯ���ݵķ�ʽ��" << endl;
        cout << "1. ��������ѯ" << endl;
        cout << "2. �����֤�Ų�ѯ" << endl;
        cout << "3. ���绰�����ѯ" << endl;
        cout << "4. ����" << endl;
        cout << "=============================" << endl;
    }


void filesearch(string filename) // ����������ѯ���������������Ϣ
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
            cout << "����������" << endl;
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
                cout << "δ�ҵ��ÿͻ�����Ϣ��" << endl;
                cout << "�����������..." << endl;
                _getch(); // �ȴ�����
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
            cout << "�������֤�ţ�" << endl;
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
                cout << "δ�ҵ��ÿͻ�����Ϣ��" << endl;
                cout << "�����������..." << endl;
                _getch(); // �ȴ�����
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
            cout << "����绰���룺" << endl;
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
                cout << "δ�ҵ��ÿͻ�����Ϣ��" << endl;
                cout << "�����������..." << endl;
                _getch(); // �ȴ�����
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
            cout << "��Ч��ѡ�����������" << endl;
        }
    } while (choice != '1' && choice != '2' && choice != '3' && choice != '4');
    do {
        cout << endl;
        cout << "�Ƿ��޸ĸÿͻ���Ϣ" << endl;
        cout << "1.��";
        cout << setfill(' ') << setw(10) << "2.��" << endl;
        cin >> choice;
        switch (choice) {
        case'1': {
            system("cls");
            fileReset(filename, cq, sq, prenode, current);
        }
        case'2':system("cls"); break;
        default:system("cls"); cout << "����������Ϸ���ѡ��" << endl;
        }
    } while (choice != '1'&&choice != '2');
}

void fileReset(const string& filename,  queue& cq, queue& sq, node* prenode, node* current)//���Ķ�������
{
    cout << "=============================" << endl;
    cout << "        ������Ŀ��" << endl;
    cout << "=============================" << endl;
    char choice;
    cout << "1. �޸�����" << endl;
    cout << "2. �޸ĵ绰����" << endl;
    cout << "3. �޸�ҵ������" << endl;
    cout << "4. �޸����֤��" << endl;
    cout << "5. ɾ���ÿͻ�" << endl;
    cout << "6. ����" << endl;
    cout << "=============================" << endl;
    cout << "������ѡ��: ";
    cin >> choice;

    do {
        switch (choice)
        {
        case '1': {
            string newName;
            cout << "�����µ�����: ";
            cin >> newName;
            current->C.setName(newName);
            cout << "���޸�����Ϊ��" << newName << endl;
            cout << "�����������..." << endl;
            _getch(); // �ȴ�����
            system("cls");
            break;
        }
        case '2': {
            int newPhone[11];
            cout << "�����µĵ绰����: ";
            inputPhone(newPhone);
            current->C.setPhone(newPhone);
            cout << "���޸ĵ绰����Ϊ��";
            for (int i = 0; i < 11; i++) {
                cout << newPhone[i];
            }
            cout << endl;
            cout << "�����������..." << endl;
            _getch(); // �ȴ�����
            system("cls");
            break;
        }
        case '3': {
            bool newKind;
            char choice;
            do {
                cout << "��������ĵ�ҵ�����ͣ�" << endl;
                cout << "1.��ͨҵ��";
                cout << setfill(' ') << setw(10) << "2.����ҵ��" << endl;
                cin >> choice;
                switch (choice) {
                case '1':
                    newKind = false;
                    break;
                case '2':
                    newKind = true;
                    break;
                default:cout << "������Ϸ���ѡ��" << endl;
                }
            } while (choice != '1' && choice != '2');
            current->C.setKind(newKind);
            cout << "���޸�ҵ������Ϊ��" << (newKind ? "����" : "һ��") << "ҵ��" << endl;
            cout << "�����������..." << endl;
            _getch(); // �ȴ�����
            system("cls");
            break;
        }
        case '4': {
            string newId;
            cout << "�����µ����֤�ţ�18λ��: ";
            inputId(newId);
            current->C.setId(newId);
            cout << "���޸����֤��Ϊ��" << newId << endl;

            cout << "�����������..." << endl;
            _getch(); // �ȴ�����
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
            cout << "��ɾ���ÿͻ�" << endl;
            cout << "�����������..." << endl;
            _getch(); // �ȴ�����
            system("cls");
            break;
        }
        case '6': return;
        default:
            cout << "������Ϸ���ѡ��" << endl;
            cout << "�����������..." << endl;
            _getch(); // �ȴ�����
        }
    } while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6');

    //��д��׷��
    filewrite(InPut, cq, true);
    filewrite(InPut, sq, false);
}