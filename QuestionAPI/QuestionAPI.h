#ifndef QUESTION_API
#define QUESTION_API

#include <string>
#include <vector>

class QuestionModel {
  struct Question {
    std::string question;
    std::string correctAnswer;
    std::vector<std::string> incorrect;
  };

  private:
    std::vector<QuestionModel::Question> questionVector;

  public:
    QuestionModel(std::string csvfile);
    std::vector<QuestionModel::Question> Questions();
};

#endif
