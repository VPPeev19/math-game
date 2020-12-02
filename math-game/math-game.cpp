#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

//Declare appripriate function prototypes (some functions are returning value function).
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
	//Declare appropriate variables.
	ofstream outputFile;
	ifstream inputFile;
	int correct = 0, wrong = 0;
	double earning = 0.00;
	string name, continu = "y";

	//srand() is used to create random number every moment.
	unsigned seed = time(0);
	srand(seed);

	//Again, We added do-while loop to make the program more like an actual game.
	do
	{
		credits(continu);
		if (continu == "y" || continu == "Y")
		{
			retrieveStats(outputFile, inputFile, name, correct, wrong, earning);
			menu(name, correct, wrong, earning);
			saveStats(outputFile, name, correct, wrong, earning);

			//Reset the statistic variables for next user.
			correct = 0;
			wrong = 0;
			earning = 0.00;
		}
	} while (continu == "y" || continu == "Y");
	return 0;
}

//Home screen to display the name of the program and my name.
void credits(string& continu)
{
	cout << "*-------------------------------------*" << endl;
	cout << ":            The Math Game            :" << endl;
	cout << ":          by Team FullHouse          :" << endl;
	cout << ":    (Todor,Stanimir,Andrei,Valentin) :" << endl;
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

//Retrieve user data function.
void retrieveStats(ofstream& outputFile, ifstream& inputFile, string& name, int& correct, int& wrong, double& earning)
{
	//Declare appropriate variables.
	string userName;

	//Call get user name function.
	getUserName(userName);

	name = userName;
	userName += ".txt";

	//open an inputfile.
	inputFile.open(userName.c_str());

	//If the inputfile with the user name does not exist, the program will proceed to the game WITHOUT retrieving the user data file.
	if (inputFile.is_open())
	{
		//retrieving.
		inputFile >> name;
		inputFile >> correct;
		inputFile >> wrong;
		inputFile >> earning;
		inputFile.close();

		//Program will greet a returning user.
		system("cls");
		cout << "*-------------------------------------*" << endl;
		cout << ":       Welcome back! " << left << setw(10) << name << "      :" << endl;
		cout << ":                                     :" << endl;
	}
	else
	{
		//Program will greet a new user.
		system("cls");
		cout << "*-------------------------------------*" << endl;
		cout << ":      Welcome to the Math Game!      :" << endl;
		cout << ":              " << left << setw(10) << name << "             :" << endl;
	}
}

//main menu function.
void menu(string name, int& correct, int& wrong, double& earning)
{
	//Declare appropriate variables.
	string select, answer;
	int correctAnswer, answerNum, rightOrWrong = 0;

	//do-while loop is used for menu-driven loop.
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

		//Calling the function that validates the user input for menu selection.
		//A string data type was used for menu selection.
		validateUserResponse(select);

		//After validating, depending on the selection, the program will execute the selected option.
		// choice 1 is Addition.
		if (select == "1")
		{
			//Set the correct answer to the returned value from the generateAddition function.
			correctAnswer = generateAddition();

			//Asks the user to type in the user's answer.
			getline(cin, answer);

			//Validate the user's answer and convert it to integer and set it to a variable answerNum
			answerNum = validateUserAnswer(answer);

			//rightOrWrong variable will determine whether the user's answer is correct or incorrect by having either 1 or 0 integer value.
			rightOrWrong = checkUserAnswer(correctAnswer, answerNum);

			//Calling updateStats function. rightOrWrong variable is used.
			updateStats(rightOrWrong, correct, wrong, earning);
		}
		//Subtraction.
		else if (select == "2")
		{
			correctAnswer = generateSubtraction();
			getline(cin, answer);
			answerNum = validateUserAnswer(answer);
			rightOrWrong = checkUserAnswer(correctAnswer, answerNum);
			updateStats(rightOrWrong, correct, wrong, earning);
		}
		//Multiplication.
		else if (select == "3")
		{
			correctAnswer = generateMultiplication();
			getline(cin, answer);
			answerNum = validateUserAnswer(answer);
			rightOrWrong = checkUserAnswer(correctAnswer, answerNum);
			updateStats(rightOrWrong, correct, wrong, earning);
		}
		//Division.
		else if (select == "4")
		{
			correctAnswer = generateDivision();
			getline(cin, answer);
			answerNum = validateUserAnswer(answer);
			rightOrWrong = checkUserAnswer(correctAnswer, answerNum);
			updateStats(rightOrWrong, correct, wrong, earning);
		}
		//Displaying the statistic of user's current progress.
		else if (select == "5")
		{
			//clears the screen, and call the displayStats function.
			system("cls");
			displayStats(name, correct, wrong, earning);
			system("cls");
			cout << "*-------------------------------------*" << endl;
			cout << ":                                     :" << endl;
			cout << ":                                     :" << endl;
		}
		//Returning to the home screen.
		else
		{
			system("cls");
		}
	} while (!(select == "n" || select == "N"));
}

