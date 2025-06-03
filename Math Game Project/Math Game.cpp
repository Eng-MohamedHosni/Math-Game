#include <iostream>
#include<string>
#include<cmath>
using namespace std;

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}

enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };

enum enOpType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

enum enCheckAnswer { True = 1, False = 2 };

struct stQuestion
{
	short Num1;
	short Num2;
	enOpType OpType;
	enQuestionLevel QuestionLevel;
	short PlayerAnswer = 0;
	short RightAnswer = 0;
	short RoundNumber = 0;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	enQuestionLevel QuestionLevel;
	enOpType OpType;
	int GameRounds = 0;
	int NumberOfRightAnswers = 0;
	int NumberOfWrongAnswers = 0;
	bool IsPass = false;
};



enQuestionLevel ReadQuestionLevel()
{
	short Choice;
	do
	{
		cout << "\nEnter Question Level  [1] Easy , [2] Med , [3] Hard, [4] Mix ?";
		cin >> Choice;
	} while (Choice < 1 || Choice>4);
	return (enQuestionLevel)Choice;

}

int ReadHowManyQuestion()
{

	int Num = 0, From = 1, To = 10;
	do

	{
		cout << "How many Questions do you want to answer? ";
		cin >> Num;
	} while (Num<From || Num >To);
	return Num;
}

string QuestionLevelName(stQuizz Quizz)
{
	string Arr[4]{ "Easy" ,"Med" ,"Hard","Mix" };
	return Arr[Quizz.QuestionLevel - 1];
}


enOpType ReadOpType()
{
	short Choice;
	do
	{
		cout << "\nEnter Operation Type  [1] Add , [2] Sub , [3] Mul , [4] Div ,[5] Mix ?";
		cin >> Choice;
	} while (Choice < 1 || Choice>5);
	return (enOpType)Choice;

}

string OpTypeName(stQuizz Quizz)
{
	string Arr[5]{ "Add" ,"Sub" ,"Mul","Div","Mix" };
	return Arr[Quizz.OpType - 1];
}


enOpType RandMixForOpType(enOpType Type)
{
	
	if (Type == enOpType::MixOp)
	{
		return (enOpType)RandomNumber(1, 4);
	}
	return Type;

}

int CalcRightAnswer(int Num1, int Num2, enOpType OpType)
{
	if (OpType == enOpType::Add)
		return Num1 + Num2;
	else if (OpType == enOpType::Sub)
		return Num1 - Num2;
	else if (OpType == enOpType::Mul)
		return Num1 * Num2;
	else if (OpType == enOpType::Div)
		return Num1 / Num2;

}

enCheckAnswer CheckAnswer(stQuizz Quizz, int QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].RightAnswer == Quizz.QuestionList[QuestionNumber].PlayerAnswer)
		return enCheckAnswer::True;
	else
		return enCheckAnswer::False;
}

void ShowAnswer(enCheckAnswer Answer, stQuizz& Quizz, int QuestionNumber)
{
	switch (Answer)
	{
	case enCheckAnswer::True:
	{
		system("color 2F");
		Quizz.NumberOfRightAnswers++;
		cout << "Right Answer :-)" << endl;
		break;
	}
	case enCheckAnswer::False:
	{
		system("color 4F");
		cout << "Wrong Answer :-(" << endl;
		cout << "\a";
		cout << "The right answer is : " << Quizz.QuestionList[QuestionNumber].RightAnswer << endl;
		break;
	}

	}
}

string OpTypeCharacter(enOpType OpType)
{
	string Arr[4]{ " + ", " - ", " * " ," / " };
	return Arr[OpType - 1];
}

void PrintQuestion(stQuizz Quizz, int QuestionNumber)
{
	cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.GameRounds << "]\n" << endl;
	cout << Quizz.QuestionList[QuestionNumber].Num1 << endl << endl;
	cout<< Quizz.QuestionList[QuestionNumber].Num2<< " " << OpTypeCharacter(Quizz.QuestionList[QuestionNumber].OpType) << endl;
	cout << "____________________\n\n";
}


void ShowFinalScreen(stQuizz& Quizz)
{
	cout << "\n________________________________________\n\n";
	cout << "Final Results is  ";
	if (Quizz.NumberOfRightAnswers > (Quizz.NumberOfWrongAnswers))
	{
		system("color 2F");
		cout << "Pass" << endl;
	}
	else
	{
		system("color 4F");
		cout << "Fail" << endl;
	}
	cout << "________________________________________\n\n";
}
void AskAndCorrectQuestionAnswer(stQuizz& Quizz)
{
	for (int QuestionNumber = 0; QuestionNumber < Quizz.GameRounds; QuestionNumber++)
	{
		PrintQuestion(Quizz, QuestionNumber);
		cin >> Quizz.QuestionList[QuestionNumber].PlayerAnswer;
		ShowAnswer(CheckAnswer(Quizz, QuestionNumber), Quizz, QuestionNumber);
	}
}


void PrintFinalGameResults(stQuizz Quizz)
{
	cout << "Number of Questions :" << Quizz.GameRounds << endl;
	cout << "Question Level :" << QuestionLevelName(Quizz) << endl;
	cout << "OpType       : " << OpTypeName(Quizz) << endl;
	cout << "Number of Right Answers : " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number of Wrong Answers : " << Quizz.NumberOfWrongAnswers << endl;
	cout << "______________________________________________________\n";
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOpType OpType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionLevel::Mix)
	{
		QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
	}
	

	if (OpType == enOpType::MixOp)
	{
		OpType = RandMixForOpType(OpType);
	}
	Question.OpType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionLevel::Easy:
	{
		Question.Num1 = RandomNumber(1, 10);
		Question.Num2 = RandomNumber(1, 10);
		break;
	}
	case enQuestionLevel::Med:
	{
		Question.Num1 = RandomNumber(10, 50);
		Question.Num2 = RandomNumber(10, 50);
		break;
	}
	case enQuestionLevel::Hard:
	{
		Question.Num1 = RandomNumber(50, 100);
		Question.Num2 = RandomNumber(50, 100);
		break;
	}
	}

	Question.RightAnswer = CalcRightAnswer(Question.Num1, Question.Num2, Question.OpType);
	return Question;
}


void GenerateQuizzQuestion(stQuizz& Quizz)
{
	for (short Round = 0; Round < Quizz.GameRounds; Round++)
	{
		Quizz.QuestionList[Round] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);


	}
}

void PlayMathGame()
{
	stQuizz Quizz;
	stQuestion Question;
	Quizz.GameRounds = ReadHowManyQuestion();
	Quizz.QuestionLevel = ReadQuestionLevel();
	Quizz.OpType = ReadOpType();

	GenerateQuizzQuestion(Quizz);
	AskAndCorrectQuestionAnswer(Quizz);
	ShowFinalScreen(Quizz);
	PrintFinalGameResults(Quizz);
}


void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartPlay()
{

	char PlayAgain = 'y';
	do
	{
		ResetScreen();
		PlayMathGame();

		cout << "Do you want to play again ? Y/N ?";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartPlay();

}
