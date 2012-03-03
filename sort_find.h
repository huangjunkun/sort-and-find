
#ifndef __SORT_FIND_H_
#define __SORT_FIND_H_

#include "stdafx.h"
//---------------------------------------------------------------------------

typedef long KeyType; // ����ؼ�������Ϊ����
typedef long InfoType; // �������������������

typedef struct RedType // ��¼����
{
    KeyType		key; // �ؼ�����
    InfoType	value; // ������������������������ж���
} RedType;

typedef struct SqList // ˳�������
{
    RedType*	data; // r[0]���û������ڱ���Ԫ
    long		length; // ˳�����
} SqList;

//����ȫ�ֱ���(����)
//����ʽ��-1������1������Ȼ������ֻ��һ������--�����ʱ���������С���ɣ�
int g_sort_mode = 1;
//��ʼ�����ݷ�ʽ��-1��δ��ʼ����0�������1������2�����򡢡���
int g_init_data_mode = -1;
//��¼ѡ�õ������㷨���Է����ļ�����ʾ������0��ʾδѡ���㷨
int g_select_sort_algo = 0;
//��־��ǰ�����Ƿ񱣴棡����
bool g_savefile_flag = false;
//��־��ǰ�����Ƿ��Ѿ����򣡣���
bool g_sorted_flag = false;
//��־�Ƿ��Ѿ���ʼ������
bool g_init_flag = false;
//���������������ļ���
string	g_filename[10];
//������̵ıȽϣ���ֵ������������
unsigned long		g_sort_assgin_count = 0, g_sort_comp_count =0;
//��ʼ�����ݳ���
long g_length; //temp_len
//���ҵ����ݣ���ֵ��λ��
RedType g_search_data;
//���ҵ����ݹ������жϴ���
unsigned long g_find_comp_count = 0;
//���ر�־
bool g_load_flag = false;



#define EQ(a,b) ((a) == (b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))



//---------------------------------------------------------------------------
//ð������
void BubbleSort(SqList &L)
{
    // ��a�����������������г���С�����������������(��������)

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
// ��ѡ������

int SelectMinKey(const SqList& L,const int& i)
{
    // ������L.data[i..L.length]��key��С�ļ�¼�����
    KeyType min;
    int j,k;
    k = i; // ���i��Ϊ��С
    min=L.data[i].key;
    ++g_sort_assgin_count;
    for (j=i+1; j<=L.length; j++)
    {
        if (L.data[j].key<min) // �ҵ���С��
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
    // ��˳���L����ѡ������
    //int i,j;
    RedType t;
    for (int i=1; i<L.length; ++i)
    {
        //  ѡ���iС�ļ�¼����������λ
        int	j=SelectMinKey(L,i); // ��L.data[i..L.length]��ѡ��key��С�ļ�¼
        if (i!=j)
        {
            // ���i����¼����
            t=L.data[i];
            L.data[i]=L.data[j];
            L.data[j]=t;
            g_sort_assgin_count += 3;
        }
    }
}
//---------------------------------------------------------------------------
// ��˳���L����������

int Partition(SqList &L,int low,int high)
{
    // ����˳���L���ӱ�L.data[low..high]�ļ�¼��ʹ�����¼��λ��
    // ������������λ�ã���ʱ����֮ǰ(��)�ļ�¼������(С)������
    RedType t;
    KeyType pivotkey = L.data[low].key; // ���ӱ�ĵ�һ����¼�������¼
    while (low<high)
    {
        // �ӱ�����˽�������м�ɨ��
        while (low<high && L.data[high].key>=pivotkey)
        {
            --high;
            ++g_sort_comp_count;
        }
        t=L.data[low]; // ���������¼С�ļ�¼�������Ͷ�
        L.data[low]=L.data[high];
        L.data[high]=t;
        while (low<high && L.data[low].key<=pivotkey)
        {
            ++low;
            ++g_sort_comp_count;
        }
        t=L.data[low]; // ���������¼��ļ�¼�������߶�
        L.data[low]=L.data[high];
        L.data[high]=t;
        g_sort_assgin_count += 3;
    }
    return low; // ������������λ��
}
void QSort(SqList &L,int low,int high)
{
    // ��˳���L�е�������L.data[low..high]����������
    int pivotloc;
    if (low < high)
    {
        // ���ȴ���1
        pivotloc=Partition(L, low, high); // ��L.data[low..high]һ��Ϊ��
        QSort(L, low, pivotloc-1); // �Ե��ӱ�ݹ�����pivotloc������λ��
        QSort(L, pivotloc+1, high); // �Ը��ӱ�ݹ�����
    }
}

//---------------------------------------------------------------------------
void QuickSort(SqList &L)
{
    // ��˳���L����������
    QSort(L,1,L.length);
}

// ��˳���L���鲢���򡣷���һ������
//*
 void Merge(RedType* &SR,RedType* &TR,long i,long m,long n)
 { // �������SR[i..m]��SR[m+1..n]�鲢Ϊ�����TR[i..n]
   //int j,k,l;
   for (int j=m+1,k=i;i<=m && j<=n;++k) // ��SR�м�¼��С����ز���TR
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
       TR[k+l]=SR[i+l]; // ��ʣ���SR[i..m]���Ƶ�TR
	  ++g_sort_assgin_count;
	 }
   }
   //if (j<=n)
   else
   {
     for (int l=0;l<=n-j;l++)
	 {
       TR[k+l]=SR[j+l]; // ��ʣ���SR[j..n]���Ƶ�TR
	  ++g_sort_assgin_count;
	 }
   }
   ++g_sort_comp_count;
 }

 void MSort(RedType SR[],RedType TR1[],long s, long t)
 { // ��SR[s..t]�鲢����ΪTR1[s..t].

	if (s == t)
	{
		TR1[s] = SR[s];
	}
	else
	{
		//int m;
		//int length = t-s+1;//
		RedType* TR2 = new RedType[length+1];
		long	m = (s+t)/2; // ��SR[s..t]ƽ��ΪSR[s..m]��SR[m+1..t]
		MSort(SR,TR2,s,m); // �ݹ�ؽ�SR[s..m]�鲢Ϊ�����TR2[s..m]
		MSort(SR,TR2,m+1,t); // �ݹ�ؽ�SR[m+1..t]�鲢Ϊ�����TR2[m+1..t]
		Merge(TR2,TR1,s,m,t); // ��TR2[s..m]��TR2[m+1..t]�鲢��TR1[s..t]

		delete[] TR2;
	}
	++g_sort_comp_count;

 }

 void MergeSort(SqList &L)
 { // ��˳���L���鲢����
	 MSort(L.data,L.data,1,L.length);
 }

