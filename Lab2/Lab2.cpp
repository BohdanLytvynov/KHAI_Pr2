// Lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<windows.h>
#include<conio.h>
#include<vector>
#include<string>


using namespace std;

#pragma region Pointers to functions

#pragma region Initialization

bool (*Init) (HANDLE);

#pragma endregion

#pragma region Console Size

const int& (*GetConsoleWidth)();

const int& (*GetConsoleHeight)();

#pragma endregion

#pragma region ConsoleCursor

short (*GetCursorPositionX)();

short (*GetCursorPositionY)();

void (*SetCursorPosition)(short x, short y);

#pragma endregion

#pragma region Console Color

void (*SetDefColor) (WORD&);

WORD* (*GetDefColor) (void);

#pragma endregion

#pragma region Print
void (*Print) (const string&);

void (*PrintColorMessage) (const string&, WORD);

void (*PrintAtCenter)(const string& msg, short yoffset);

void (*PrintColorMsgAtCenter)(const string& msg, WORD color, short yoffset);

#pragma endregion

#pragma region Input

HANDLE* (*GetHandle)(void);

string(*Input) (const string&, WORD, bool (*) (const string&));

char (*InputKey) (const string&, WORD);

#pragma endregion

#pragma region Console Graphics

void (*DrawRect)(int x, int y, int width,
	int height,
	WORD BorderColor, WORD Fill);

void (*DrawTextBlock)(const unsigned short x, const unsigned short y,
	const unsigned short width,
	const unsigned short height,
	WORD BorderColor, WORD Fill, const string& text,
	WORD Foreground, vector<unsigned short> padding, bool Wrapping);

#pragma endregion

#pragma endregion

#pragma region Checking Values

bool CheckNumber(const string& str)
{
	for (auto c : str)
	{
		if (!isdigit(c))
			return false;
	}

	if (stoi(str) <= 0)
	{
		return false;
	}

	return true;
}

#pragma endregion



int main()
{
	WORD white = FOREGROUND_RED | FOREGROUND_GREEN |
		FOREGROUND_BLUE | FOREGROUND_INTENSITY;

#pragma region Load_Library for Console Fumctions

	auto ConsoleLib = LoadLibrary(L"../libs/ConsoleLib.dll");

#pragma endregion

#pragma region Get functions from Lib

	DrawTextBlock = (decltype(DrawTextBlock))GetProcAddress(ConsoleLib, "DrawTextBlock");

	DrawRect = (decltype(DrawRect))GetProcAddress(ConsoleLib, "DrawRect");

	PrintAtCenter = (decltype(PrintAtCenter))GetProcAddress(ConsoleLib, "PrintAtCenter");

	PrintColorMsgAtCenter = (decltype(PrintColorMsgAtCenter))GetProcAddress(ConsoleLib, "PrintColorMsgAtCenter");

	GetCursorPositionX = (decltype(GetCursorPositionX))GetProcAddress(ConsoleLib, "GetCursorPositionX");

	GetCursorPositionY = (decltype(GetCursorPositionY))GetProcAddress(ConsoleLib, "GetCursorPositionY");

	SetCursorPosition = (decltype(SetCursorPosition))GetProcAddress(ConsoleLib, "SetCursorPosition");

	GetConsoleWidth = (decltype(GetConsoleWidth))GetProcAddress(ConsoleLib, "GetConsoleWidth");

	GetConsoleHeight = (decltype(GetConsoleHeight))GetProcAddress(ConsoleLib, "GetConsoleHeight");

	Init = (bool (*) (HANDLE))GetProcAddress(ConsoleLib, "Init");

	SetDefColor = (decltype(SetDefColor))GetProcAddress(ConsoleLib, "SetDefaultColor");

	GetDefColor = (decltype(GetDefColor))GetProcAddress(ConsoleLib, "GetDefaultColor");

	Print = (void (*) (const string&))GetProcAddress(ConsoleLib, "Print");

	PrintColorMessage = (decltype(PrintColorMessage))GetProcAddress(ConsoleLib, "PrintColorMsg");

	GetHandle = (decltype(GetHandle))GetProcAddress(ConsoleLib, "GetHandle");

	Input = (decltype(Input))GetProcAddress(ConsoleLib, "Input");

	InputKey = (decltype(InputKey))GetProcAddress(ConsoleLib, "InputKey");

#pragma endregion




#pragma region Main Codde

	if (Init(GetStdHandle(STD_OUTPUT_HANDLE)))
	{
		do
		{
			system("CLS");

			SetCursorPosition(0, 0);

			SetDefColor(white);

			unsigned short x = stoi(Input("Enter x Coord:", FOREGROUND_GREEN, CheckNumber));

			unsigned short y = stoi(Input("Enter y Coord:", FOREGROUND_GREEN, CheckNumber));

			unsigned short width = stoi(Input("Enter width:", FOREGROUND_GREEN, CheckNumber));

			unsigned short height = stoi(Input("Enter height:", FOREGROUND_GREEN, CheckNumber));
		
			string txt = "Lytvynov Bohdan Yuriyevich Group 115";

			vector<unsigned short> relTxtPos = { 4, (unsigned short)(height/2 - 1) };

			system("CLS");

			DrawTextBlock(x, y, width, height, (BACKGROUND_RED | BACKGROUND_GREEN) |
				(FOREGROUND_BLUE), BACKGROUND_BLUE, txt, 
				0 | (FOREGROUND_RED | FOREGROUND_GREEN |
					FOREGROUND_BLUE | FOREGROUND_INTENSITY), 
				relTxtPos, false);

			SetCursorPosition(0, height + 5);

		} while (InputKey("Press Q to quite or press any key to continue:", white) != 'q');
	}

#pragma endregion


	FreeLibrary(ConsoleLib);
}


