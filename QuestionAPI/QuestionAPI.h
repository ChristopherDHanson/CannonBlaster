#ifndef QUESTION_API
#define QUESTION_API

#include <string>
#include <vector>

class QuestionModel {
  private:
    std::vector<QuestionModel::Question> questionVector;

  public:
    struct Question {
      std::string question;
      std::string correctAnswer;
      std::vector<std::string> incorrect;
    };
    struct ShuffledQuestion {
        std::string question;
        std::vector<std::string> answers;
        int correctAnswer;
    };
    QuestionModel(std::string csvfile);
    std::vector<QuestionModel::Question> Questions();
    ShuffledQuestion ShuffleAnswers(Question q);
};

#endif
