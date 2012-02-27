

#include "stdafx.h"
#include "sort_find.h"
#include "main.h"


//---------------------------------------------------------------------------
int main()
{
    time_t t;
    srand((unsigned) time(&t));//rand()

    InitFliename();//初始化文件名

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
                cout << "\n\n\n	对不起，数据还未初始化或未排序！！！\n";
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
                cout << "\n\n\n	对不起，数据还未初始化！！！\n";
                break;
            }
            if (g_init_data_mode == 1||g_sorted_flag == 1)
            {
                cout << "\n	当前数据为有序序列！！！\n";
                break;
            }
            if (SelectSortAlgo(L))
            {
                g_sorted_flag = true;
                g_savefile_flag = false;
            }
            break;
        case '4':
            g_find_comp_count = 0;//初始化查找次数

            if ( g_sorted_flag == false || g_init_flag == false )
            {
                cout << "\n\n\n	对不起，数据还未初始化或未排序！！！\n";
                break;
            }
            else
            {
                if (SearchKey(L))
                {
                    cout << "\n\n\n	！！！查找成功！！！\n";
                    cout <<	"	查找键值：" << g_search_data.key
                         << ", 位置：" << g_search_data.value
                         << ",  查找比较次数: " << g_find_comp_count << endl;
                }
                else
                {
                    cout << "\n\n\n	对不起，查找失败！！！\n";
                }
            }

            break;
        case '5':
            if (g_init_flag == false)//g_sorted_flag == false||或未排序
            {
                cout << "\n\n\n	对不起，数据还未初始化！！！\n";
            }
            else
            {
                ofstream	out_stream;
                out_stream.open(g_filename[g_select_sort_algo].c_str());//
                PrintData(L,out_stream);
                out_stream.close();
                g_savefile_flag = true;
                cout << "\n\n	！！！成功，打印排序结果到指定文件！！！";
            }

            break;
        case '6':
            if (g_init_flag == false||g_savefile_flag == false)
            {
                cout << "\n\n\n	对不起，数据还未初始化或未保存文件！！！\n";
            }
            else
            {
                cout << "\n\n\n\n	请查看排序数据结果，关闭文档后继续操作、、、\n	";
                system( g_filename[g_select_sort_algo].c_str() );
            }

            break;
        case '7':

            break;
        case '8':
            if (g_savefile_flag == false && g_init_data_mode!=-1)
            {
                //数据为初始化且数据未保存文件
                cout << "\n	退出系统之前是否保存当前数据信息Y(y): ";
                cin >> c;
                cin.ignore(100,'\n');

                if (c == 'y'||c == 'Y')
                {
                    ofstream	fout;
                    fout.open(g_filename[g_select_sort_algo].c_str());//

                    if ( PrintData(L, fout) )
                        cout << "\n\n\n		！！！保存成功！！！！\n";
                    else
                        cout << "\n\n\n		对不起，保存失败！\n";

                    fout.close();
                }
                g_savefile_flag = true;
            }
            cout << "\n你是否真的要退出系统，请按Y(y)确认退出,其他任意键则退回： ";
            cin >> c;
            cin.ignore(100,'\n');
            if (c == 'y'||c == 'Y')
            {
                SayGoodbye();
                if (g_init_flag == true)
                    delete[] L.data;//释放申请内存空间
                return 0;
            }
            break;

        default:
            cout << " \n\n\n\n	您的输入有误，请重新输入选择 !\n	";

        }
        cout << "\n		";
        PauseRun();

    }
    while (true);
    return 0;
}

//---------------------------------------------------------------------------

