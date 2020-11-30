#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

void credits(string&);
void menu(string, int&, int&, double&);
void retrieveStats(ofstream&, ifstream&, string&, int&, int&, double&);
void getUserName(string&);
void validateUserResponse(string&);
int validateUserAnswer(string);
int checkUserAnswer(int, int);
void updateStats(int, int&, int&, double&);
void displayStats(string, int, int, double);
void saveStats(ofstream&, string, int, int, double);
int generateAddition();
int generateSubtraction();
int generateMultiplication();
int generateDivision();

int main()
{
    ofstream outputFile;
	ifstream inputFile;
	int correct = 0, wrong = 0;
	double earning = 0.00;
	string name, continu = "y";

	unsigned seed = time(0);
	srand(seed);

	do
	{
		credits(continu);
		if (continu == "y" || continu == "Y")
		{
			retrieveStats(outputFile, inputFile, name, correct, wrong, earning);
			menu(name, correct, wrong, earning);
			saveStats(outputFile, name, correct, wrong, earning);

			correct = 0;
			wrong = 0;
			earning = 0.00;
		}
	} while (continu == "y" || continu == "Y");
	return 0;
}
