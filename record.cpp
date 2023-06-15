#include "record.h"
#include <cstdio>

void Record::serialize(ofstream &stream) const {
  stream.write(reinterpret_cast<const char *>(&score), sizeof(score));
  stream.write(reinterpret_cast<const char *>(&elapsedTime), sizeof(elapsedTime));
  // Write the number of answered in the vector
  size_t answersSize = answered.size();
  stream.write(reinterpret_cast<const char *>(&answersSize), sizeof(answersSize));
  // Serialize and write each user in the vector
  for (size_t i = 0; i < answered.size(); ++i) {
    answered[i].serialize(stream);
  }
}

void Record::deserialize(ifstream &stream) {
  stream.read(reinterpret_cast<char *>(&score), sizeof(score));
  stream.read(reinterpret_cast<char *>(&elapsedTime), sizeof(elapsedTime));
  // Read the number of users in the vector
  size_t answersSize;
  stream.read(reinterpret_cast<char *>(&answersSize), sizeof(answersSize));

  // Clear the existing users vector
  answered.clear();

  // Deserialize and read each user from the file
  for (size_t i = 0; i < answersSize; ++i) {
    QuestionRecord answer;
    answer.deserialize(stream);
    answered.push_back(answer);
  }
}

void Record::saveToFile(const vector<Record> &records, const string &filename) {
  ofstream file(filename.c_str(), ios::binary);
  if (file.is_open()) {
    size_t recordSize = records.size();
    file.write(reinterpret_cast<const char *>(&recordSize), sizeof(recordSize));
    for (size_t i = 0; i < records.size(); i++) {
      records[i].serialize(file);
    }
    file.close();
  }
}

void Record::readFromFile(vector<Record> &records, const string &filename) {
  ifstream file(filename.c_str(), ios::binary);
  if (file.is_open()) {
    // Read the number of users in the vector
    size_t recordSize;
    file.read(reinterpret_cast<char *>(&recordSize), sizeof(recordSize));

    // Clear the existing users vector
    records.clear();

    // Deserialize and read each user from the file
    for (size_t i = 0; i < recordSize; ++i) {
      Record record;
      record.deserialize(file);
      records.push_back(record);
    }
    file.close();
  }
}

void QuestionRecord::serialize(std::ofstream &stream) const {
  // Serialize the question
  question.serialize(stream);
  // Write the correct flag
  stream.write(reinterpret_cast<const char*>(&correct), sizeof(correct));
}

void QuestionRecord::deserialize(std::ifstream &stream) {
  // Deserialize the question
  question.deserialize(stream);
  // Read the correct flag
  stream.read(reinterpret_cast<char*>(&correct), sizeof(correct));
}
