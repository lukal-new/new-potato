#include "Sudoku.h"

void Sudoku::check(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "输入个数不合法" << endl;
	}
	else
	{
		argcc = argc;

		if (strcmp(argv[1], "-c") == 0)
		{
			type = 'c';

			int len = strlen(argv[2]);
			int num = 0;

			for (int i = 0; i < len; i++)
			{
				if (argv[2][i] >= '0'&&argv[2][i] <= '9')
				{

					num = num * 10 + (argv[2][i] - '0');
					//cout << "正在生成"<<num<<"个数独终局" << endl;
				}
				else
				{
					printf("输入不合法，输入数字应在0-9之间\n");
					num = -1;
					isint = false;
					break;

				}

			}
			if (num != -1)
			{
				if (num == 0)
				{
					printf("输入不合法，生成数独个数应大于0\n");
				}
				else if (num > 1000000)
				{
					printf("输入不合法，生成数度个数应小于一百万\n");
				}
				else
				{
					num = num;
			

				}

			}
		}
		else if (strcmp(argv[1], "-s") == 0)
		{
			type = 's';

			errno_t err;
			FILE *tryopen;
			//fopen_s(&tryopen, "a.txt", "w");
			err = fopen_s(&tryopen, argv[2], "r");
			if (err != 0)
			{
				isaddress = false;
				printf("打开文档失败\n");


			}
			else
			{
			}
		}
		else
		{
			cout << "输入不合法" << endl;
		}
	}

}


Sudoku::~Sudoku()
{
}

Sudoku::Sudoku()  //初始化
{
	isint = true;
	isaddress = true;
	argcc = 0;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			grid[i][j] = 0;
}

char matx[200000000] = { 0 };

void Sudoku::createSudoku(int num)
{	
	errno_t err;
	err = fopen_s(&resultfile1, "sudoku.txt", "w");
	if (err != 0)
	{
		printf("创建文档失败\n");

	}

	int count = 0;  //已产生数独个数
	int shift[9] = { 0, 3, 6, 1, 4, 7, 2, 5, 8 };

	for (int i = 0; i < 6; i++)
	{
		if (count >= num)
		{
			//matx[count * 163 - 1] = '\0';
			//cout << "i="<<i << endl;
			break;
		}

		if (i)
		{
			next_permutation(shift + 3, shift + 6);
			//shift[6] = 2, shift[7] = 5, shift[8] = 8;
			//cout <<"sh1"<< shift << endl;
		}
		for (int j = 0; j < 6; j++)
		{
			if (count >= num)
			{
				//cout << "j="<<j << endl;
				break;
			}
				

			if (j)
			{
				next_permutation(shift + 6, shift + 9);
				//cout <<"sh2"<< shift << endl;
			}

			char row[10] = "912345678";
			for (int k = 0; k < 40320; k++)
			{
				if (count >= num)
					break;
				if (k)
				{
					next_permutation(row + 1, row + 9);
					//cout << "sh3" << row << endl;
				}

				int m = 0;
				for (int t = 0; t < 9; t++)
				{
					for (int y = 0; y < 9; y++)
					{
						matx[m + count * 163] = row[(y + shift[t]) % 9];
						matx[m + 1 + count * 163] = ' ';
						//cout<<matx[m + count * 163] << endl;
						m += 2;
					}
					//cout << matx << endl;
					matx[(m - 1) + 163 * count] = '\n';
				}
				matx[162 + 163 * count] = '\n';

				//cout << matx <<"  1"<< endl;
				//cout << m << "  2" << endl;
				count++;
				//cout << count <<"  3"<< endl;
			}
		}
	}
	matx[count * 163 - 1] = '\0';
	fputs(matx, resultfile1);
}





bool Sudoku::isPlace(int count)
{
	int row = count / 9;
	int col = count % 9;
	int j;
	for (j = 0; j < 9; j++)     //同一行
	{
		if (grid[row][j] == grid[row][col] && j != col)
			return false;
	}

	for (j = 0; j < 9; j++)     //同一列
	{
		if (grid[j][col] == grid[row][col] && j != row)
			return false;
	}

	int baseRow = row / 3 * 3;
	int baseCol = col / 3 * 3;
	for (j = baseRow; j < baseRow + 3; j++)
	{
		for (int k = baseCol; k < baseCol + 3; k++)
		{
			if (grid[j][k] == grid[row][col] && (j != row || k != col))
				return false;
		}
	}
	return true;
}

void Sudoku::backtrace(int count)
{
	if (count == 81)
	{
		for (int i = 0; i < 9; ++i)
		{
			fprintf(resultfile2, "%c %c %c %c %c %c %c %c %c\n", grid[i][0], grid[i][1], grid[i][2], grid[i][3], grid[i][4], grid[i][5], grid[i][6], grid[i][7], grid[i][8]);
		}
		fputs("\n", resultfile2);
		return;
	}
	int row = count / 9;  
	int col = count % 9;  
	if (grid[row][col] == '0')
	{
		for (int i = 1; i <= 9; i++)
		{
			grid[row][col] = i + '0';
			if (isPlace(count))
			{
				backtrace(count + 1);
			}

		}
		grid[row][col] = '0';
	}
	else
		backtrace(count + 1);
}

void Sudoku::solveSudoku(string path)
{
	ifstream problemfile(path);

	errno_t err;
	err = fopen_s(&resultfile2, "sudoku.txt", "w+");

	if (problemfile)
	{
		int total = 0;
		string temp[9];
		string str;
		int line = 0;
		bool exc = false;
		while (total < 1000000 && getline(problemfile, str))
		{
			temp[line] = str;
			line++;
			if (line == 9)
			{
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)
					{
						grid[i][j] = temp[i][2 * j];
						if (grid[i][j] < '0' || grid[i][j] > '9')
						{
							exc = true;
							break;
						}
					}
				}
				getline(problemfile, str);
				line = 0;
				if (exc)
				{
					exc = false;
					cout << "存在不合法局面" << endl;
					continue;
				}
				total++;
				// solve sudoku
				long count = 0;
				backtrace(0);
			}
		}
		//resultfile.close();
	}
	else
		cout << "Can't find such file:" << string(path) << endl;
}
