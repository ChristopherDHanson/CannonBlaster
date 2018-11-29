#include "questionmodel.h"
#include <string>
#include <vector>

void QuestionModel::AddQuestion(std::string newTitle) {
    Question q = Question();
    q.title = newTitle;
    questions.push_back(q);
}

void QuestionModel::UpdateQuestion(int index, std::string newTitle) {
    Question q = questions[index];
    q.title = newTitle;
}

void QuestionModel::RemoveQuestion(int index) {
    questions.erase(questions.begin()+index);
}
