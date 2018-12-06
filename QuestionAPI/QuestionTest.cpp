#include "QuestionAPI.h"
#include <vector>
#include <iostream>
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
  if (argc == 2) {
    QuestionModel model = QuestionModel(argv[1]);
    for (int i=0; i < model.Questions().size(); i++) {
      QuestionModel::ShuffledQuestion sq = model.ShuffleAnswers(model.Questions()[i]);
      cout << sq.question << endl;
      for (int j=0; j < sq.answers.size(); j++) {
        cout << (sq.correctAnswer==j?"+ ":"- ") << sq.answers[j] << endl;
      }
      cout << endl;
    }
    return 0;
  }
  else return 1;
}
