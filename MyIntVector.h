// 计算机科学与技术 雒勖博 2019111571
// LuoXubo 2020.9.30
// 支持各种插入、排序功能
#include <cassert>
#include <iostream>
#include <list>
#include <algorithm>

class MyIntVector
{
private:
    /* data */
    int *m_pData; // 储存数组
    int m_size; // 实际数组长度
    int m_capacity; // 数组最大长度
    void Reset(); // 释放目前的动态内存


public:
    MyIntVector(int size); // 构造函数
    ~MyIntVector() {Reset();} // 析构
    
    // * 赋值构造函数和复制构造函数
    MyIntVector &operator=(const MyIntVector &);
    MyIntVector (const MyIntVector &);
    // *

    // * 插入和删除
    void Insert(int index, int value);
    void Delete(int index);
    void InsertHead(int value);
    void InsertEnd(int value);
    void DeleteHead();
    void DeleteEnd();
    // *

    // * 快速排序函数 以及 它的封装函数
    void Quicksort();
    void quicksort(int l, int r);
    // * 

    // * 保留多大的内存容量
    void Reserve(int capacity);
    // *

    // * 传入list的数据
    MyIntVector(std::initializer_list<int> list);
    // *

    // * 访问
    int &at(int index)
    {
        assert( index >=0 && index < m_size);
        return m_pData[index];
    }
    // *

    inline int size() const {return m_size;}

    // * 重载访问
    int &operator[] (int index){ return m_pData[index];}
    const int &operator[](int index) const {return m_pData[index];}
    // *

    // * 重载输出流
    friend std::ostream &operator<<(std::ostream &out, const MyIntVector &arr);
    // *

    
};


std::ostream &operator<<(std::ostream &out, const MyIntVector &arr)
{
    for(int i=0;i<arr.m_size;i++)
        out << arr[i] << ' ';
    return out;
}

MyIntVector :: MyIntVector(int sz) : m_size(0), m_capacity(sz+16)
{
    m_pData = new int[sz+16]{0};
}

MyIntVector :: MyIntVector(std::initializer_list<int> list)
{
    m_size = list.size();
    m_capacity = 2*m_size + 16;
    m_pData = new int[m_capacity]{0};
    std::copy(list.begin(), list.end(), m_pData);
}

void MyIntVector::Reset()
{
    if(m_pData != nullptr)
    {
        delete[] m_pData;
        m_pData = nullptr;
        m_size = 0;
        m_capacity = 0;
    }
}

void MyIntVector:: Reserve(int capacity)
{
    if(capacity <= m_size)
        return ;
    int *pBuffer = new (std::nothrow) int[capacity]{0};
    if(pBuffer != nullptr)
    {
        for(int i=0;i<m_size;i++)
            pBuffer[i] = m_pData[i];
        Reset();
        m_pData = pBuffer;
        m_capacity = capacity;
    }
}

MyIntVector:: MyIntVector(const MyIntVector &other): m_pData(nullptr), m_size(0), m_capacity(0)
{
    Reserve(other.m_capacity);
    m_size = other.m_size;
    for(int i=0;i<m_size;i++)
        m_pData[i] = other[i];
}

MyIntVector &MyIntVector::operator=(const MyIntVector &rhs)
{
    if(this==&rhs)
        return *this;
    
    if(m_capacity < rhs.m_capacity)
        Reserve(rhs.m_capacity);
    
    m_size = rhs.m_size;
    for(int i=0;i<m_size;i++)
        m_pData[i] = rhs[i];

    return *this;
}
void MyIntVector::Delete(int index)
{
    assert(index>=0 && index<m_size);
    for(int i=index+1;i<m_size;i++)
        m_pData[i-1] = m_pData[i];
    m_size--;
    if(m_size>16 && m_size<m_capacity/4)
        Reserve(m_capacity/2);
}
void MyIntVector::Insert(int index, int value)
{
    assert(index >=0 && index<=m_size);
    if(m_size >= m_capacity)
        Reserve(m_capacity*2 + 16);
    
    if(m_capacity > 0)
    {
        m_size++;
        for(int i=m_size-1;i>index;i--)
            m_pData[i] = m_pData[i-1];
        m_pData[index] = value;
    }
}
void MyIntVector::DeleteHead()
{
    this->Delete(0);
}
void MyIntVector::DeleteEnd()
{
    this->Delete(m_size-1);
}
void MyIntVector::InsertHead(int value)
{
    this->Insert(0, value);
}
void MyIntVector::InsertEnd(int value)
{
    if(m_size == 0)
        this->Insert(0, value);
    else  
        this->Insert(m_size-1, value);
}

void MyIntVector::Quicksort()
{
    quicksort(0,m_size-1);
}
void MyIntVector::quicksort(int l, int r)
{
    if(l>=r)
        return ;
    int i=l-1, j=r+1, x=m_pData[(l+r) >> 1];
    while(i < j)
    {
        do i++; while(m_pData[i] < x);
        do j--; while(m_pData[j] > x);
        if(i < j) std::swap(m_pData[i], m_pData[j]);
    }
    quicksort(l,j);
    quicksort(j+1,r);
}