//---------------------------------------------------------------------------
// ��˳���L���鲢���򡣷�����
//************�ϲ�����******************************
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
    // ��˳���L��ֱ�Ӳ�������
    //int i,j;
    for (int i=2; i<=L.length; ++i)
    {
        if (L.data[i].key < L.data[i-1].key) // "<",�轫L.data[i]���������ӱ�
        {
            L.data[0]=L.data[i]; // ����Ϊ�ڱ�
            ++g_sort_assgin_count;
            int j=i-1;
            for (; L.data[0].key<L.data[j].key; --j)
            {
                L.data[j+1]=L.data[j]; // ��¼����
				++g_sort_assgin_count;
				++g_sort_comp_count;
            }

            L.data[j+1]=L.data[0]; // ���뵽��ȷλ��
            ++g_sort_assgin_count;
        }
        ++g_sort_assgin_count;
        ++g_sort_comp_count;
    }
}
//---------------------------------------------------------------------------
void BInsertSort(SqList &L)
{
    // ��˳���L���۰��������
    int i,j,m,low,high;
    for (i=2; i<=L.length; ++i)
    {
        L.data[0]=L.data[i]; // ��L.data[i]�ݴ浽L.data[0]
        low=1;
        high=i-1;
        while (low<=high)
        {
            // ��r[low..high]���۰������������λ��
            m=(low+high)/2; // �۰�
            if LT(L.data[0].key,L.data[m].key)
                high=m-1; // ������ڵͰ���
            else
                low=m+1; // ������ڸ߰���
            ++g_sort_assgin_count;
            ++g_sort_comp_count;
        }
        for (j=i-1; j>=high+1; --j)
        {
            L.data[j+1]=L.data[j]; // ��¼����
            ++g_sort_assgin_count;//???
        }
        L.data[high+1]=L.data[0]; // ����
        ++g_sort_assgin_count;
    }
}
//---------------------------------------------------------------------------
void P2InsertSort(SqList &L)
{
    // 2_·��������
    int first, final;
    RedType	*d;
    //d=(RedType*)malloc(L.length*sizeof(RedType)); // ����L.length����¼����ʱ�ռ�
    d = new RedType[L.length];
    d[0] = L.data[1]; // ��L�ĵ�1����¼Ϊd���ź���ļ�¼(��λ��[0])
    first = final = 0; // first��final�ֱ�ָʾd���ź���ļ�¼�ĵ�1�������1����¼��λ��
    for (int i=2; i<=L.length; ++i)
    {
        // ���ν�L�ĵ�2�������1����¼����d��
        if (L.data[i].key<d[first].key)
        {
            // �����¼С��d����Сֵ���嵽d[first]֮ǰ(�����ƶ�d�����Ԫ��)
            first=(first-1+L.length)%L.length; // ��dΪѭ������
            d[first]=L.data[i];
            ++g_sort_assgin_count;
        }
        else
        {
            if (L.data[i].key > d[final].key)
            {
                // �����¼����d�����ֵ���嵽d[final]֮��(�����ƶ�d�����Ԫ��)
                final=final+1;
                d[final]=L.data[i];
                ++g_sort_assgin_count;
            }
            else
            {
                // �����¼����d����Сֵ��С��d�����ֵ���嵽d���м�(��Ҫ�ƶ�d�����Ԫ��)
                int	j;
                j = final++; // �ƶ�d��β��Ԫ���Ա㰴������¼
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
    for (int i=1; i<=L.length; i++) // ��d����L.data
    {
        L.data[i]=d[(i+first-1)%L.length]; // ���Թ�ϵ
        ++g_sort_assgin_count;
    }
    //delete[] d;
}
//---------------------------------------------------------------------------
void HeapBottomUp(RedType H[], int i, int n )//RedType* &H
{
    //����󶥶�
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
            //���������ӽڵ�
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
    //������
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
// ϣ������
void ShellInsert(SqList &L,int dk)
{
    // ��˳���L��һ��ϣ���������򡣱��㷨�Ǻ�һ��ֱ�Ӳ���������ȣ�
    // ���������޸ģ�
    // 1.ǰ���¼λ�õ�������dk,������1;
    // 2.data[0]ֻ���ݴ浥Ԫ,�����ڱ�����j<=0ʱ,����λ�����ҵ���
    int i,j;
    for (i=dk+1; i<=L.length; ++i)
    {
        if ( L.data[i].key < L.data[i-dk].key )
        {
            // �轫L.data[i]�������������ӱ�
            L.data[0]=L.data[i]; // �ݴ���L.data[0]
            for (j=i-dk; j>0 && LT(L.data[0].key,L.data[j].key); j-=dk)
            {
                L.data[j+dk]=L.data[j]; // ��¼���ƣ����Ҳ���λ��
            }
            L.data[j+dk]=L.data[0]; // ����
        }
    }
}
//---------------------------------------------------------------------------


void ShellSort(SqList &L)
{
    // ����������dlta[0..t-1]��˳���L��ϣ������

    int	dlta[3] = {5,3,1}; // ������������
    for (int i=0; i<3; ++i)
    {
        ShellInsert(L,dlta[i]); // һ������Ϊdlta[i]�Ĳ�������
    }
}
//---------------------------------------------------------------------------
bool SequentialFind(const SqList &L, RedType& g_search_data)
{
    //˳�����

    if (L.length < 1)
    {
        std::cerr << "\n	����ʧ�ܣ��ַ�������Ϊ�գ�\n";
        return false;
    }
    for (int i=1; i<L.length; i++)
    {
        g_find_comp_count++;
        if (L.data[i].key == g_search_data.key)
        {
            //��¼��������λ��
            g_search_data.value = i;
            return true;
        }
    }
    return false;
}
//---------------------------------------------------------------------------

bool BinaryFind(const SqList &L,  RedType& g_search_data )
{
    //�۰����
    if (L.length < 1)
    {
        std::cerr << "\n	����ʧ�ܣ��ַ�������Ϊ�գ�\n";
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
    //��ֵ����
    g_find_comp_count++;
    if (L.length < 1)
    {
        std::cerr << "\n	����ʧ�ܣ��ַ�������Ϊ�գ�\n";
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

/// �������� ///
//(radix sort���������ڡ�����ʽ���򡱣�distribution sort�������������ֳơ�Ͱ�ӷ�����bucket sort����bin sort������˼�壬����͸����ֵ�Ĳ�����Ѷ��
// ��Ҫ�����Ԫ�ط�����ĳЩ��Ͱ���У����Դﵽ��������ã����������������ȶ��Ե�������ʱ�临�Ӷ�ΪO (nlog(r)m)��
// ����rΪ����ȡ�Ļ�������mΪ��������ĳЩʱ�򣬻������򷨵�Ч�ʸ��������ıȽ������򷨡�

/// Ч�ʷ���
// ʱ��Ч�ʣ����������Ϊn����¼��d���ؼ��룬�ؼ����ȡֵ��ΧΪradix���������ʽ���������ʱ�临�Ӷ�ΪO(d(n+radix))��
// ���У�һ�˷���ʱ�临�Ӷ�ΪO(n)��һ���ռ�ʱ�临�Ӷ�ΪO(n)��������d�˷�����ռ���

// �ռ�Ч�ʣ���Ҫ2*radix��ָ����еĸ����ռ䣬�Լ����ھ�̬�����n��ָ�롣

/// ʵ�ֵķ���
//���λ����(Most Significant Digit first)�������MSD�����Ȱ�k1������飬ͬһ���м�¼���ؼ���k1��ȣ��ٶԸ��鰴k2����ֳ����飬
//֮�󣬶Ժ���Ĺؼ������������������飬ֱ�������λ�ؼ���kd�Ը�����������ٽ�����������������õ�һ���������С�

//���λ����(Least Significant Digit first)�������LSD�����ȴ�kd��ʼ�����ٶ�kd-1�������������ظ���ֱ����k1������õ�һ���������С�


/// ��������LSD������ʾ ///
int test_distribution_sort()
{
    const unsigned DATA_COUNT = 10;
    int data[DATA_COUNT]= {73,22,93,43,55,14,28,65,39,81};
	int max_data = 93;
    int temp[DATA_COUNT][DATA_COUNT]= {0};
    int order[DATA_COUNT]= {0};

    printf("\n����ǰ: ");
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
        printf("\n��������: ");
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
    printf("\n�����: ");
    for (int i=0; i<10; i++)
        printf("%d ",data[i]);

    putchar('\n');
    return 0;

}

#endif /// __SORT_FIND_H_
