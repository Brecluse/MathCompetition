#ifndef RECORD_H
#define RECORD_H

#include <fstream>
#include <vector>
#include "question.h"

using namespace std;

struct QuestionRecord {
  Question question;
  bool correct;

  explicit QuestionRecord()
    : question(), correct(false) {};

  explicit QuestionRecord(const Question &question, bool correct)
    : question(question), correct(correct) {};

  void serialize(ofstream &stream) const;

  void deserialize(ifstream &stream);
};

struct Record {
  int score;
  int elapsedTime;
  vector<QuestionRecord> answered;

  Record() : score(0), elapsedTime(0) {};

  explicit Record(
    int scoreValue,
    int elapsedTimeValue,
    const vector<QuestionRecord> &questions
  ) : score(scoreValue), elapsedTime(elapsedTimeValue), answered(questions) {}

  Record operator+(const Record &other) const {
    vector<QuestionRecord> totalQuestions = answered;
    totalQuestions.insert(totalQuestions.end(), other.answered.begin(), other.answered.end());
    return Record(score + other.score, elapsedTime + other.elapsedTime, totalQuestions);
  }

  void serialize(ofstream &stream) const;

  void deserialize(ifstream &stream);

  static void saveToFile(const vector<Record> &records, const std::string &filename);

  static void readFromFile(vector<Record> &records, const std::string &filename);
};

#endif /* RECORD_H */
