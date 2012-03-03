
#ifndef __SORT_FIND_H_
#define __SORT_FIND_H_

#include "stdafx.h"
//---------------------------------------------------------------------------

typedef long KeyType; // 定义关键字类型为整型
typedef long InfoType; // 定义其它数据项的类型

typedef struct RedType // 记录类型
{
    KeyType		key; // 关键字项
    InfoType	value; // 其它数据项，具体类型在主程中定义
} RedType;

typedef struct SqList // 顺序表类型
{
    RedType*	data; // r[0]闲置或用作哨兵单元
    long		length; // 顺序表长度
} SqList;

//定义全局变量(以下)
//排序方式：-1，降序；1，升序；然而降序只是一个假象--在输出时倒序输出（小技巧）
int g_sort_mode = 1;
//初始化数据方式：-1，未初始化；0，随机；1，升序；2，降序、、、
int g_init_data_mode = -1;
//记录选用的排序算法，以方便文件名表示、、、0表示未选用算法
int g_select_sort_algo = 0;
//标志当前数据是否保存！！！
bool g_savefile_flag = false;
//标志当前数据是否已经排序！！！
bool g_sorted_flag = false;
//标志是否已经初始化数据
bool g_init_flag = false;
//存放输出各排序结果文件名
string	g_filename[10];
//排序过程的比较，赋值次数，计数器
unsigned long		g_sort_assgin_count = 0, g_sort_comp_count =0;
//初始化数据长度
long g_length; //temp_len
//查找的数据：键值，位置
RedType g_search_data;
//查找的数据过程中判断次数
unsigned long g_find_comp_count = 0;
//加载标志
bool g_load_flag = false;



#define EQ(a,b) ((a) == (b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))



//---------------------------------------------------------------------------
//冒泡排序
void BubbleSort(SqList &L)
{
    // 将a中整数序列重新排列成自小至大有序的整数序列(起泡排序)

    RedType	t;
    for (int i=L.length; i>=1; --i)
    {
        bool is_changed = false;
        for (int j=1; j<i; ++j)
        {
            if (L.data[j].key > L.data[j+1].key)
            {
                t = L.data[j];
                L.data[j] = L.data[j+1];
                L.data[j+1] = t;
                is_changed = true;
                g_sort_assgin_count += 3;
            }
            ++g_sort_comp_count;
        }
        if (!is_changed)
            break;
    }
}

//---------------------------------------------------------------------------
// 简单选择排序

int SelectMinKey(const SqList& L,const int& i)
{
    // 返回在L.data[i..L.length]中key最小的记录的序号
    KeyType min;
    int j,k;
    k = i; // 设第i个为最小
    min=L.data[i].key;
    ++g_sort_assgin_count;
    for (j=i+1; j<=L.length; j++)
    {
        if (L.data[j].key<min) // 找到更小的
        {
            k=j;
            min=L.data[j].key;
        }
        ++g_sort_assgin_count;
        ++g_sort_comp_count;

    }
    return k;
}

void SelectSort(SqList &L)
{
    // 对顺序表L作简单选择排序。
    //int i,j;
    RedType t;
    for (int i=1; i<L.length; ++i)
    {
        //  选择第i小的记录，并交换到位
        int	j=SelectMinKey(L,i); // 在L.data[i..L.length]中选择key最小的记录
        if (i!=j)
        {
            // 与第i个记录交换
            t=L.data[i];
            L.data[i]=L.data[j];
            L.data[j]=t;
            g_sort_assgin_count += 3;
        }
    }
}
//---------------------------------------------------------------------------
// 对顺序表L作快速排序。

