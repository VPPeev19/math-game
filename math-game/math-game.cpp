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

void credits(string& continu)
{
	cout << "*-------------------------------------*" << endl;
	cout << ":            The Math Game            :" << endl;
	cout << ":          by Team FullHouse             :" << endl;
	cout << ":    (Todor,Stanimir,Andrei,Valentin)           :" << endl;
	cout << "*-------------------------------------*" << endl;
	cout << ":                                     :" << endl;
	cout << ":                                     :" << endl;
	cout << ":         Press y/Y to play.          :" << endl;
	cout << ":         Press anything else         :" << endl;
	cout << ":        to exit the program.         :" << endl;
	cout << ":                                     :" << endl;
	cout << ":                                     :" << endl;
	cout << "*-------------------------------------*" << endl;
	getline(cin, continu);
}

void retrieveStats(ofstream& outputFile, ifstream& inputFile, string& name, int& correct, int& wrong, double& earning)
{
	string userName;

	getUserName(userName);

	name = userName;
	userName += ".txt";

	inputFile.open(userName.c_str());

	if (inputFile.is_open())
	{
		inputFile >> name;
		inputFile >> correct;
		inputFile >> wrong;
		inputFile >> earning;
		inputFile.close();

		system("cls");
		cout << "*-------------------------------------*" << endl;
		cout << ":       Welcome back! " << left << setw(10) << name << "      :" << endl;
		cout << ":                                     :" << endl;
	}
	else
	{
		system("cls");
		cout << "*-------------------------------------*" << endl;
		cout << ":      Welcome to the Math Game!      :" << endl;
		cout << ":              " << left << setw(10) << name << "             :" << endl;
	}
}

void menu(string name, int& correct, int& wrong, double& earning)
{
	string select, answer;
	int correctAnswer, answerNum, rightOrWrong = 0;

	do
	{
		cout << "*-------------------------------------*" << endl;
		cout << ":              Game Menu              :" << endl;
		cout << ":    (1) Addition                     :" << endl;
		cout << ":    (2) Subtraction                  :" << endl;
		cout << ":    (3) Multiplication               :" << endl;
		cout << ":    (4) Division                     :" << endl;
		cout << ":    (5) Current statistic            :" << endl;
		cout << ":    (N) Save and return to home      :" << endl;
		cout << "*-------------------------------------*" << endl;
		getline(cin, select);

		validateUserResponse(select);

		if (select == "1")
		{
			correctAnswer = generateAddition();

			getline(cin, answer);

			answerNum = validateUserAnswer(answer);

			rightOrWrong = checkUserAnswer(correctAnswer, answerNum);

			updateStats(rightOrWrong, correct, wrong, earning);
		}
		else if (select == "2")
		{
			correctAnswer = generateSubtraction();

			getline(cin, answer);

			answerNum = validateUserAnswer(answer);

			rightOrWrong = checkUserAnswer(correctAnswer, answerNum);

			updateStats(rightOrWrong, correct, wrong, earning);
		}
		else if (select == "3")
		{
			correctAnswer = generateMultiplication();

			getline(cin, answer);

			answerNum = validateUserAnswer(answer);

			rightOrWrong = checkUserAnswer(correctAnswer, answerNum);

			updateStats(rightOrWrong, correct, wrong, earning);
		}
		else if (select == "4")
		{
			correctAnswer = generateDivision();

			getline(cin, answer);

			answerNum = validateUserAnswer(answer);

			rightOrWrong = checkUserAnswer(correctAnswer, answerNum);

			updateStats(rightOrWrong, correct, wrong, earning);
		}
		else if (select == "5")
		{
			system("cls");
			displayStats(name, correct, wrong, earning);
			system("cls");
			cout << "*-------------------------------------*" << endl;
			cout << ":                                     :" << endl;
			cout << ":                                     :" << endl;
		}
		else
		{
			system("cls");
		}
	} while (!(select == "n" || select == "N"));
}

void getUserName(string& userName)
{
	int strLength, counter = 0;

	system("cls");
	cout << "*-------------------------------------*" << endl;
	cout << ":       Please enter your name.       :" << endl;
	cout << ":                                     :" << endl;
	cout << "*-------------------------------------*" << endl;
	getline(cin, userName);

	strLength = userName.length();

	while (counter < strLength || counter == 0)
	{
		if (!isalpha(userName[counter]))
		{
			system("cls");
			cout << "*-------------------------------------*" << endl;
			cout << ":      Please enter a valid name      :" << endl;
			cout << ":      containing one word only.      :" << endl;
			cout << "*-------------------------------------*" << endl;
			getline(cin, userName);
			strLength = userName.length();
			counter = 0;
		}
		else if (strLength > 11)
		{
			system("cls");
			cout << "*-------------------------------------*" << endl;
			cout << ": Your name cannot exceed 11 letters. :" << endl;
			cout << ":     Please type another name.       :" << endl;
			cout << "*-------------------------------------*" << endl;
			getline(cin, userName);
			strLength = userName.length();
			counter = 0;
		}
		else
		{
			counter++;
		}
	}
}

