

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
        //δ�������ݴ洢
        os << L.length << endl;
    }
    else
    {
        os << "		������ϢΪ�������ݵ������Ϣ�������£�	\n";
        os << "		�����㷨�� " << g_filename[g_select_sort_algo]
        << "\n		���ݳ��ȣ�" << L.length
        << "\n		�������еĸ�ֵ����:" << g_sort_assgin_count
        << "\n		�������еıȽϴ���:" << g_sort_comp_count
        << "\n		���ֵ��" << L.data[L.length].key << "	��Сֵ��" << L.data[1].key << endl;
        os << endl;
    }


    if (os != cout)
    {
        if (g_select_sort_algo!=0)
        {
            os << "���	" << "��ֵ	" << "�������\n";
        }
        //����ʽ��-1������1������
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
//��ʾϵͳ��ǰʱ��
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
    cout << "		" << "����������" <<date_show;
    cout << "	" << "����ʱ����" <<time<< endl;
}
//---------------------------------------------------------------------------
//�������˵�
void MainMenu()
{
    ClearPrint();
    system("color 02");
    cout << "\n\n\n\n";
    cout << "	������������������������������������������������������\n"
         << "	����ѡ����������Իس�����  0--��ʾ����������Ϣ     ��\n"
         << "	���������������������������Щ�������������������������\n"
         << "	��1--��ʼ������           ��2--����ʽ(Ĭ������)   ��\n"
         << "	��3--ѡ���������򷽷�     ��4--ѡ�����ݲ��ҷ���     ��\n"
         << "	��5--��ӡ������(�ļ�)   ��6--�鿴�������(�ļ�)   ��\n"
         << "	��7--************(*)      ��8--�˳�ϵͳ             ��\n"
         << "	���������������������������ة�������������������������\n";
    PrintNow();
    cout << "	��ѡ����Ҫ�����Ĺ��ܣ�";
}
//---------------------------------------------------------------------------
//
bool LoadData(SqList &L)
{
    ifstream	fin;
    g_select_sort_algo = 0;
    fin.open(g_filename[g_select_sort_algo].c_str());//g_filename[0] = "δ��������.txt";
    if ( fin.fail() )
    {
        return false;
    }

    fin >> L.length;
    g_length = L.length;
    if (!L.data)
    {
        //f�ǿ������ͷ�������ڴ�ռ�
        delete[] L.data;
    }
    L.data = new RedType[g_length+1];//�����ڴ�ռ�
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
    cout << "	������������������������������������������������������������������\n"
         << "	��1--������� 2--�������� 3--�������� 4--��������  0--�������˵���\n"
         << "	������������������������������������������������������������������\n"
         << "	��ѡ����Ҫ��ʼ�����ݵ����ͣ�";
    cin >> ch;
    cin.ignore(100,'\n');
    if (ch == '0')
    {
        return false;
    }

    switch(ch)
    {
    case '0':
        //���á�������
        break;
    case '1':
    {
        cout << "	��������Ҫ��ʼ�����ݵĳ��ȣ�";
        string	str_int;
        cin >> str_int;
        g_length = atol(str_int.c_str());

        if (!L.data)
        {
            //f�ǿ������ͷ�������ڴ�ռ�
            delete[] L.data;
        }
        L.data = new RedType[g_length+1];//�����ڴ�ռ�
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
        cout << "	��������Ҫ��ʼ�����ݵĳ��ȣ�";
        string	str_int;
        cin >> str_int;
        g_length = atol(str_int.c_str());

        if (!L.data)
        {
            //f�ǿ������ͷ�������ڴ�ռ�
            delete[] L.data;
        }
        L.data = new RedType[g_length+1];//�����ڴ�ռ�
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
        cout << "	��������Ҫ��ʼ�����ݵĳ��ȣ�";
        string	str_int;
        cin >> str_int;
        g_length = atol(str_int.c_str());

        if (!L.data)
        {
            //f�ǿ������ͷ�������ڴ�ռ�
            delete[] L.data;
        }
        L.data = new RedType[g_length+1];//�����ڴ�ռ�
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
            cout << "\n\n\n	�������ɹ����������ݣ�����\n";
            g_load_flag = true;
            g_init_flag = true;
            g_select_sort_algo = 0;
        }
        else
        {
            cout << "\n\n\n	�Բ��𣬼�������ʧ�ܣ�����\n";
        }
        break;
    default:
        cout << "	�Բ��������������\n";
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
    cout << "	������������������������������������������������������\n"
         << "	��  1--��������     2--��������     0--�������˵�   ��\n"
         << "	������������������������������������������������������\n"
         << "	��ѡ����Ҫ����ķ�ʽ��";
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
        cout << "	�Բ��������������\n";
        PauseRun();
        SelectSortMode();
    }
}
//---------------------------------------------------------------------------
bool SelectSortAlgo(SqList &L)
{
    ClearPrint();

    cout << "\n\n\n\n";
    cout << "	������������������������������������������������������\n"
         << "	�� ��ѡ����������򷽷���   0--�������˵�           ��\n"
         << "	���������������������������Щ�������������������������\n"
         << "	��1--ð������             ��2--ѡ������             ��\n"
         << "	��3--�ϲ�����             ��4--��������             ��\n"
         << "	��5--ֱ�Ӳ�������         ��6--�۰��������         ��\n"
         << "	��7--��·��������         ��8--������               ��\n"
         << "	��9--ϣ������             ��*--********             ��\n"
         << "	���������������������������ة�������������������������\n"
         << "	��ѡ����Ҫ����ķ�����";

    char	ch;
    cin >> ch;
    cin.ignore(100,'\n');
    //��ʼ������ʱΪ����������Ѿ��ź����򲻱ؽ������򣡣���


    g_sort_assgin_count = 0;//��ʼ����ֵ����
    g_sort_comp_count = 0;//��ʼ���Ƚϴ���

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
        cout << "	�Բ��������������\n";
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
    cout << "	����������������������������������������������������������\n"
         << "	�� 1--˳�����  2--�۰����  3--��ֵ���� 0--�������˵�  ��\n"
         << "	����������������������������������������������������������\n"
         << "	��ѡ����Ҫ���ҵķ�ʽ��";
    char	ch;
    cin >> ch;
    cin.ignore(100,'\n');

    switch(ch)
    {
    case '0':
        //���á�������
        return false;
    case '1':
    {
        cout << "	��������Ҫ���ҵ���ֵ( " << L.data[1].key
             << " ~~ " << L.data[L.length].key << " ) : ";
        string	str_int;
        cin >> str_int;
        g_search_data.key = atoi( str_int.c_str() );
        if ( g_search_data.key< L.data[1].key || g_search_data.key >L.data[L.length].key )
        {
            //��ֵԽ�磬��������
            cout << "	�Բ�������Ĳ�����ֵ����\n";
            PauseRun();
            SearchKey(L);
        }
    }
    search_flag = SequentialFind(L, g_search_data);
    break;
    case '2':
    {
        cout << "	��������Ҫ���ҵ���ֵ( " << L.data[1].key
             << " ~~ " << L.data[L.length].key << " ) : ";
        string	str_int;
        cin >> str_int;
        g_search_data.key = atoi( str_int.c_str() );
        if ( g_search_data.key< L.data[1].key || g_search_data.key >L.data[L.length].key )
        {
            //��ֵԽ�磬��������
            cout << "	�Բ�������Ĳ�����ֵ����\n";
            PauseRun();
            SearchKey(L);
        }
    }

    search_flag = BinaryFind(L, g_search_data);
    break;
    case '3':
    {
        cout << "	��������Ҫ���ҵ���ֵ( " << L.data[1].key
             << " ~~ " << L.data[L.length].key << " ) : ";
        string	str_int;
        cin >> str_int;
        g_search_data.key = atoi( str_int.c_str() );
        if ( g_search_data.key< L.data[1].key || g_search_data.key >L.data[L.length].key )
        {
            //��ֵԽ�磬��������
            cout << "	�Բ�������Ĳ�����ֵ����\n";
            PauseRun();
            SearchKey(L);
        }
    }

    search_flag = InterpolationFind(L, g_search_data);
    break;
    default:
        cout << "	�Բ��������������\n";
        PauseRun();
        SearchKey(L);
    }

    return search_flag;
}
//---------------------------------------------------------------------------
//�����˳�ģʽ����ʾ��
void SayGoodbye()
{
    ClearPrint();
    system("color 74");
    cout << "\n\n\n		       !!! GOODBYE,BYE-BYE !!!		\n";
    getch();
}
//---------------------------------------------------------------------------
//��ʼ���ļ���
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
