#include "QuestionAPI.h"
#include <vector>
#include <iostream>
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
  if (argc == 2) {
    QuestionModel model = QuestionModel(argv[1]);
    for (int i=0; i < model.Questions().size(); i++) {
      cout << model.Questions()[i].question
        << " (" + model.Questions()[i].correctAnswer + "):" << endl;
      for (int j=0; j < model.Questions()[i].incorrect.size(); j++) {
        cout << "- " << model.Questions()[i].incorrect[j] << endl;
      }
      cout << endl;
    }
    return 0;
  }
  else return 1;
}
