#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <algorithm>

// ����һ��ģ����vector
template <typename T>
class vector {
private:
    T* data;         // ָ��̬���������ָ��
    int capacity; // ���������
    int length;   // �����е�ǰ�洢��Ԫ������
public:
    vector() : data(nullptr), capacity(0), length(0) {}
    ~vector() {
        delete[] data;
    }

    // push_back��������������ĩβ���һ��Ԫ��
    void push_back(const T& value) {
        if (length == capacity) { // �����ǰ���ȵ�����������Ҫ����
            resize(capacity == 0 ? 1 : capacity * 2); // �����������ʼ��Ϊ1
        }
        data[length++] = value; // ���Ԫ�ز����³���
    }

    // pop_back���������Ƴ�����ĩβ��Ԫ��
    void pop_back() {
        if (length > 0) { // ������鲻Ϊ��
            --length; // ���ٳ��ȣ�ʵ���ϲ���ɾ��Ԫ�أ�ֻ�ǲ��ٷ�����
        }
    }

    // ����[]��������ṩ��Ԫ�ص��������
    T& operator[](int index) {
        return data[index]; // ����ָ����������Ԫ������
    }

    // ����[]������ĳ����汾������const����
    const T& operator[](int index) const {
        return data[index]; // ����ָ����������Ԫ�س�������
    }

    // size�������������е�ǰ�洢��Ԫ������
    int size() const {
        return length;
    }

    // resize�������ڵ�����������
    void resize(int new_capacity) {
        T* new_data = new T[new_capacity]; // �����µ�����
        copy(data, data + length, new_data); // ���������е����ݸ��Ƶ�������
        delete[] data; // ɾ��������
        data = new_data; // ����dataָ��ָ��������
        capacity = new_capacity; // ��������
    }
};

#endif
