#include <cstdio>
#include <cstring>
#include <cassert>



using namespace std;


/**
** 源文件： count_sort_test.cpp
**计数排序（算法）
 * 比较计数法
 * 分布计数法

** Just test for these function here.
** 详见代码逻辑。
** 作者：junkun huang
** 日期：2012-06-26 /
*/

int ComparisonCountingSort(int iArray[], size_t nCount, int iResult[])
{
    // 用比较计数法对数组排序
    // 输入:可排序数组 A[0 ... n-1]
    // 输出:将A中元素按照升序排列的数组 S[0 ... n-1]
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
    // 用分布计数法对数组排序,对来自于有限范围整数的一个数组进行排序
    // 输入:可排序数组 A[0 ... n-1],数组中的整数位于l和u之间( l <= u)
    // 输出:将A中元素按照升序排列的数组 S[0 ... n-1]
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
    memset(elementStat, 0, nStatCount * sizeof(int));   // 初始化频率数组
    for (size_t i = 0; i < nCount; ++i)
        elementStat[iArray[i] - iMin] += 1;             // 计算频率值
    for (size_t i = 1; i < nStatCount; ++i)
        elementStat[i] += elementStat[i-1];             // 重用于分布值

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
