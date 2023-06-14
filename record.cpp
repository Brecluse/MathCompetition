#include "record.h"
#include <cstdio>
#include <cstdlib>

void Record::serialize(ofstream &stream) const {
  stream.write(reinterpret_cast<const char *>(&score), sizeof(score));
  stream.write(reinterpret_cast<const char *>(&elapsedTime), sizeof(elapsedTime));
}

void Record::deserialize(ifstream &stream) {
  stream.read(reinterpret_cast<char *>(&score), sizeof(score));
  stream.read(reinterpret_cast<char *>(&elapsedTime), sizeof(elapsedTime));
}

void Record::saveToFile(const std::vector<Record> &records, const std::string &filename) {
  std::ofstream file(filename, std::ios::binary);
  if (file.is_open()) {
    for (size_t i = 0; i < records.size(); i++) {
      records[i].serialize(file);
    }
    file.close();
  }
}

void Record::readFromFile(std::vector<Record> &records, const std::string &filename) {
  std::ifstream file(filename, std::ios::binary);
  if (file.is_open()) {
    while (file.peek() != EOF) {
      Record record;
      record.deserialize(file);
      records.push_back(record);
    }
    file.close();
  }
}
