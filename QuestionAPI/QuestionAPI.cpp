#include "QuestionAPI.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
using namespace std;

QuestionModel::QuestionModel(string csvfile) {
  questionVector = vector<Question>();
  ifstream infile(csvfile);
  while (infile) {
    string line;
    if (!getline(infile, line)) {
      break;
    }

    istringstream ss(line);
    Question newQuestion;
    newQuestion.incorrect = vector<string>();
    int entryNum = 0;
    while (ss) {
      string entry;
      if (!getline(ss, entry, ',')) {
        break;
      }
      if (entryNum == 0) {
        newQuestion.question = entry;
      }
      else if (entryNum == 1) {
        newQuestion.correctAnswer = entry;
      }
      else {
        newQuestion.incorrect.push_back(entry);
      }
      entryNum++;
    }
    questionVector.push_back(newQuestion);
  }
}

std::vector<QuestionModel::Question> QuestionModel::Questions() {
  return questionVector;
}

ShuffledQuestion ShuffleAnswers(Question q) {
  std::random_shuffle(q.incorrect.begin(),q.incorrect.end());
  srand(time(NULL));

  ShuffledQuestion shuffleQ;
  shuffleQ.question = q.question;
  shuffleQ.correctAnswer = rand() % q.incorrect.size();
  int index = 0;
  while (index < q.incorrect.size()) {
    if (index == shuffleQ.correctAnswer) {
      shuffleQ.answers.push_back(q.correctAnswer);
    }
    else {
      shuffleQ.answers.push_back(q.incorrect[index]);
      index++;
    }
  }

  return shuffleQ;
}