int Partition(SqList &L,int low,int high)
{
    // 交换顺序表L中子表L.data[low..high]的记录，使枢轴记录到位，
    // 并返回其所在位置，此时在它之前(后)的记录均不大(小)于它。
    RedType t;
    KeyType pivotkey = L.data[low].key; // 用子表的第一个记录作枢轴记录
    while (low<high)
    {
        // 从表的两端交替地向中间扫描
        while (low<high && L.data[high].key>=pivotkey)
        {
            --high;
            ++g_sort_comp_count;
        }
        t=L.data[low]; // 将比枢轴记录小的记录交换到低端
        L.data[low]=L.data[high];
        L.data[high]=t;
        while (low<high && L.data[low].key<=pivotkey)
        {
            ++low;
            ++g_sort_comp_count;
        }
        t=L.data[low]; // 将比枢轴记录大的记录交换到高端
        L.data[low]=L.data[high];
        L.data[high]=t;
        g_sort_assgin_count += 3;
    }
    return low; // 返回枢轴所在位置
}
void QSort(SqList &L,int low,int high)
{
    // 对顺序表L中的子序列L.data[low..high]作快速排序。
    int pivotloc;
    if (low < high)
    {
        // 长度大于1
        pivotloc=Partition(L, low, high); // 将L.data[low..high]一分为二
        QSort(L, low, pivotloc-1); // 对低子表递归排序，pivotloc是枢轴位置
        QSort(L, pivotloc+1, high); // 对高子表递归排序
    }
}

//---------------------------------------------------------------------------
void QuickSort(SqList &L)
{
    // 对顺序表L作快速排序。
    QSort(L,1,L.length);
}

// 对顺序表L作归并排序。方法一！！！
//*
 void Merge(RedType* &SR,RedType* &TR,long i,long m,long n)
 { // 将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n]
   //int j,k,l;
   for (int j=m+1,k=i;i<=m && j<=n;++k) // 将SR中记录由小到大地并入TR
   {
     if (LQ(SR[i].key,SR[j].key))
		TR[k]=SR[i++];
     else
		TR[k]=SR[j++];
	++g_sort_assgin_count;
	 ++g_sort_comp_count;
   }
   if (i<=m)
   {
     for (int l=0;l<=m-i;l++)
	 {
       TR[k+l]=SR[i+l]; // 将剩余的SR[i..m]复制到TR
	  ++g_sort_assgin_count;
	 }
   }
   //if (j<=n)
   else
   {
     for (int l=0;l<=n-j;l++)
	 {
       TR[k+l]=SR[j+l]; // 将剩余的SR[j..n]复制到TR
	  ++g_sort_assgin_count;
	 }
   }
   ++g_sort_comp_count;
 }

 void MSort(RedType SR[],RedType TR1[],long s, long t)
 { // 将SR[s..t]归并排序为TR1[s..t].

	if (s == t)
	{
		TR1[s] = SR[s];
	}
	else
	{
		//int m;
		//int length = t-s+1;//
		RedType* TR2 = new RedType[length+1];
		long	m = (s+t)/2; // 将SR[s..t]平分为SR[s..m]和SR[m+1..t]
		MSort(SR,TR2,s,m); // 递归地将SR[s..m]归并为有序的TR2[s..m]
		MSort(SR,TR2,m+1,t); // 递归地将SR[m+1..t]归并为有序的TR2[m+1..t]
		Merge(TR2,TR1,s,m,t); // 将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t]

		delete[] TR2;
	}
	++g_sort_comp_count;

 }

 void MergeSort(SqList &L)
 { // 对顺序表L作归并排序。
	 MSort(L.data,L.data,1,L.length);
 }