void validateUserResponse(string& select)
{
	while (!(select == "1" || select == "2" || select == "3" || select == "4" || select == "5" || select == "n" || select == "N"))
	{
		system("cls");
		cout << "*-------------------------------------*" << endl;
		cout << ":       Invalid menu selection.       :" << endl;
		cout << ":   Please type from the choice ().   :" << endl;
		cout << "*-------------------------------------*" << endl;
		cout << ":              Game Menu              :" << endl;
		cout << ":    (1) Addition                     :" << endl;
		cout << ":    (2) Subtraction                  :" << endl;
		cout << ":    (3) Multiplication               :" << endl;
		cout << ":    (4) Division                     :" << endl;
		cout << ":    (5) Current statistic            :" << endl;
		cout << ":    (N) Save and return to home      :" << endl;
		cout << "*-------------------------------------*" << endl;
		getline(cin, select);
	}
}

int validateUserAnswer(string answer)
{
	int strLength, answerNum = 0, counter = 0;
	char nextChar;

	strLength = answer.length();

	while (counter < strLength || counter == 0)
	{
		if (!isdigit(answer[counter]))
		{
			cout << "Please type positive integer." << endl;
			getline(cin, answer);
			strLength = answer.length();
			counter = 0;
		}
		else
		{
			counter++;
		}
	}

	for (int counter = 0; counter < strLength; counter++)
	{
		nextChar = answer[counter];
		answerNum = answerNum * 10 + (nextChar - '0');
	}

	return answerNum;
}

int checkUserAnswer(int correctAnswer, int answerNum)
{
	system("cls");

	if (correctAnswer == answerNum)
	{
		cout << "*-------------------------------------*" << endl;
		cout << ":         That is correct!        :" << endl;
		cout << ":                                     :" << endl;
		return 1;
	}
	else
	{
		cout << "*-------------------------------------*" << endl;
		cout << ":         That is wrong.          :" << endl;
		cout << ":                                     :" << endl;
		return 0;
	}
}

void updateStats(int rightOrWrong, int& correct, int& wrong, double& earning)
{
	if (rightOrWrong == 1)
	{
		correct += 1;
		earning += 0.05;
	}
	else
	{
		wrong += 1;
		earning -= 0.03;
	}
}

void displayStats(string name, int correct, int wrong, double earning)
{
	cout << "*-------------------------------------*" << endl;
	cout << ":              Statistic              :" << endl;
	cout << ":                                     :" << endl;
	cout << "*-------------------------------------*" << endl;
	cout << ":                                     :" << endl;
	cout << ":   Name:                  " << left << setw(10) << name << " :" << endl;
	cout << ":   Total correct answer:  " << left << setw(3) << correct << "        :" << endl;
	cout << ":   Total wrong answer:    " << left << setw(3) << wrong << "        :" << endl;
	cout << ":   Total earning:         $" << left << setw(6) << fixed << showpoint << setprecision(2) << earning << "    :" << endl;
	cout << ":                                     :" << endl;
	cout << ":                                     :" << endl;
	cout << "*-------------------------------------*" << endl;
	system("pause");
}

void saveStats(ofstream& outputFile, string name, int correct, int wrong, double earning)
{
	string userName;
	userName = name + ".txt";

	outputFile.open(userName.c_str());

	outputFile << name << endl;
	outputFile << correct << endl;
	outputFile << wrong << endl;
	outputFile << fixed << showpoint << setprecision(2) << earning << endl;

	outputFile.close();
}

int generateAddition()
{
	system("cls");

	int num1, num2, correctAnswer;

	num1 = (rand() % 10) + 1;
	num2 = (rand() % 10) + 1;

	correctAnswer = num1 + num2;

	cout << "*-------------------------------------*" << endl;
	cout << ":              Addition               :" << endl;
	cout << ":             " << setw(2) << num1 << " + " << setw(2) << num2 << " = ?             :" << endl;
	cout << "*-------------------------------------*" << endl;

	return correctAnswer;
}


int generateSubtraction()
{
	system("cls");

	int num1, num2, correctAnswer;

	num1 = (rand() % 10) + 1;
	num2 = (rand() % num1) + 1;

	correctAnswer = num1 - num2;

	cout << "*-------------------------------------*" << endl;
	cout << ":             Subtraction             :" << endl;
	cout << ":             " << setw(2) << num1 << " - " << setw(2) << num2 << " = ?             :" << endl;
	cout << "*-------------------------------------*" << endl;

	return correctAnswer;
}

int generateMultiplication()
{
	system("cls");

	int num1, num2, correctAnswer;

	num1 = (rand() % 10) + 1;
	num2 = (rand() % 10) + 1;

	correctAnswer = num1 * num2;

	cout << "*-------------------------------------*" << endl;
	cout << ":            Muliplication            :" << endl;
	cout << ":             " << setw(2) << num1 << " x " << setw(2) << num2 << " = ?             :" << endl;
	cout << "*-------------------------------------*" << endl;

	return correctAnswer;
}

int generateDivision()
{
	system("cls");

	int num1, num2, correctAnswer;

	num1 = (rand() % 10) + 1;
	num2 = ((rand() % 10) + 1) * num1;

	correctAnswer = num2 / num1;

	cout << "*-------------------------------------*" << endl;
	cout << ":              Division               :" << endl;
	cout << ":             " << setw(2) << num2 << " / " << setw(2) << num1 << " = ?             :" << endl;
	cout << "*-------------------------------------*" << endl;

	return correctAnswer;
}
