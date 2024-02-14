#include <iostream>
#include<cstdlib>
#include <cmath>
#include <string>

using namespace std;

enum EnTypeOfQuestions { Easy = 1, Med = 2, Hard = 3, QMix = 4 };

enum EnTypeOfOperators { Add = 1, Sub = 2, Mul = 3, Div = 4, OMix = 5 };

struct StQuiz
{
	int NumberOfQuestions = 0;
	EnTypeOfQuestions QuestionsLevel;
	EnTypeOfOperators OpType;
	int NumberOfRightAnswers = 0;
	int NumberOfWrongAnswers = 0;
	int Result = 0;
};

struct StQuestionParts
{
	int FirstOperand;
	int SecondOperand;
	int OpFrom;
	int OpTo;
	int From_Random;
	int To_Random;
	int NumberOfQuestion = 0;
	char MainOp;
};

string Tabs(short num)
{
	string tab = "";
	for (short i = 0; i < num; i++)
	{
		tab += '\t';
	}

	return tab;
}

string MinusCharacter(short num)
{
	string minus = "";
	for (short i = 0; i < num; i++)
	{
		minus += '-';
	}

	return minus;
}

string ChangeEnumLevelToString(int Level)
{
	string Levels[4] = { "Easy", "Medium", "Hard", "Mix" };

	return Levels[Level - 1];
}

string ChangeEnumOperatorToString(int Operator)
{
	string Operators[5] = { "Add", "Sub", "Mul", "Div", "Mix" };

	return Operators[Operator - 1];
}

int ReadNumber(string Message, int From, int To, short TabsNum)
{
	int num = 0;

	do
	{
		cout << Tabs(TabsNum) << Message;
		cin >> num;

	} while (num < From || num > To);

	return num;
}

int RandomNumber(int From, int To)
{
	int Random = rand() % (To - From + 1) + From;

	return Random;
}

short RandomNumberForOperators(int From, int To)
{
	short Random;

	do
	{
		Random = rand() % (To - From + 1) + From;

	} while (Random == 44 || Random == 46);

	return Random;
}

bool PassOrFail(StQuiz& Quiz)
{
	return Quiz.NumberOfRightAnswers >= Quiz.NumberOfWrongAnswers;
}

void ExamResult(StQuiz& Quiz)
{
	cout << endl << endl;

	cout << Tabs(2) << MinusCharacter(70) << endl;
	if (PassOrFail(Quiz))
	{
		cout << Tabs(5) << "    You have PASSED" << endl;
		system("color 2F");
	}
	else
	{
		cout << Tabs(5) << "    You have FAILED" << endl;
		system("color 4F");
	}

	cout << Tabs(2) << MinusCharacter(70) << endl;
	cout << endl;
	cout << Tabs(2) << "   Number Of Questions : " << Quiz.NumberOfQuestions << endl;
	cout << Tabs(2) << "   Questions Level     : " << ChangeEnumLevelToString(Quiz.QuestionsLevel) << endl;
	cout << Tabs(2) << "   Operator Type       : " << ChangeEnumOperatorToString(Quiz.OpType) << endl;
	cout << Tabs(2) << "   Right Answers       : " << Quiz.NumberOfRightAnswers << endl;
	cout << Tabs(2) << "   Wrong Answers       : " << Quiz.NumberOfWrongAnswers << endl;
	cout << Tabs(2) << MinusCharacter(70) << endl << endl;
}

int CheckResult(StQuestionParts& QuestionParts)
{
	switch (QuestionParts.MainOp)
	{
	case '+':
		return QuestionParts.FirstOperand + QuestionParts.SecondOperand;

	case '-':
		return QuestionParts.FirstOperand - QuestionParts.SecondOperand;

	case '*':
		return QuestionParts.FirstOperand * QuestionParts.SecondOperand;

	case '/':
		return QuestionParts.FirstOperand / QuestionParts.SecondOperand;
	}
}

void PrintQuestion(StQuestionParts& QuestionParts, StQuiz& Quiz)
{
	int Result = 0;
	int RightResult = 0;

	cout << endl << endl;
	cout << Tabs(2) << MinusCharacter(10) << " Question [" << QuestionParts.NumberOfQuestion << "] " << MinusCharacter(10) << endl;
	cout << Tabs(3) << " " << QuestionParts.FirstOperand << endl;
	cout << Tabs(3) << QuestionParts.MainOp << endl;
	cout << Tabs(3) << " " << QuestionParts.SecondOperand << endl;
	cout << Tabs(3) << "______________" << endl;
	Result = ReadNumber("", -100000, 100000, 3);

	cout << endl << endl;
	RightResult = CheckResult(QuestionParts);

	if (RightResult == Result)
	{
		Quiz.NumberOfRightAnswers++;
		cout << Tabs(2) << "Right Answer: -)" << endl;
		system("color 2F");
	}
	else
	{
		Quiz.NumberOfWrongAnswers++;
		cout << Tabs(2) << "Wrong Answer: -(";
		system("color 4F");
		cout << endl << endl;
		cout << Tabs(2) << "The right answer is " << RightResult << endl;
	}
}