//---------------------------------------------------------------------------
// 对顺序表L作归并排序。方法二
//************合并排序******************************
void   Merge2(SqList  &L1, SqList  &L2, SqList  &L)
{
    long   i=1,j=1,k=1;
    while ( i<=L1.length && j<=L2.length )
    {
        if (L1.data[i].key<=L2.data[j].key)
        {
            L.data[k]=L1.data[i];
            i++;
        }
        else
        {
            L.data[k]=L2.data[j];
            j++;
        }
        k++;
        ++g_sort_assgin_count;
        ++g_sort_comp_count;
    }
    if ( (i-1) == L1.length )
        for (; j<=L2.length; j++,k++)
        {
            L.data[k]=L2.data[j];
            ++g_sort_assgin_count;
        }
    else
        for (; i<=L1.length; i++,k++)
        {
            L.data[k]=L1.data[i];
            ++g_sort_assgin_count;
        }
}
void   MergeSort2(SqList  &L)
{
    long   i,j;
    SqList  L1,L2;

    if ( L.length>1)
    {
        L1.data = new RedType [L.length/2+1];
        L2.data = new RedType [L.length/2+2];

        for (i=1; i<=L.length/2; i++)
            L1.data[i] = L.data[i];
        L1.length = i-1;
        for (j=i; j<=L.length; j++)
            L2.data[j-i+1] = L.data[j];
        L2.length = L.length - L1.length;
        MergeSort(L1);
        MergeSort(L2);
        Merge(L1,L2,L);

        delete[] L1.data;
        delete[] L2.data;
    }

}
//---------------------------------------------------------------------------
void InsertSort(SqList &L)
{
    // 对顺序表L作直接插入排序。
    //int i,j;
    for (int i=2; i<=L.length; ++i)
    {
        if (L.data[i].key < L.data[i-1].key) // "<",需将L.data[i]插入有序子表
        {
            L.data[0]=L.data[i]; // 复制为哨兵
            ++g_sort_assgin_count;
            int j=i-1;
            for (; L.data[0].key<L.data[j].key; --j)
            {
                L.data[j+1]=L.data[j]; // 记录后移
				++g_sort_assgin_count;
				++g_sort_comp_count;
            }

            L.data[j+1]=L.data[0]; // 插入到正确位置
            ++g_sort_assgin_count;
        }
        ++g_sort_assgin_count;
        ++g_sort_comp_count;
    }
}
//---------------------------------------------------------------------------
void BInsertSort(SqList &L)
{
    // 对顺序表L作折半插入排序。
    int i,j,m,low,high;
    for (i=2; i<=L.length; ++i)
    {
        L.data[0]=L.data[i]; // 将L.data[i]暂存到L.data[0]
        low=1;
        high=i-1;
        while (low<=high)
        {
            // 在r[low..high]中折半查找有序插入的位置
            m=(low+high)/2; // 折半
            if LT(L.data[0].key,L.data[m].key)
                high=m-1; // 插入点在低半区
            else
                low=m+1; // 插入点在高半区
            ++g_sort_assgin_count;
            ++g_sort_comp_count;
        }
        for (j=i-1; j>=high+1; --j)
        {
            L.data[j+1]=L.data[j]; // 记录后移
            ++g_sort_assgin_count;//???
        }
        L.data[high+1]=L.data[0]; // 插入
        ++g_sort_assgin_count;
    }
}
//---------------------------------------------------------------------------
void P2InsertSort(SqList &L)
{
    // 2_路插入排序
    int first, final;
    RedType	*d;
    //d=(RedType*)malloc(L.length*sizeof(RedType)); // 生成L.length个记录的临时空间
    d = new RedType[L.length];
    d[0] = L.data[1]; // 设L的第1个记录为d中排好序的记录(在位置[0])
    first = final = 0; // first、final分别指示d中排好序的记录的第1个和最后1个记录的位置
    for (int i=2; i<=L.length; ++i)
    {
        // 依次将L的第2个～最后1个记录插入d中
        if (L.data[i].key<d[first].key)
        {
            // 待插记录小于d中最小值，插到d[first]之前(不需移动d数组的元素)
            first=(first-1+L.length)%L.length; // 设d为循环向量
            d[first]=L.data[i];
            ++g_sort_assgin_count;
        }
        else
        {
            if (L.data[i].key > d[final].key)
            {
                // 待插记录大于d中最大值，插到d[final]之后(不需移动d数组的元素)
                final=final+1;
                d[final]=L.data[i];
                ++g_sort_assgin_count;
            }
            else
            {
                // 待插记录大于d中最小值，小于d中最大值，插到d的中间(需要移动d数组的元素)
                int	j;
                j = final++; // 移动d的尾部元素以便按序插入记录
                ++g_sort_comp_count;
                while (L.data[i].key < d[j].key)
                {
                    d[(j+1)%L.length]=d[j];
                    j=(j-1+L.length)%L.length;
                    ++g_sort_assgin_count;
                    ++g_sort_comp_count;
                }
                d[j+1]=L.data[i];
                ++g_sort_assgin_count;
            }
            ++g_sort_comp_count;
        }
    }
    ++g_sort_comp_count;
    for (int i=1; i<=L.length; i++) // 把d赋给L.data
    {
        L.data[i]=d[(i+first-1)%L.length]; // 线性关系
        ++g_sort_assgin_count;
    }
    //delete[] d;
}
//---------------------------------------------------------------------------
void HeapBottomUp(RedType H[], int i, int n )//RedType* &H
{
    //构造大顶堆
    int	k = i;
    RedType	temp = H[k];
    ++g_sort_assgin_count;
    bool heap_flag = false;
    while ( !heap_flag && (2*k)<=n )
    {
        int	j = 2*k;
        ++g_sort_comp_count;
        if ( j<n )
        {
            //存在两个子节点
            if ( H[j].key < H[j+1].key )
                j = j+1;
            ++g_sort_comp_count;
        }
        ++g_sort_comp_count;
        if ( temp.key >= H[j].key )
            heap_flag = true;
        else
        {
            H[k] = H[j];
            ++g_sort_assgin_count;
            k = j;
        }
    }
    H[k] = temp;
    ++g_sort_assgin_count;
}
//---------------------------------------------------------------------------
void HeapSort(SqList &L)
{
    //堆排序
    for (int i=L.length/2; i>=1; i--)
    {
        HeapBottomUp( L.data, i, L.length);
    }

    for (int i=L.length; i>1; i--)
    {
        /**/
        RedType		temp;
        temp = L.data[1];
        L.data[1] = L.data[i];
        L.data[i] = temp;
        g_sort_assgin_count += 3;

        HeapBottomUp( L.data, 1, i-1);
    }

}
//---------------------------------------------------------------------------
// 希尔排序
void ShellInsert(SqList &L,int dk)
{
    // 对顺序表L作一趟希尔插入排序。本算法是和一趟直接插入排序相比，
    // 作了以下修改：
    // 1.前后记录位置的增量是dk,而不是1;
    // 2.data[0]只是暂存单元,不是哨兵。当j<=0时,插入位置已找到。
    int i,j;
    for (i=dk+1; i<=L.length; ++i)
    {
        if ( L.data[i].key < L.data[i-dk].key )
        {
            // 需将L.data[i]插入有序增量子表
            L.data[0]=L.data[i]; // 暂存在L.data[0]
            for (j=i-dk; j>0 && LT(L.data[0].key,L.data[j].key); j-=dk)
            {
                L.data[j+dk]=L.data[j]; // 记录后移，查找插入位置
            }
            L.data[j+dk]=L.data[0]; // 插入
        }
    }
}
//---------------------------------------------------------------------------


