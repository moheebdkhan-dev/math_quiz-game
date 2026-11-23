#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "myInputLib.h"
#include "myRandomLib.h"

using namespace std;

enum enQuizLevel { Easy = 1, Medium = 2, Hard = 3, Mix = 4 };

enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

enum enFinalResult { Pass, Fail };

struct stQuizInfo {
	unsigned short QuestionsNumber;
	enQuizLevel QuizLvl;
	enOperationType OperType;
};

struct stQuestion {
	short QuesNumber;
	short Num1, Num2;
	enOperationType Operation;
	enQuizLevel QuesLvl;
	short RightAnswer, UserAnswer;
	bool IsAnswerCorrect;
};

struct stQuizResult {
	stQuizInfo QuizInfo;
	unsigned short  RightAnswers = 0, WrongAnswers = 0;
	enFinalResult FinalResult;
};

stQuizInfo ReadQuizInfo() {
	stQuizInfo QuizInfo = stQuizInfo();
	QuizInfo.QuestionsNumber = myInputLib::readIntegerInRange("How many questions 1 - 10", 1, 10);
	QuizInfo.OperType = (enOperationType)myInputLib::readIntegerInRange("Enter the operation type [1] Add, [2] Sub, [3] Mult, [4] Div, [5] Mix Operations", 1, 5);
	QuizInfo.QuizLvl = (enQuizLevel)myInputLib::readIntegerInRange("Enter the Quiz level [1] Easy, [2] Medium, [3] Hard, [4] Mix", 1, 4);
	return QuizInfo;
}

enQuizLevel GenerateRandomLvl() {
	return (enQuizLevel)myRandomLib::RandomNumber(1, 3);
}

enOperationType GenerateRandomOperation() {
	return (enOperationType)myRandomLib::RandomNumber(1, 4);
}

short GenerateNumDependingOnLvl(enQuizLevel lvl) {
	switch (lvl) {
	case enQuizLevel::Easy:return myRandomLib::RandomNumber(1, 10);
	case enQuizLevel::Medium:return myRandomLib::RandomNumber(10, 50);
	case enQuizLevel::Hard:return myRandomLib::RandomNumber(50, 100);
	}
}

short RightAnswer(short Num1, short Num2, enOperationType Oper) {
	switch (Oper) {
	case enOperationType::Add: return Num1 + Num2;
	case enOperationType::Sub: return Num1 - Num2;
	case enOperationType::Mult: return Num1 * Num2;
	case enOperationType::Div: return Num1 / Num2;
	default: return Num1 + Num2;
	}
}

stQuestion GenerateQuestion(stQuizInfo QuizInfo) {
	stQuestion Ques = stQuestion();
	enQuizLevel QuesLvl = (QuizInfo.QuizLvl == enQuizLevel::Mix) ? GenerateRandomLvl() : QuizInfo.QuizLvl;
	Ques.Num1 = GenerateNumDependingOnLvl(QuesLvl);
	Ques.Num2 = GenerateNumDependingOnLvl(QuesLvl);
	Ques.QuesLvl = QuesLvl;
	Ques.Operation = (QuizInfo.OperType == enOperationType::MixOp) ? GenerateRandomOperation() : QuizInfo.OperType;
	Ques.RightAnswer = RightAnswer(Ques.Num1, Ques.Num2, Ques.Operation);
	return Ques;
}

void GenerateManyQuestions(stQuestion Questions[], stQuizInfo QuizInfo) {
	for (short i = 0; i < QuizInfo.QuestionsNumber; i++)
	{
		Questions[i] = GenerateQuestion(QuizInfo);
		Questions[i].QuesNumber = i + 1;
	}
}

string StrOperation(enOperationType OpType) {
	switch (OpType) {
	case enOperationType::Add:return "+";
	case enOperationType::Sub:return "-";
	case enOperationType::Mult:return "X";
	case enOperationType::Div:return "/";
	default:return "Mix";
	}
}

void ScreenInteraction(bool IsAnswerCorrect, short RightAnswer = 0) {
	if (IsAnswerCorrect) {
		system("color 2F");
		cout << "Right Answer :-)\n";
	}
	else {
		system("color 4F");
		cout << "Wrong Answer :-(\nThe right answer is : " << RightAnswer << endl;
	}
}

void ResetScreen() {
	system("color 0F");
	system("cls");
}


string StrQuizLvl(enQuizLevel lvl) {
	switch (lvl) {
	case enQuizLevel::Easy:
		return "Easy";
	case enQuizLevel::Medium:
		return "Medium";
	case enQuizLevel::Hard:
		return "Hard";
	case enQuizLevel::Mix:
		return "Mix";

	}
}
void AskQuestion(stQuestion& Question, unsigned short QuestionsNum, stQuizResult& QuizResult) {
	cout << "\nQuestion [" << Question.QuesNumber << "/" << QuestionsNum << "], Question lvl : " << StrQuizLvl(Question.QuesLvl) << endl;;
	cout << Question.Num1 << endl;
	cout << Question.Num2 << "\t" << StrOperation(Question.Operation) << endl;
	cout << "---------------\n";
	cin >> Question.UserAnswer;
	Question.IsAnswerCorrect = Question.RightAnswer == Question.UserAnswer;
	if (Question.IsAnswerCorrect) {
		QuizResult.RightAnswers++;
	}
	else {
		QuizResult.WrongAnswers++;
	}
	ScreenInteraction(Question.IsAnswerCorrect, Question.RightAnswer);
}
string StrQuizResult(enFinalResult res) {
	return res == enFinalResult::Pass ? "Pass" : "Fail";
}

void PrintQuizResult(stQuizResult QuizResult) {
	cout << "Final Quiz Result : " << StrQuizResult(QuizResult.FinalResult) << endl;
	cout << "Question Number : " << QuizResult.QuizInfo.QuestionsNumber << endl;
	cout << "Right Answers : " << QuizResult.RightAnswers << endl;
	cout << "Wrong Answers : " << QuizResult.WrongAnswers << endl;
	cout << "Operation Type : " << StrOperation(QuizResult.QuizInfo.OperType) << endl;
	cout << "Quiz Level : " << StrQuizLvl(QuizResult.QuizInfo.QuizLvl) << endl;

}

void PlayOneQuiz(stQuizInfo QuizInfo) {
	stQuestion Questions[100];
	stQuizResult QuizResult;
	QuizResult.QuizInfo = QuizInfo;
	GenerateManyQuestions(Questions, QuizInfo);
	for (int ques = 0; ques < QuizInfo.QuestionsNumber; ques++) {
		AskQuestion(Questions[ques], QuizInfo.QuestionsNumber, QuizResult);
	}
	QuizResult.FinalResult = (QuizResult.RightAnswers >= QuizResult.WrongAnswers) ? enFinalResult::Pass : enFinalResult::Fail;
	PrintQuizResult(QuizResult);
}

void StartGame() {
	char PlayAgain = 'Y';
	do {
		ResetScreen();
		stQuizInfo QuizInfo = ReadQuizInfo();
		PlayOneQuiz(QuizInfo);
		cout << "Do you want to play again? (Y,N) : ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{

	srand((unsigned)time(NULL));
	StartGame();

}