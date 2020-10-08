#include <cstdio>
#include <ctime>

#include "MyIntVector.h"

const int testnum=100000;
void TestInsert(int n);

int main()
{
    TestInsert(testnum);
    system("pause");
    return 0;
}

void TestInsert(int n)
{
    MyIntVector vec1 = {}, vec2 = {};
    clock_t start1,start2,end1,end2;
    start1 = clock();
    for(int i=0;i<n;i++)
        vec1.InsertEnd(i);
    end1 = clock();

    start2 = clock();
    for(int i=0;i<n;i++)
        vec2.InsertHead(i);
    end2 = clock();

    std::cout << vec1.size() << '\n';
    std::cout << vec2.size() << '\n';
    printf("Time of inserting at end: 0.000%ld s\n ",  1000 * (end1 - start1) / CLOCKS_PER_SEC);
    printf("Time of inserting at head: %ld s\n ", (end2 - start2) / CLOCKS_PER_SEC);
}
