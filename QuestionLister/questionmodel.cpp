#include "questionmodel.h"
#include <string>
#include <vector>

QuestionModel::QuestionModel() {
    questions = std::vector<Question>();
}

//ADD/REMOVE QUESTIONS

void QuestionModel::AddQuestion(std::string newTitle) {
    Question q = Question();
    q.title = newTitle;
    questions.push_back(q);
}

void QuestionModel::UpdateQuestion(int index, std::string newTitle) {
    if (index >= 0 && questions.size()>0) {
        Question q = questions[index];
        q.title = newTitle;
    }
}

void QuestionModel::RemoveQuestion(int index) {
    if (questions.size() > index) {
        questions.erase(questions.begin()+index);
    }
}

//ADD/REMOVE CORRECT ANSWERS

void QuestionModel::AddCorrectAnswer(int questionIndex, std::string answer) {
    Question q = questions[questionIndex];
    q.correct.push_back(answer);
}

void QuestionModel::UpdateCorrectAnswer(int questionIndex, int answerIndex, std::string newAnswer) {
    Question q = questions[questionIndex];
    q.correct[answerIndex] = newAnswer;
}

void QuestionModel::RemoveCorrectAnswer(int questionIndex, int answerIndex) {
    Question q = questions[questionIndex];
    if (q.correct.size() > answerIndex) {
        q.correct.erase(q.correct.begin()+answerIndex);
    }
}

//ADD/REMOVE INCORRECT ANSWERS


void QuestionModel::AddIncorrectAnswer(int questionIndex, std::string answer) {
    Question q = questions[questionIndex];
    q.incorrect.push_back(answer);
}

void QuestionModel::UpdateIncorrectAnswer(int questionIndex, int answerIndex, std::string newAnswer) {
    Question q = questions[questionIndex];
    q.incorrect[answerIndex] = newAnswer;
}

void QuestionModel::RemoveIncorrectAnswer(int questionIndex, int answerIndex) {
    Question q = questions[questionIndex];
    if (q.incorrect.size() > answerIndex) {
        q.incorrect.erase(q.incorrect.begin()+answerIndex);
    }
}

//GET QUESTIONS, ANSWERS

std::vector<std::string> QuestionModel::QuestionNames() {
    std::vector<std::string> names;
    for (auto it = questions.begin(); it != questions.end(); it++) {
        names.push_back(it.base()->title);
    }
    return names;
}

std::vector<std::string> QuestionModel::CorrectAnswers(int questionIndex) {
    std::vector<std::string> answers;
    for (auto it = questions[questionIndex].correct.begin(); it != questions[questionIndex].correct.end(); it++) {
        answers.push_back(*it.base());
    }
    return answers;
}

std::vector<std::string> QuestionModel::IncorrectAnswers(int questionIndex) {
    std::vector<std::string> answers;
    for (auto it = questions[questionIndex].incorrect.begin(); it != questions[questionIndex].incorrect.end(); it++) {
        answers.push_back(*it.base());
    }
    return answers;
}
