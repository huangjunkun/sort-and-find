

#include "stdafx.h"
#include "sort_find.h"
#include "main.h"


//---------------------------------------------------------------------------
int main()
{
    time_t t;
    srand((unsigned) time(&t));//rand()

    InitFliename();//��ʼ���ļ���

    SqList L;
    L.length = 0;

    do
    {
        char	c;
        MainMenu();
        cin >> c;
        cin.ignore(100,'\n');
        ClearPrint();
        switch (c)
        {
        case '0':
            if (g_sorted_flag == true && g_init_flag == true)
            {
                cout << "\n\n\n";
                PrintData(L,cout);
            }
            else
            {
                cout << "\n\n\n	�Բ������ݻ�δ��ʼ����δ���򣡣���\n";
            }
            break;
        case '1':
            if (InitData(L))
            {
                g_sorted_flag = false;
                g_savefile_flag = false;
                g_init_flag = true;
                g_select_sort_algo = 0;
            }
            //Print(L,cout);
            break;
        case '2':
            SelectSortMode();
            break;
        case '3':
            if (L.length == 0)
            {
                cout << "\n\n\n	�Բ������ݻ�δ��ʼ��������\n";
                break;
            }
            if (g_init_data_mode == 1||g_sorted_flag == 1)
            {
                cout << "\n	��ǰ����Ϊ�������У�����\n";
                break;
            }
            if (SelectSortAlgo(L))
            {
                g_sorted_flag = true;
                g_savefile_flag = false;
            }
            break;
        case '4':
            g_find_comp_count = 0;//��ʼ�����Ҵ���

            if ( g_sorted_flag == false || g_init_flag == false )
            {
                cout << "\n\n\n	�Բ������ݻ�δ��ʼ����δ���򣡣���\n";
                break;
            }
            else
            {
                if (SearchKey(L))
                {
                    cout << "\n\n\n	���������ҳɹ�������\n";
                    cout <<	"	���Ҽ�ֵ��" << g_search_data.key
                         << ", λ�ã�" << g_search_data.value
                         << ",  ���ұȽϴ���: " << g_find_comp_count << endl;
                }
                else
                {
                    cout << "\n\n\n	�Բ��𣬲���ʧ�ܣ�����\n";
                }
            }

            break;
        case '5':
            if (g_init_flag == false)//g_sorted_flag == false||��δ����
            {
                cout << "\n\n\n	�Բ������ݻ�δ��ʼ��������\n";
            }
            else
            {
                ofstream	out_stream;
                out_stream.open(g_filename[g_select_sort_algo].c_str());//
                PrintData(L,out_stream);
                out_stream.close();
                g_savefile_flag = true;
                cout << "\n\n	�������ɹ�����ӡ��������ָ���ļ�������";
            }

            break;
        case '6':
            if (g_init_flag == false||g_savefile_flag == false)
            {
                cout << "\n\n\n	�Բ������ݻ�δ��ʼ����δ�����ļ�������\n";
            }
            else
            {
                cout << "\n\n\n\n	��鿴�������ݽ�����ر��ĵ����������������\n	";
                system( g_filename[g_select_sort_algo].c_str() );
            }

            break;
        case '7':

            break;
        case '8':
            if (g_savefile_flag == false && g_init_data_mode!=-1)
            {
                //����Ϊ��ʼ��������δ�����ļ�
                cout << "\n	�˳�ϵͳ֮ǰ�Ƿ񱣴浱ǰ������ϢY(y): ";
                cin >> c;
                cin.ignore(100,'\n');

                if (c == 'y'||c == 'Y')
                {
                    ofstream	fout;
                    fout.open(g_filename[g_select_sort_algo].c_str());//

                    if ( PrintData(L, fout) )
                        cout << "\n\n\n		����������ɹ���������\n";
                    else
                        cout << "\n\n\n		�Բ��𣬱���ʧ�ܣ�\n";

                    fout.close();
                }
                g_savefile_flag = true;
            }
            cout << "\n���Ƿ����Ҫ�˳�ϵͳ���밴Y(y)ȷ���˳�,������������˻أ� ";
            cin >> c;
            cin.ignore(100,'\n');
            if (c == 'y'||c == 'Y')
            {
                SayGoodbye();
                if (g_init_flag == true)
                    delete[] L.data;//�ͷ������ڴ�ռ�
                return 0;
            }
            break;

        default:
            cout << " \n\n\n\n	����������������������ѡ�� !\n	";

        }
        cout << "\n		";
        PauseRun();

    }
    while (true);
    return 0;
}

//---------------------------------------------------------------------------

