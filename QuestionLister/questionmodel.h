#ifndef QUESTIONMODEL_H
#define QUESTIONMODEL_H
#include <string>
#include <vector>


class QuestionModel {
    struct Question {
        std::string title;
        std::vector<std::string> correct;
        std::vector<std::string> incorrect;
    };

    private:
        std::vector<Question> questions;

    public:
        void AddQuestion();
        void UpdateQuestion(int index, std::string newTitle);
        void RemoveQuestion(int index);

        void AddCorrectAnswer(int questionIndex, std::string answer);
        void UpdateCorrectAnswer(int questionIndex, int answerIndex, std::string newAnswer);
        void RemoveCorrectAnswer(int questionIndex, int answerIndex);

        void AddIncorrectAnswer(int questionIndex, std::string answer);
        void UpdateIncorrectAnswer(int questionIndex, int answerIndex, std::string newAnswer);
        void RemoveIncorrectAnswer(int questionIndex, int answerIndex);
};

#endif
