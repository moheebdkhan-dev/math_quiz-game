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
	unsigned short  RightAnswers=0, WrongAnswers=0;
	enFinalResult FinalResult;
};

stQuizInfo ReadQuizInfo() {
	stQuizInfo QuizInfo = stQuizInfo();
	QuizInfo.QuestionsNumber = myInputLib::readIntegerInRange("How many questions 1 - 10", 1, 10);
	QuizInfo.OperType = (enOperationType)myInputLib::readIntegerInRange("Enter the operation type [1] Add, [2] Sub, [3] Mult, [4] Div, [5] Mix Operations", 1, 5);
	QuizInfo.QuizLvl =(enQuizLevel) myInputLib::readIntegerInRange("Enter the Quiz level [1] Easy, [2] Medium, [3] Hard, [4] Mix", 1, 4);
	return QuizInfo;
}

enQuizLevel GenerateRandomLvl() {
	return (enQuizLevel) myRandomLib::RandomNumber(1, 3);
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
	}
}

void ScreenInteraction(bool IsAnswerCorrect,short RightAnswer = 0) {
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

void AskQuestion(stQuestion& Question, unsigned short QuestionsNum, stQuizResult& QuizResult) {
	cout << "\nQuestion [" << Question.QuesNumber << "/" << QuestionsNum << "], Question lvl : " << Question.QuesLvl << endl;;
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
	cout << "Operation Type : " << QuizResult.QuizInfo.OperType<< endl;
	cout << "Quiz Level : " << QuizResult.QuizInfo.QuizLvl << endl;

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



	return 0;
}







/*
#include <iostream>   // Include iostream for input/output operations.
#include <cstdlib>    // Include cstdlib for system functions like clearing the screen.
#include <ctime>      // Include ctime for random number seeding.
using namespace std;  // Use the standard namespace to avoid prefixing std:: before standard functions.

// Enumeration: enQuestionsLevel
// Purpose: Defines the difficulty levels available for quiz questions.
enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };

// Enumeration: enOperationType
// Purpose: Defines the types of arithmetic operations used in the quiz.
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

// Function: RandomNumber
// Purpose: Generates a random number within the given range [From, To].
// Parameters:
//   - From: Lower bound of the random range.
//   - To: Upper bound of the random range.
// Returns: A random integer between From and To.
int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

// Function: GetOpTypeSymbol
// Purpose: Converts an operation type to its corresponding symbol.
// Parameters:
//   - OpType: The arithmetic operation type.
// Returns: A string representation of the operator.
string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "x";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}

// Function: GetRandomOperationType
// Purpose: Generates a random arithmetic operation type.
// Returns: A random enOperationType value.
enOperationType GetRandomOperationType()
{
	return (enOperationType)RandomNumber(1, 4);
}

// Function: GetQuestionLevelText
// Purpose: Converts an enQuestionsLevel enum to a string representation.
// Parameters:
//   - QuestionLevel: The selected difficulty level.
// Returns: A string representation of the difficulty level.
string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy","Medium","Hard","Mixed" };
	return arrQuestionLevelText[QuestionLevel - 1];
}

// Function: SetScreenColor
// Purpose: Changes the console screen color based on answer correctness.
// Parameters:
//   - Right: Boolean value indicating if the answer is correct.
void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F"); // Green for correct answers.
	else
	{
		system("color 4F"); // Red for incorrect answers.
		cout << "\a"; // Plays an alert sound.
	}
}

// Function: SimpleCalculator
// Purpose: Performs the selected arithmetic operation on two numbers.
// Parameters:
//   - Number1: First operand.
//   - Number2: Second operand.
//   - OpType: The operation type (Add, Sub, Mult, or Div).
// Returns: The result of the operation.
int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return (Number2 != 0) ? (Number1 / Number2) : 0;  // Avoid division by zero.
	default:
		return Number1 + Number2;
	}
}

// Structure: stQuestion
// Purpose: Stores information for a single quiz question.
struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionsLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

// Structure: stQuizz
// Purpose: Stores details of the entire quiz session.
struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions;---
	enQuestionsLevel QuestionsLevel;---
	enOperationType OpType;---
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;
};

// Function: GenerateQuestion
// Purpose: Creates a random math question based on difficulty and operation type.
stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionsLevel::Mix)
		QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);

	if (OpType == enOperationType::MixOp)
		OpType = GetRandomOperationType();

	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionsLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		break;
	case enQuestionsLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		break;
	case enQuestionsLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		break;
	}

	Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
	Question.QuestionLevel = QuestionLevel;

	return Question;
}

// Function: AskAndCorrectQuestionListAnswers
// Purpose: Iterates through quiz questions, evaluates answers, and provides feedback.
void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n";
		cout << Quizz.QuestionList[QuestionNumber].Number1 << " "
			<< GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType) << " "
			<< Quizz.QuestionList[QuestionNumber].Number2 << " = ";

		cin >> Quizz.QuestionList[QuestionNumber].PlayerAnswer;

		if (Quizz.QuestionList[QuestionNumber].PlayerAnswer == Quizz.QuestionList[QuestionNumber].CorrectAnswer)
		{
			cout << "Correct!\n";
			Quizz.NumberOfRightAnswers++;
		}
		else
		{
			cout << "Wrong! Correct Answer: " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
			Quizz.NumberOfWrongAnswers++;
		}
	}

	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

// Function: PlayMathGame
// Purpose: Initializes the quiz, generates questions, and manages the quiz flow.
void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions = 5;  // Set a fixed number of questions.
	Quizz.QuestionsLevel = enQuestionsLevel::EasyLevel;
	Quizz.OpType = enOperationType::MixOp;

	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		Quizz.QuestionList[QuestionNumber] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
	}

	AskAndCorrectQuestionListAnswers(Quizz);

	cout << "\nQuiz Completed! Right Answers: " << Quizz.NumberOfRightAnswers
		<< ", Wrong Answers: " << Quizz.NumberOfWrongAnswers << "\n";

	cout << (Quizz.isPass ? "You Passed the Quiz!\n" : "You Failed the Quiz!\n");
}

// Main Function
int main()
{
	srand((unsigned)time(NULL));  // Seed the random number generator.
	PlayMathGame();  // Start the quiz game.
	return 0;  // Exit the program successfully.
}
*/