void ShellSort(SqList &L)
{
    // 按增量序列dlta[0..t-1]对顺序表L作希尔排序。

    int	dlta[3] = {5,3,1}; // 增量序列数组
    for (int i=0; i<3; ++i)
    {
        ShellInsert(L,dlta[i]); // 一趟增量为dlta[i]的插入排序
    }
}
//---------------------------------------------------------------------------
bool SequentialFind(const SqList &L, RedType& g_search_data)
{
    //顺序查找

    if (L.length < 1)
    {
        std::cerr << "\n	查找失败，字符串集合为空！\n";
        return false;
    }
    for (int i=1; i<L.length; i++)
    {
        g_find_comp_count++;
        if (L.data[i].key == g_search_data.key)
        {
            //记录数据所在位置
            g_search_data.value = i;
            return true;
        }
    }
    return false;
}
//---------------------------------------------------------------------------

bool BinaryFind(const SqList &L,  RedType& g_search_data )
{
    //折半查找
    if (L.length < 1)
    {
        std::cerr << "\n	查找失败，字符串集合为空！\n";
        return false;
    }
    int begin = 1,  end = L.length+1;
    int position = (begin+end)/2;

    do
	{
		g_find_comp_count++;
        if ( g_search_data.key == L.data[position].key )
        {
            g_search_data.value = position;
            return true;
        }
        else if (g_search_data.key > L.data[position].key)
        {
            begin = position+1;
            position = (begin+end)/2;
        }
        else
        {
            end = position-1;
            position = (begin+end)/2;
		}
    } while (begin <= end );

    return false;
}
//---------------------------------------------------------------------------
bool InterpolationFind(const SqList &L,  RedType& g_search_data )
{
    //插值查找
    g_find_comp_count++;
    if (L.length < 1)
    {
        std::cerr << "\n	查找失败，字符串集合为空！\n";
        return false;
    }
    int begin = 1,  end = L.length;
    int position = begin + (g_search_data.key-L.data[begin].key)*(end-begin)/(L.data[end].key-L.data[begin].key);

    do
    {
        g_find_comp_count++;
        if ( g_search_data.key == L.data[position].key )
        {
            g_search_data.value = position;
            return true;
        }

        g_find_comp_count++;
        if (g_search_data.key > L.data[position].key)
        {
            begin = position+1;
            position = begin + (g_search_data.key-L.data[begin].key)*(end-begin)/(L.data[end].key-L.data[begin].key);
        }
        else
        {
            end = position-1;
            position = begin + (g_search_data.key-L.data[begin].key)*(end-begin)/(L.data[end].key-L.data[begin].key);
        }
        g_find_comp_count++;
    }
    while (begin <= end );

    return false;
}
//---------------------------------------------------------------------------