void DecideOperatorType(StQuiz& Quiz, StQuestionParts& QuestionParts)
{
	switch (Quiz.OpType)
	{
	case EnTypeOfOperators::Add:

		QuestionParts.OpFrom = 43;
		QuestionParts.OpTo = 43;
		break;

	case EnTypeOfOperators::Sub:

		QuestionParts.OpFrom = 45;
		QuestionParts.OpTo = 45;
		break;

	case EnTypeOfOperators::Mul:

		QuestionParts.OpFrom = 42;
		QuestionParts.OpTo = 42;
		break;

	case EnTypeOfOperators::Div:

		QuestionParts.OpFrom = 47;
		QuestionParts.OpTo = 47;
		break;

	case EnTypeOfOperators::OMix:

		QuestionParts.OpFrom = 42;
		QuestionParts.OpTo = 47;
		break;
	}
}

void DecideQuestionsType(StQuiz& Quiz, StQuestionParts& QuestionParts)
{
	switch (Quiz.QuestionsLevel)
	{
	case EnTypeOfQuestions::Easy:
		QuestionParts.From_Random = 1;
		QuestionParts.To_Random = 10;
		break;

	case EnTypeOfQuestions::Med:
		QuestionParts.From_Random = 11;
		QuestionParts.To_Random = 50;
		break;

	case EnTypeOfQuestions::Hard:
		QuestionParts.From_Random = 50;
		QuestionParts.To_Random = 100;
		break;

	case EnTypeOfQuestions::QMix:
		QuestionParts.From_Random = 1;
		QuestionParts.To_Random = 100;
		break;
	}
}

void QuizChoicesForStarting(StQuiz& Quiz)
{
	cout << endl << endl;
	cout << Tabs(2) << MinusCharacter(70) << endl;
	cout << Tabs(5) << "Choices For Which Questions" << endl;
	cout << Tabs(2) << MinusCharacter(70);

	cout << endl << endl;
	cout << Tabs(3) << "Easy [1]  /  Med [2]  /  Hard [3]  /  Mix [4]" << endl;
	Quiz.QuestionsLevel = EnTypeOfQuestions(ReadNumber("Enter the type of Questions you want (Look Above): ", 1, 4, 3));

	cout << endl << endl;
	cout << Tabs(3) << "Add [1]  /  Sub [2]  /  Mul [3]  /  Div [4] / Mix [5]" << endl;
	Quiz.OpType = EnTypeOfOperators(ReadNumber("Enter the type of Operators you want (Look Above): ", 1, 5, 3));

	cout << endl;
	cout << Tabs(2) << MinusCharacter(70) << endl;
}

void QuizTime(int QuestionsNumber)
{
	StQuiz Quiz;
	StQuestionParts QuestionParts;

	Quiz.NumberOfQuestions = QuestionsNumber;

	QuizChoicesForStarting(Quiz);
	DecideQuestionsType(Quiz, QuestionParts);
	DecideOperatorType(Quiz, QuestionParts);

	for (int i = 1; i <= QuestionsNumber; i++)
	{
		QuestionParts.FirstOperand = RandomNumber(QuestionParts.From_Random, QuestionParts.To_Random);
		QuestionParts.SecondOperand = RandomNumber(QuestionParts.From_Random, QuestionParts.To_Random);
		QuestionParts.NumberOfQuestion = i;
		QuestionParts.MainOp = char(RandomNumberForOperators(QuestionParts.OpFrom, QuestionParts.OpTo));
		PrintQuestion(QuestionParts, Quiz);
	}

	ExamResult(Quiz);

}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartQuiz()
{
	char TestAgain = 'y';

	do
	{
		ResetScreen();
		QuizTime(ReadNumber("Please enter how many Questions do you want in your Quiz: ", 1, 30000, 0));
		cout << "Do you wanna pass The test again (Y/N): ";
		cin >> TestAgain;

	} while (TestAgain == 'Y' || TestAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartQuiz();

	return 0;
}