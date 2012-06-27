#include <cstdio>
#include <cstring>
#include <cassert>



using namespace std;


/**
** Դ�ļ��� count_sort_test.cpp
**���������㷨��
 * �Ƚϼ�����
 * �ֲ�������

** Just test for these function here.
** ��������߼���
** ���ߣ�junkun huang
** ���ڣ�2012-06-26 /
*/

int ComparisonCountingSort(int iArray[], size_t nCount, int iResult[])
{
    // �ñȽϼ���������������
    // ����:���������� A[0 ... n-1]
    // ���:��A��Ԫ�ذ����������е����� S[0 ... n-1]
//    assert (iResult < iArray && iResult >= iArray + nCount);
//    if (!(iResult < iArray && iResult >= iArray + nCount))
//        return -1;
    assert (iResult != iArray );
    if (iResult == iArray)
        return -1;
    if (!(iArray && iResult && nCount > 1))
        return -1;

    int* elementCount = new int [nCount];
    assert (elementCount);
//    for (size_t i = 0; i < nCount; ++i)
//        elementCount[i] = 0;
    memset(elementCount, 0, nCount * sizeof(int));
    for (size_t i = 0; i < nCount - 1; ++i)
        for (size_t j = i+1; j < nCount; ++j)
        {
            if (iArray[i] < iArray[j])
                elementCount[j] += 1;
            else
                elementCount[i] += 1;
        }

    for (size_t i = 0; i < nCount; ++i)
        iResult[elementCount[i]]= iArray[i];

    delete [] elementCount;
    return 0;
}

int DistributionCountingSort(int iArray[], size_t nCount, int iMin, int iMax, int iResult[])
{
    // �÷ֲ�����������������,�����������޷�Χ������һ�������������
    // ����:���������� A[0 ... n-1],�����е�����λ��l��u֮��( l <= u)
    // ���:��A��Ԫ�ذ����������е����� S[0 ... n-1]
//    assert (iResult < iArray && iResult > iArray + nCount);
//    if (!(iResult < iArray && iResult > iArray + nCount))
//        return -1;
    assert (iResult != iArray );
    if (iResult == iArray)
        return -1;
    if (!(iArray && iResult && nCount > 1))
        return -1;
    if (!(iMax > iMin))
        return -1;

    const size_t nStatCount = iMax - iMin + 1;
    int* elementStat = new int [nStatCount];
    assert (elementStat);
    memset(elementStat, 0, nStatCount * sizeof(int));   // ��ʼ��Ƶ������
    for (size_t i = 0; i < nCount; ++i)
        elementStat[iArray[i] - iMin] += 1;             // ����Ƶ��ֵ
    for (size_t i = 1; i < nStatCount; ++i)
        elementStat[i] += elementStat[i-1];             // �����ڷֲ�ֵ

    for (int i = nCount - 1; i >= 0; --i)
    {
        size_t j = iArray[i] - iMin;
        iResult[elementStat[j] - 1] = iArray[i];
        elementStat[j] -= 1;
    }
    delete [] elementStat;
    return 0;
}

void PrintArray(int iArray[], size_t nCount)
{
    for (size_t i = 0; i < nCount; ++i)
        printf(" %d ", iArray[i]);
    printf("\n");
}
int main()
{
    const unsigned TEST_ELEMENT_COUNT = 10;
    int iArray[TEST_ELEMENT_COUNT] = { 6, -1, 5, 4, 3, 2, 1, 0 ,3, -1};
    int iMax = 6, iMin = -1;
    int iResult1[TEST_ELEMENT_COUNT], iResult2[TEST_ELEMENT_COUNT];
    ComparisonCountingSort(iArray, TEST_ELEMENT_COUNT, iResult1);

    DistributionCountingSort(iArray, TEST_ELEMENT_COUNT, iMin, iMax, iResult2);

    PrintArray(iArray, TEST_ELEMENT_COUNT);
    PrintArray(iResult1, TEST_ELEMENT_COUNT);
    PrintArray(iResult2, TEST_ELEMENT_COUNT);
    /*********/
    printf(" Hello world!\n");
    return 0;
}
