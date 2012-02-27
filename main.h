

#ifndef __MAIN_H_
#define __MAIN_H_

#include "sort_find.h"

//---------------------------------------------------------------------------
void PauseRun()
{
    system("pause");
}

void ClearPrint()
{
    system("cls");
}

bool PrintData(const SqList& L, ostream& os)
{
    bool g_sorted_flag = false;

    if (g_select_sort_algo == 0)
    {
        //未排序数据存储
        os << L.length << endl;
    }
    else
    {
        os << "		以下信息为排序数据的相关信息：（如下）	\n";
        os << "		排序算法： " << g_filename[g_select_sort_algo]
        << "\n		数据长度：" << L.length
        << "\n		程序运行的赋值次数:" << g_sort_assgin_count
        << "\n		程序运行的比较次数:" << g_sort_comp_count
        << "\n		最大值：" << L.data[L.length].key << "	最小值：" << L.data[1].key << endl;
        os << endl;
    }


    if (os != cout)
    {
        if (g_select_sort_algo!=0)
        {
            os << "编号	" << "数值	" << "产生序号\n";
        }
        //排序方式：-1，降序；1，升序；
        if (g_sort_mode == 1)
        {
            for (int i=1; i<=L.length; i++)
                os << i << "	" <<L.data[i].key << "	" << L.data[i].value << "\n";
        }
        else
        {
            for (int i=L.length; i>=1; i--)
                os << L.length-i+1 << "	" <<L.data[i].key << "	" << L.data[i].value << "\n";
        }
        g_sorted_flag = true;
    }



    return g_sorted_flag;
}

