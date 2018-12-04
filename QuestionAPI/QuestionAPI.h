#ifndef QUESTION_API
#define QUESTION_API

#include <string>
#include <vector>

class QuestionModel {
  struct Question {
    std::string question;
    std::vector<std::string> correct;
    std::vector<std::string> incorrect;
  };

  public:
    QuestionModel(std::string csvfile);
    std::vector<Question> Questions();
};

#endif
