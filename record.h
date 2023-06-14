#ifndef RECORD_H
#define RECORD_H

#include <fstream>
#include <vector>

using namespace std;

struct Record {
  int score;
  int elapsedTime;

  explicit Record(int scoreValue = 0, int elapsedTimeValue = 0)
    : score(scoreValue), elapsedTime(elapsedTimeValue) {}

  Record operator+(const Record &other) const {
    return Record(score + other.score, elapsedTime + other.elapsedTime);
  }

  void serialize(ofstream &stream) const;

  void deserialize(ifstream &stream);

  static void saveToFile(const vector<Record> &records, const std::string &filename);

  static void readFromFile(vector<Record> &records, const std::string &filename);
};

#endif /* RECORD_H */
