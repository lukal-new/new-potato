
#pragma once
#include<algorithm>/
#include<fstream>
#include<iostream>
#include<cstdlib>
#include<string>
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>

using namespace std;

class Sudoku
{
private:
	char grid[9][9] = { 0 };
	FILE *resultfile1;
	FILE *resultfile2;
	

public:
	int type;
	int num;
	bool isint;
	bool isaddress;
	int argcc;
	Sudoku();
	~Sudoku();
	void solveSudoku(string);
	void createSudoku(int);
	void backtrace(int );
	bool isPlace(int );
	void check(int argc, char* argv[]);
};

