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

QuestionModel::ShuffledQuestion QuestionModel::ShuffleAnswers(Question q, int answerCount) {
  ShuffledQuestion shuffleQ;
  shuffleQ.answers = vector<string>();

  vector<string> incorrect = q.incorrect;
  srand(time(NULL));

  std::random_shuffle(incorrect.begin(),incorrect.end());
  shuffleQ.question = q.question;
  shuffleQ.correctAnswer = rand() % min(answerCount, (int)incorrect.size());
  int index = 0;
  bool passedCorrect = false;
  while (shuffleQ.answers.size() < min(answerCount, (int)incorrect.size())) {
    if (index == shuffleQ.correctAnswer) {
      shuffleQ.answers.push_back(q.correctAnswer);
      passedCorrect = true;
    }
    else {
      shuffleQ.answers.push_back(incorrect[index-(passedCorrect?1:0)]);
    }
    index++;
  }

  return shuffleQ;
}
