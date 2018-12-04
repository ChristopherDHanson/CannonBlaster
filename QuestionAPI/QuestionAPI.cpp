#include "QuestionAPI.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

QuestionModel::QuestionModel(string csvfile) {
  questions = vector<Question>();
  ifstream infile(csvfile);
  while (infile) {
    string line;
    if (!getline(infile, line)) {
      break;
    }

    istringstream ss(line);
    Question newQuestion;
    int entryNum = 0;
    while (ss) {
      string entry;
      if (!getline(ss, entry, ',')) {
        break;
      }
      if (entryNum = 0) {
        newQuestion.question = entry;
      }
      else if (entryNum = 1) {
        newQuestion.correctAnswer = entry;
      }
      else {
        newQuestion.incorrect.push_back(entry);
      }
      entryNum++;
    }
    questions.push_back(newQuestion);
  }
}

QuestionModel::Questions() {
  return questions;
}