/// 基数排序 ///
//(radix sort）则是属于“分配式排序”（distribution sort），基数排序法又称“桶子法”（bucket sort）或bin sort，顾名思义，它是透过键值的部份资讯，
// 将要排序的元素分配至某些“桶”中，藉以达到排序的作用，基数排序法是属于稳定性的排序，其时间复杂度为O (nlog(r)m)，
// 其中r为所采取的基数，而m为堆数，在某些时候，基数排序法的效率高于其它的比较性排序法。

/// 效率分析
// 时间效率：设待排序列为n个记录，d个关键码，关键码的取值范围为radix，则进行链式基数排序的时间复杂度为O(d(n+radix))，
// 其中，一趟分配时间复杂度为O(n)，一趟收集时间复杂度为O(n)，共进行d趟分配和收集。

// 空间效率：需要2*radix个指向队列的辅助空间，以及用于静态链表的n个指针。

/// 实现的方法
//最高位优先(Most Significant Digit first)法，简称MSD法：先按k1排序分组，同一组中记录，关键码k1相等，再对各组按k2排序分成子组，
//之后，对后面的关键码继续这样的排序分组，直到按最次位关键码kd对各子组排序后。再将各组连接起来，便得到一个有序序列。

//最低位优先(Least Significant Digit first)法，简称LSD法：先从kd开始排序，再对kd-1进行排序，依次重复，直到对k1排序后便得到一个有序序列。


/// 基数排序（LSD法）演示 ///
int test_distribution_sort()
{
    const unsigned DATA_COUNT = 10;
    int data[DATA_COUNT]= {73,22,93,43,55,14,28,65,39,81};
	int max_data = 93;
    int temp[DATA_COUNT][DATA_COUNT]= {0};
    int order[DATA_COUNT]= {0};

    printf("\n排序前: ");
    for (int i=0; i<10; ++i)
        printf("%d ",data[i]);
    putchar('\n');

    for (int n = 1; n <= max_data; n *= 10)
    {
        for (int i=0; i<10; ++i)
        {
            int lsd=((data[i]/n)%10);
            temp[lsd][order[lsd]]=data[i];
            ++order[lsd];
        }
        printf("\n重新排列: ");
        int k = 0;
        for (int i=0; i<10; ++i)
        {
            if(order[i]!=0)
                for (int j=0; j<order[i]; ++j)
                {
                    data[k]=temp[i][j];
                    printf("%d ",data[k]);
                    k++;
                }
            order[i]=0;
        }
    }
    putchar('\n');
    printf("\n排序后: ");
    for (int i=0; i<10; i++)
        printf("%d ",data[i]);

    putchar('\n');
    return 0;

}

#endif /// __SORT_FIND_H_
