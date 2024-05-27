#include <windows.h>

#ifdef WIN32
HANDLE cHandle = GetStdHandle(
	STD_OUTPUT_HANDLE);
void SetConsoleColor(int color) {
	SetConsoleTextAttribute(cHandle, color);
}
#endif

#define SHOW_COMPRESSION_STATUS_PAK
#ifdef WIN32
#define SETCONSOLECOLOR SetConsoleColor
#endif

#include "../../msfldev/msfldev/pak.h"
#include "../../msfldev/msfldev/balloon.hpp"
#include <iostream>

#define CONSOLE_COLOR_DBLUE 1
#define CONSOLE_COLOR_DGREEN 2
#define CONSOLE_COLOR_DCYAN 3
#define CONSOLE_COLOR_DRED 4
#define CONSOLE_COLOR_DMAGENTA 5
#define CONSOLE_COLOR_DYELLOW 6
#define CONSOLE_COLOR_GRAY 7
#define CONSOLE_COLOR_DGRAY 8
#define CONSOLE_COLOR_BLUE 9
#define CONSOLE_COLOR_GREEN 10 
#define CONSOLE_COLOR_CYAN 11
#define CONSOLE_COLOR_RED 12
#define CONSOLE_COLOR_MAGENTA 13
#define CONSOLE_COLOR_YELLOW 14
#define CONSOLE_COLOR_WHITE 15

enum MenuOptions {
	null_opt,
	PakDirectory,
	DecodePak,
	Exit
};

void processOption(int opt) {
#ifdef WIN32
	SetConsoleColor(CONSOLE_COLOR_YELLOW);
#endif
	switch (opt) {
		case PakDirectory: {
			std::cout << "Enter Directory to pak [include backslash at end]: ";
			std::string dir;
			std::getline(std::cin, dir);
			std::cout << "Enter Output directory [include backslash at end]: ";
			std::string out;
			std::getline(std::cin, out);
			std::cout << "Enter Output File Name: ";
			std::string outfName;
			std::getline(std::cin, outfName);
			out = out + outfName + ".pak";
			std::cout << "Enter compression level [0-2] (2 is default): ";
			std::string clevelstr;
			std::getline(std::cin, clevelstr);
			int compressionLevel = 2;
			try {
				compressionLevel = std::stoi(clevelstr);
			}
			catch (std::exception e) {};
#ifdef WIN32
			SetConsoleColor(CONSOLE_COLOR_MAGENTA);
#endif
			std::cout << "Paking File..." << std::endl;
			int err_code = 0;
#ifdef WIN32
			SetConsoleColor(CONSOLE_COLOR_CYAN);
#endif
			//std::cout << "G: " << (int)(compressionLevel > 2) << " " << 2 << std::endl;
			if (err_code=pak::PakFilesInDirectory(dir, out, (int)(compressionLevel > 0), compressionLevel) != 0) {
#ifdef WIN32
				SetConsoleColor(CONSOLE_COLOR_RED);
#endif
				std::cout << "Error failed to pack directory! Error Code: " << err_code << std::endl;
			} else 
#ifdef WIN32
				SetConsoleColor(CONSOLE_COLOR_GREEN);
#endif
			std::cout << "Successfully paked file!" << std::endl;
			break;
		}
		case DecodePak: {
			std::cout << "Enter Directory to unpak [include backslash at end]: ";
			std::string dir;
			std::getline(std::cin, dir);
			std::cout << "Enter Output directory [include backslash at end]: ";
			std::string out;
			std::getline(std::cin, out);
			int err_code = 0;
#ifdef WIN32
			SetConsoleColor(CONSOLE_COLOR_MAGENTA);
#endif
			std::cout << "Unpacking File..." << std::endl;
#ifdef WIN32
			SetConsoleColor(CONSOLE_COLOR_CYAN);
#endif
			if (err_code = pak::ExtractContentsToDisk(dir, out)) {
#ifdef WIN32
				SetConsoleColor(CONSOLE_COLOR_DRED);
#endif
				std::cout << "Error failed to unpack directory! Error Code: " << err_code << std::endl;
			}
			else {
#ifdef WIN32
				SetConsoleColor(CONSOLE_COLOR_GREEN);
#endif
				std::cout << "Successfully unpaked file!" << std::endl;
			}

			break;
		}
	}
}

int main() {
	int option = null_opt;

#ifdef WIN32
	SetConsoleColor(CONSOLE_COLOR_DGRAY);
#endif
	std::cout << "Copyright muffinshades 2024 (c)" << std::endl;

	while (option != Exit) {
#ifdef WIN32
		SetConsoleColor(CONSOLE_COLOR_WHITE);
#endif
		std::cout << "----Pak Utility----" << std::endl;
		std::cout << "1. Pak Directory \n2. Unpack pak" << std::endl;
#ifdef WIN32
		SetConsoleColor(CONSOLE_COLOR_RED);
#endif
		std::cout << "3. Exit" << std::endl;
#ifdef WIN32
		SetConsoleColor(CONSOLE_COLOR_WHITE);
#endif
		std::cout << "-------------------" << std::endl;
#ifdef WIN32
		SetConsoleColor(CONSOLE_COLOR_BLUE);
#endif
		std::cout << "Enter Option: ";
		option = null_opt;
		while (option == null_opt) {
			std::string strOption;
			std::getline(std::cin, strOption);

			try {
				option = std::stoi(strOption);
			}
			catch (std::exception e) {
				continue;
			}
		}

		processOption(option);
	}
}