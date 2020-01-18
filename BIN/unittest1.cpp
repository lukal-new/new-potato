#include "stdafx.h"
#pragma once
#include<algorithm>/
#include<fstream>
#include<iostream>
#include<cstdlib>
#include<string>
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>

#include "CppUnitTest.h"

#include"../Project1/Sudoku.h"
#include"../Project1/Sudoku.cpp"
#include"../Project1/Դ.cpp"




#include<string>

using namespace std;



using namespace Microsoft::VisualStudio::CppUnitTestFramework;



namespace SudokuUnitTest1

{

	TEST_CLASS(UnitTest1)

	{

	public:



		int argc;

		char **argv_c, **argv_s;

		UnitTest1()

		{

			argc = 3;

			argv_c = new char*[3];

			argv_s = new char*[3];



			for (int i = 0; i < 3; i++)

			{

				argv_c[i] = new char[100];

				argv_s[i] = new char[100];

			}



			strcpy_s(argv_c[0], 100, "sudoku.exe");

			strcpy_s(argv_c[1], 100, "-c");

			strcpy_s(argv_c[2], 100, "100");



			strcpy_s(argv_s[0], 100, "sudoku.exe");

			strcpy_s(argv_s[1], 100, "-s");

			strcpy_s(argv_s[2], 100, "C:\\Users\\��Ľ��Ķ�������\Desktop\Project1\Debug\b.txt");

		}





		TEST_METHOD(TestMethod1) //������������Ĳ��ԣ�-c N ����ȷ���룩

		{

			strcpy_s(argv_c[2], 100, "20");
;			
			Sudoku M;

			M.check(argc,argv_c);

			Assert::AreEqual(M.type == 'c', true);

			Assert::AreEqual(M.num == 20, true);



		}

		TEST_METHOD(TestMethod2) //������������Ĳ��ԣ�-s addr ����ȷ���룩

		{

			strcpy_s(argv_c[2], 100, "20");

			Sudoku M;

			M.check(argc, argv_s);

			Assert::AreEqual(M.type == 's', true);

			Assert::AreEqual(M.num == 20, true);

		}

		TEST_METHOD(TestMethod3)//�������������������Ĳ��ԣ�-c ��int��

		{

			strcpy_s(argv_c[2], 100, "asd");

			strcpy_s(argv_c[1], 100, "-c");


			Sudoku M;

			M.check(argc, argv_c);

			Assert::AreEqual(M.isint, true);
	


		}

		TEST_METHOD(TestMethod4)//�������������������Ĳ��ԣ�-s �Ҳ�����ַ��

		{

			strcpy_s(argv_s[2], 100, "C:\\Users\\��Ľ��Ķ�������\Desktop\Project1\Debug\b.txt");

			strcpy_s(argv_s[1], 100, "-s");

			Sudoku  M;

			M.check(argc, argv_s);

			Assert::AreEqual(M.isaddress, true);

		}

		TEST_METHOD(TestMethod5)//�������������������Ĳ��ԣ�-v sff��

		{

			strcpy_s(argv_s[2], 100, "sff");

			strcpy_s(argv_s[1], 100, "-v");

			Sudoku  M;

			M.check(argc, argv_s);

			Assert::AreEqual(M.type == 's', true);

			M.check(argc, argv_c);

			Assert::AreEqual(M.type == 'c', true);

	

		}

		TEST_METHOD(TestMethod6)//�����������������Ĳ���

		{

			argc = 4;

			Sudoku  M;

			M.check(argc, argv_c);

			M.check(argc, argv_s);

			Assert::AreEqual(M.argcc == argc, true);



		}

		TEST_METHOD(TestMethod7)//������������������վָ�������Ĳ��ԣ�-c 10000000��

		{

			strcpy_s(argv_c[2], 100, "10000000");

			strcpy_s(argv_c[1], 100, "-c");

			Sudoku  M;

			M.check(argc, argv_c);

			Assert::AreEqual(M.num==1000000, true);


		}

		TEST_METHOD(TestMethod8)//������������������վָ�������Ĳ��ԣ�-c 0��

		{

			strcpy_s(argv_c[2], 100, "0");

			strcpy_s(argv_c[1], 100, "-c");

			Sudoku  M;

			M.check(argc, argv_c);

			Assert::AreEqual( M.num == 0, true);
	

		}

		TEST_METHOD(TestMethod9)//�����������isplace�������е��������

		{



			char grid[9][9] = { { 9, 5, 8, 3, 5, 7, 1, 2, 4 },

			{ 2, 3, 7, 4, 5, 1, 9, 6, 8 },

			{ 1, 4, 6, 9, 2, 8, 3, 5, 7 },

			{2, 1, 2, 8, 7, 4, 5, 9, 3},

			{5, 7, 3, 6, 1, 9, 4, 8, 2},

			{4, 8, 9, 2, 3, 5, 6, 7, 1},

			{7, 2, 4, 5, 9, 3, 8, 1, 5},

			{8, 9, 1, 7, 4, 6, 2, 3, 5},

			{3, 6, 5, 1, 8, 2, 7, 4, 9}

			};

			//isplace

			int flag = 0;

			int row = 0;

			int col = 4;

			int j;

			for (j = 0; j < 9; j++)     //ͬһ��

			{

				if (grid[row][j] == grid[row][col] && j != col)

				{

					flag = 1;

					break;

				}

			}

			Assert::AreEqual(flag == 1, true);



			row = 3; col = 0; flag = 0;

			for (j = 0; j < 9; j++)     //ͬһ��

			{

				if (grid[j][col] == grid[row][col] && j != row)

				{

					flag = 1;

					break;

				}

			}

			Assert::AreEqual(flag == 1, true);



			row = 6, col = 8; flag = 0;

			int baseRow = row / 3 * 3;

			int baseCol = col / 3 * 3;

			for (j = baseRow; j < baseRow + 3; j++)   //ͬһ��

			{

				for (int k = baseCol; k < baseCol + 3; k++)

				{

					if (grid[j][k] == grid[row][col] && (j != row || k != col))

					{

						flag = 1;

						break;

					}

				}

				if (flag == 1)

					break;

			}

			Assert::AreEqual(flag == 1, true);



		}



		TEST_METHOD(TestMethod10)//�����������isplace�������е���ȷ����

		{

			char grid[9][9] = { { 9, 5, 8, 3, 6, 7, 1, 2, 4 },

			{ 2, 3, 7, 4, 5, 1, 9, 6, 8 },

			{ 1, 4, 6, 9, 2, 8, 3, 5, 7 },

			{ 6, 1, 2, 8, 7, 4, 5, 9, 3 },

			{ 5, 7, 3, 6, 1, 9, 4, 8, 2 },

			{ 4, 8, 9, 2, 3, 5, 6, 7, 1 },

			{ 7, 2, 4, 5, 9, 3, 8, 1, 6 },

			{ 8, 9, 1, 7, 4, 6, 2, 3, 5 },

			{ 3, 6, 5, 1, 8, 2, 7, 4, 9 }

			};

			//isplace

			int flag = 0;

			int row = 0;

			int col = 4;

			int j;

			for (j = 0; j < 9; j++)     //ͬһ��

			{

				if (grid[row][j] == grid[row][col] && j != col)

				{

					flag = 1;

					break;

				}

			}

			for (j = 0; j < 9; j++)     //ͬһ��

			{

				if (grid[j][col] == grid[row][col] && j != row)

				{

					flag = 1;

					break;

				}

			}

			int baseRow = row / 3 * 3;

			int baseCol = col / 3 * 3;

			for (j = baseRow; j < baseRow + 3; j++)   //ͬһ��

			{

				for (int k = baseCol; k < baseCol + 3; k++)

				{

					if (grid[j][k] == grid[row][col] && (j != row || k != col))

					{

						flag = 1;

						break;

					}

				}

				if (flag == 1)

					break;

			}

			Assert::AreEqual(flag == 0, true);



		}

		TEST_METHOD(TestMethod11)//�����������վ��е�ȫ���к������

		{

			int x;

			int a[9] = { 1,2,3,4,5,6,7,8,9 };

			int flag = 0;

			next_permutation(a, a + 9);

			int b[9] = { 1,2,3,4,5,6,7,9,8 };

			for (int i = 0; i < 9; i++)

				if (a[i] != b[i])

				{

					flag = 1;

					break;

				}

			Assert::AreEqual(flag == 0, true);

		}



	};

}