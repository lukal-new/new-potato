	#pragma once

	#include<algorithm>
	#include<fstream>
	#include<iostream>
	#include<cstdlib>
	#include<string>
	#include <SDKDDKVer.h>
	#include <stdio.h>
	#include <tchar.h>
	#include <time.h>

	#include "Sudoku.h"

	using namespace std;


	int main(int argc, char* argv[])
	{
		if (argc != 3)
		{
			cout << "����������Ϸ�" << endl;
		}
		else
		{
			Sudoku M;
			if (strcmp(argv[1], "-c") == 0)
			{
				int len = strlen(argv[2]);
				int num = 0;

				for (int i = 0; i < len; i++)
				{
					if (argv[2][i] >= '0'&&argv[2][i] <= '9')
					{
			
						num = num * 10 + (argv[2][i] - '0');
						//cout << "��������"<<num<<"�������վ�" << endl;
					}
					else
					{
						printf("���벻�Ϸ�����������Ӧ��0-9֮��\n");
						num = -1;
						break;

					}

				}
				if (num != -1)
				{
					clock_t s_time, e_time;
					s_time = clock();
					cout << "��������" << num << "�������վ�" << endl;
					M.createSudoku(num);
					e_time = clock();
					cout << "����ʱ:" << (double)(e_time - s_time) / CLOCKS_PER_SEC << "S" << endl;

				}
			}
			else if (strcmp(argv[1], "-s") == 0)
			{
				errno_t err;
				FILE *tryopen;
				//fopen_s(&tryopen, "a.txt", "w");
				err = fopen_s(&tryopen, argv[2], "r");
				if (err != 0)
				{
					printf("���ĵ�ʧ��\n");

				}
				else
				{
					clock_t s_time, e_time;
					s_time = clock();
					M.solveSudoku(string(argv[2]));
					e_time = clock();
					cout << "����ʱ:" << (double)(e_time - s_time) / CLOCKS_PER_SEC << "S" << endl;
				}
			}
			else
			{
				cout << "���벻�Ϸ�" << endl;
			}
		}
		return 0;
	}