//---------------------------------------------------------------------------
//显示系统当前时间
void PrintNow()
{
    char date[9];
    char date_show[11];
    char time[9];
    _strdate(date);
    _strtime(time);
    date_show[0]='2';
    date_show[1]='0';
    date_show[2]=date[6];
    date_show[3]=date[7];
    date_show[4]='-',date_show[5]=date[0],date_show[6]=date[1];
    date_show[7]='-',date_show[8]=date[3],date_show[9]=date[4],date_show[10]='\0';
    cout << "		" << "现在日期是" <<date_show;
    cout << "	" << "现在时间是" <<time<< endl;
}
//---------------------------------------------------------------------------
//程序主菜单
void MainMenu()
{
    ClearPrint();
    system("color 02");
    cout << "\n\n\n\n";
    cout << "	┌─────────────────────────┐\n"
         << "	│请选择操作功能以回车结束  0--显示排序数据信息     │\n"
         << "	├────────────┬────────────┤\n"
         << "	│1--初始化数据           │2--排序方式(默认升序)   │\n"
         << "	│3--选择数据排序方法     │4--选择数据查找方法     │\n"
         << "	│5--打印排序结果(文件)   │6--查看结果数据(文件)   │\n"
         << "	│7--************(*)      │8--退出系统             │\n"
         << "	└────────────┴────────────┘\n";
    PrintNow();
    cout << "	请选择你要操作的功能：";
}
//---------------------------------------------------------------------------
//
bool LoadData(SqList &L)
{
    ifstream	fin;
    g_select_sort_algo = 0;
    fin.open(g_filename[g_select_sort_algo].c_str());//g_filename[0] = "未排序数据.txt";
    if ( fin.fail() )
    {
        return false;
    }

    fin >> L.length;
    g_length = L.length;
    if (!L.data)
    {
        //f非空则先释放申请的内存空间
        delete[] L.data;
    }
    L.data = new RedType[g_length+1];//申请内存空间
    int pass;
    for (int	i=1; i<=g_length; i++)
    {
        fin >> L.data[i].value >> L.data[i].key >> pass ;
    }
    return true;

}
//---------------------------------------------------------------------------
bool InitData(SqList &L)
{
    char	ch;
    ClearPrint();
    cout << "\n\n\n\n";
    cout << "	┌───────────────────────────────┐\n"
         << "	│1--随机数据 2--逆序数据 3--升序数据 4--加载数据  0--返回主菜单│\n"
         << "	└───────────────────────────────┘\n"
         << "	请选择你要初始化数据的类型：";
    cin >> ch;
    cin.ignore(100,'\n');
    if (ch == '0')
    {
        return false;
    }

    switch(ch)
    {
    case '0':
        //闲置、、、、
        break;
    case '1':
    {
        cout << "	请输入你要初始化数据的长度：";
        string	str_int;
        cin >> str_int;
        g_length = atol(str_int.c_str());

        if (!L.data)
        {
            //f非空则先释放申请的内存空间
            delete[] L.data;
        }
        L.data = new RedType[g_length+1];//申请内存空间
        L.length = g_length;

        for (int	i=1; i<=g_length; i++)
        {
            L.data[i].key = rand();
            L.data[i].value = i;
        }
    }
    g_init_data_mode = 0;
    break;
    case '2':
    {
        cout << "	请输入你要初始化数据的长度：";
        string	str_int;
        cin >> str_int;
        g_length = atol(str_int.c_str());

        if (!L.data)
        {
            //f非空则先释放申请的内存空间
            delete[] L.data;
        }
        L.data = new RedType[g_length+1];//申请内存空间
        L.length = g_length;

        for (int	i=1; i<=g_length; i++)
        {
            L.data[i].key = g_length-i+1;
            L.data[i].value = i;
        }
    }
    g_init_data_mode = -1;
    break;
    case '3':
    {
        cout << "	请输入你要初始化数据的长度：";
        string	str_int;
        cin >> str_int;
        g_length = atol(str_int.c_str());

        if (!L.data)
        {
            //f非空则先释放申请的内存空间
            delete[] L.data;
        }
        L.data = new RedType[g_length+1];//申请内存空间
        L.length = g_length;
        for (int	i=1; i<=g_length; i++)
        {
            L.data[i].key = i;
            L.data[i].value = i;
        }
    }
    g_init_data_mode = 1;
    break;
    case '4':
        if ( LoadData(L) )
        {
            cout << "\n\n\n	！！！成功，加载数据！！！\n";
            g_load_flag = true;
            g_init_flag = true;
            g_select_sort_algo = 0;
        }
        else
        {
            cout << "\n\n\n	对不起，加载数据失败！！！\n";
        }
        break;
    default:
        cout << "	对不起，你的输入有误！\n";
        PauseRun();
        InitData(L);
    }
    return true;
}
//---------------------------------------------------------------------------
void SelectSortMode()
{
    ClearPrint();
    cout << "\n\n\n\n";
    cout << "	┌─────────────────────────┐\n"
         << "	│  1--升序排序     2--降序排序     0--返回主菜单   │\n"
         << "	└─────────────────────────┘\n"
         << "	请选择你要排序的方式：";
    char	ch;
    cin >> ch;
    cin.ignore(100,'\n');
    switch(ch)
    {
    case '0':
        break;
    case '1':
        g_sort_mode = 1;
        break;
    case '2':
        g_sort_mode =-1;
        break;

    default:
        cout << "	对不起，你的输入有误！\n";
        PauseRun();
        SelectSortMode();
    }
}
//---------------------------------------------------------------------------
bool SelectSortAlgo(SqList &L)
{
    ClearPrint();

    cout << "\n\n\n\n";
    cout << "	┌─────────────────────────┐\n"
         << "	│ 请选择操以下排序方法：   0--返回主菜单           │\n"
         << "	├────────────┬────────────┤\n"
         << "	│1--冒泡排序             │2--选择排序             │\n"
         << "	│3--合并排序             │4--快速排序             │\n"
         << "	│5--直接插入排序         │6--折半插入排序         │\n"
         << "	│7--二路插入排序         │8--堆排序               │\n"
         << "	│9--希尔排序             │*--********             │\n"
         << "	└────────────┴────────────┘\n"
         << "	请选择你要排序的方法：";

    char	ch;
    cin >> ch;
    cin.ignore(100,'\n');
    //初始化数据时为升序或数据已经排好序，则不必进行排序！！！


    g_sort_assgin_count = 0;//初始化赋值次数
    g_sort_comp_count = 0;//初始化比较次数

    switch(ch)
    {
    case '0':
        return false;
        break;
    case '1':
        BubbleSort(L);
        g_select_sort_algo = 1;
        break;
    case '2':
        SelectSort(L);
        g_select_sort_algo = 2;
        break;
    case '3':
        MergeSort(L);
        g_select_sort_algo = 3;
        break;
    case '4':
        QuickSort(L);
        g_select_sort_algo = 4;
        break;
    case '5':
        g_select_sort_algo = 5;
        InsertSort(L);
        break;
    case '6':
        g_select_sort_algo = 6;
        BInsertSort(L);
        break;
    case '7':
        g_select_sort_algo = 7;
        P2InsertSort(L);
        break;
    case '8':
        g_select_sort_algo = 8;
        HeapSort(L);
        break;
    case '9':
        g_select_sort_algo = 9;
        ShellSort(L);
        break;
    default:
        cout << "	对不起，你的输入有误！\n";
        PauseRun();
        SelectSortAlgo(L);
    }
    return true;
}
//---------------------------------------------------------------------------
bool SearchKey( const SqList &L)
{
    bool search_flag = false;
    ClearPrint();
    cout << "\n\n\n\n";
    cout << "	┌───────────────────────────┐\n"
         << "	│ 1--顺序查找  2--折半查找  3--插值查找 0--返回主菜单  │\n"
         << "	└───────────────────────────┘\n"
         << "	请选择你要查找的方式：";
    char	ch;
    cin >> ch;
    cin.ignore(100,'\n');

    switch(ch)
    {
    case '0':
        //闲置。。。。
        return false;
    case '1':
    {
        cout << "	请输入你要查找的数值( " << L.data[1].key
             << " ~~ " << L.data[L.length].key << " ) : ";
        string	str_int;
        cin >> str_int;
        g_search_data.key = atoi( str_int.c_str() );
        if ( g_search_data.key< L.data[1].key || g_search_data.key >L.data[L.length].key )
        {
            //数值越界，输入有误
            cout << "	对不起，输入的查找数值有误！\n";
            PauseRun();
            SearchKey(L);
        }
    }
    search_flag = SequentialFind(L, g_search_data);
    break;
    case '2':
    {
        cout << "	请输入你要查找的数值( " << L.data[1].key
             << " ~~ " << L.data[L.length].key << " ) : ";
        string	str_int;
        cin >> str_int;
        g_search_data.key = atoi( str_int.c_str() );
        if ( g_search_data.key< L.data[1].key || g_search_data.key >L.data[L.length].key )
        {
            //数值越界，输入有误
            cout << "	对不起，输入的查找数值有误！\n";
            PauseRun();
            SearchKey(L);
        }
    }

    search_flag = BinaryFind(L, g_search_data);
    break;
    case '3':
    {
        cout << "	请输入你要查找的数值( " << L.data[1].key
             << " ~~ " << L.data[L.length].key << " ) : ";
        string	str_int;
        cin >> str_int;
        g_search_data.key = atoi( str_int.c_str() );
        if ( g_search_data.key< L.data[1].key || g_search_data.key >L.data[L.length].key )
        {
            //数值越界，输入有误
            cout << "	对不起，输入的查找数值有误！\n";
            PauseRun();
            SearchKey(L);
        }
    }

    search_flag = InterpolationFind(L, g_search_data);
    break;
    default:
        cout << "	对不起，你的输入有误！\n";
        PauseRun();
        SearchKey(L);
    }

    return search_flag;
}
//---------------------------------------------------------------------------
//程序退出模式（提示）
void SayGoodbye()
{
    ClearPrint();
    system("color 74");
    cout << "\n\n\n		       !!! GOODBYE,BYE-BYE !!!		\n";
    getch();
}
//---------------------------------------------------------------------------
//初始化文件名
void InitFliename()
{
    g_filename[0] = "unsorted_data.txt";
    g_filename[1] = "bubble_sort_data.txt";
    g_filename[2] = "select_sort_data.txt";
    g_filename[3] = "merge_sort_data.txt";
    g_filename[4] = "quick_sort_data.txt";
    g_filename[5] = "direct_insert_sort_data.txt";
    g_filename[6] = "binary_insert_sort_data.txt";
    g_filename[7] = "2-insert_sort_data.txt";
    g_filename[8] = "heap_sort_data.txt";
    g_filename[9] = "shell_sort_data.txt";
}

//---------------------------------------------------------------------------
#endif ///__MAIN_H_