//Function that gets the user name.
void getUserName(string& userName)
{
	//Declare appropriate variables.
	int strLength, counter = 0;

	//Asks the user to type his/her name to proceed.
	system("cls");
	cout << "*-------------------------------------*" << endl;
	cout << ":       Please enter your name.       :" << endl;
	cout << ":                                     :" << endl;
	cout << "*-------------------------------------*" << endl;
	getline(cin, userName);

	//Finding how many letters are there in the user input.
	strLength = userName.length();

	//Input Validation.
	while (counter < strLength || counter == 0)
	{
		//Validation. Only a letter and one word is allowed.
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
		//Validation. The name cannot have more than 10 letters.
		else if (strLength > 10)
		{
			system("cls");
			cout << "*-------------------------------------*" << endl;
			cout << ": Your name cannot exceed 10 letters. :" << endl;
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

//Function that validates user's input for menu selection.
void validateUserResponse(string& select)
{
	//Simple. only 1, 2, 3, 4, 5, n, N is allowed.
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

//Value returning function that validates user's answer for game problems.
int validateUserAnswer(string answer)
{
	//Declare appropriate variables.
	int strLength, answerNum = 0, counter = 0;
	char nextChar;

	//Finding how many chars are there from the user's input.
	strLength = answer.length();

	//Input Validation.
	while (counter < strLength || counter == 0)
	{
		//Validatation. Only numbers are allowed.
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

	//Convert the user's answer to integer datatype.
	for (int counter = 0; counter < strLength; counter++)
	{
		nextChar = answer[counter];
		answerNum = answerNum * 10 + (nextChar - '0');
	}

	//Return the answer as an integer value.
	return answerNum;
}

//Value returning Function that Checks whether the user's answer is correct or wrong.
int checkUserAnswer(int correctAnswer, int answerNum)
{
	system("cls");

	//If the answer is correct, returns the value as 1.
	if (correctAnswer == answerNum)
	{
		cout << "*-------------------------------------*" << endl;
		cout << ":         That is correct!            :" << endl;
		cout << ":                                     :" << endl;
		return 1;
	}
	//If the answer is incorrect, returns the value as 0.
	else
	{
		cout << "*-------------------------------------*" << endl;
		cout << ":         That is wrong. :(           :" << endl;
		cout << ":                                     :" << endl;
		return 0;
	}
}

//Function that updates the user's statistic.
void updateStats(int rightOrWrong, int& correct, int& wrong, double& earning)
{
	//By using the rightOrWrong variable, update the statistic of the user.
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

//Function that displays the User's current progress.
void displayStats(string name, int correct, int wrong, double earning)
{
	//That precision tho. Looking nice and neat.
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

//Function that saves the current progress to the txt file when exiting the game.
void saveStats(ofstream& outputFile, string name, int correct, int wrong, double earning)
{
	//Declare appropriate variables.
	string userName;
	userName = name + ".txt";

	//Open the outputFile with the text file named user name.
	outputFile.open(userName.c_str());

	//write the data.
	outputFile << name << endl;
	outputFile << correct << endl;
	outputFile << wrong << endl;
	outputFile << fixed << showpoint << setprecision(2) << earning << endl;

	//Close the outputFile.
	outputFile.close();
}

//Function that generate addition problem. The function will return an integer value of correct answer to that problem.
int generateAddition()
{
	system("cls");

	//Declare appropriate variables.
	int num1, num2, correctAnswer;

	//Create 2 random numbers ranging from 1 to 10.
	num1 = (rand() % 10) + 1;
	num2 = (rand() % 10) + 1;

	//set the correct answer.
	correctAnswer = num1 + num2;

	//Display the game problem to the user.
	cout << "*-------------------------------------*" << endl;
	cout << ":              Addition               :" << endl;
	cout << ":             " << setw(2) << num1 << " + " << setw(2) << num2 << " = ?             :" << endl;
	cout << "*-------------------------------------*" << endl;

	//return an integer value of the correct answer.
	return correctAnswer;
}

//Function that generate subtraction problem. The function will return an integer value of correct answer to that problem.
int generateSubtraction()
{
	system("cls");

	//Declare appropriate variables.
	int num1, num2, correctAnswer;

	//Create 2 random numbers. num1 ranges from 1 to 10.
	//num2 ranges from 1 to num1 because we need num2 to be less than num1.
	num1 = (rand() % 10) + 1;
	num2 = (rand() % num1) + 1;

	//set the correct answer.
	correctAnswer = num1 - num2;

	//Display the game problem to the user.
	cout << "*-------------------------------------*" << endl;
	cout << ":             Subtraction             :" << endl;
	cout << ":             " << setw(2) << num1 << " - " << setw(2) << num2 << " = ?             :" << endl;
	cout << "*-------------------------------------*" << endl;

	//return an integer value of the correct answer.
	return correctAnswer;
}

//Function that generate multiplication problem. The function will return an integer value of correct answer to that problem.
int generateMultiplication()
{
	system("cls");

	//Declare appripriate variables.
	int num1, num2, correctAnswer;

	//Create 2 random numbers ranging from 1 to 10.
	num1 = (rand() % 10) + 1;
	num2 = (rand() % 10) + 1;

	//set the correct answer.
	correctAnswer = num1 * num2;

	//Display the game problem to the user.
	cout << "*-------------------------------------*" << endl;
	cout << ":            Muliplication            :" << endl;
	cout << ":             " << setw(2) << num1 << " x " << setw(2) << num2 << " = ?             :" << endl;
	cout << "*-------------------------------------*" << endl;

	//return an integer value of the correct answer.
	return correctAnswer;
}

//Function that generate division problem. The function will return an integer value of correct answer to that problem.
int generateDivision()
{
	system("cls");

	//Declare appripriate variables.
	int num1, num2, correctAnswer;

	//Create 2 random numbers. num1 ranges from 1 to 10.
	//num2 first generate number that ranges from 1 to 10 and it is multiplied by the num1.
	//the former number of num2 before multiplying, that value will be the correct answer.
	num1 = (rand() % 10) + 1;
	num2 = ((rand() % 10) + 1) * num1;

	//set the correct answer.
	correctAnswer = num2 / num1;

	//Display the game problem to the user.
	cout << "*-------------------------------------*" << endl;
	cout << ":              Division               :" << endl;
	cout << ":             " << setw(2) << num2 << " / " << setw(2) << num1 << " = ?             :" << endl;
	cout << "*-------------------------------------*" << endl;

	//return an integer value of the correct answer.
	return correctAnswer;
}
