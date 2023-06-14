#include "user.h"

void User::serialize(ofstream &stream) const {
  size_t usernameSize = username.size();
  stream.write(reinterpret_cast<const char *>(&usernameSize), sizeof(usernameSize));
  stream.write(username.c_str(), usernameSize);

  stream.write(reinterpret_cast<const char *>(&grade), sizeof(grade));

  size_t schoolSize = school.size();
  stream.write(reinterpret_cast<const char *>(&schoolSize), sizeof(schoolSize));
  stream.write(school.c_str(), schoolSize);
}

void User::deserialize(ifstream &stream) {
  size_t usernameSize;
  stream.read(reinterpret_cast<char *>(&usernameSize), sizeof(usernameSize));
  username.resize(usernameSize);
  stream.read(const_cast<char *>(username.data()), usernameSize);

  stream.read(reinterpret_cast<char *>(&grade), sizeof(grade));

  size_t schoolSize;
  stream.read(reinterpret_cast<char *>(&schoolSize), sizeof(schoolSize));
  school.resize(schoolSize);
  stream.read(const_cast<char *>(school.data()), schoolSize);
}

void User::saveToFile(const vector <User> &users, const string &filename) {
  // Save the vector of User structs to a file
  ofstream file(filename.c_str(), ios::binary);
  if (file.is_open()) {
    // Write the number of users in the vector
    size_t numUsers = users.size();
    file.write(reinterpret_cast<const char *>(&numUsers), sizeof(numUsers));

    // Serialize and write each user in the vector
    for (size_t i = 0; i < users.size(); ++i) {
      users[i].serialize(file);
    }

    file.close();
  }
}

void User::readFromFile(vector <User> &users, const string &filename) {
  // Read the vector of User structs from a file
  ifstream file(filename.c_str(), ios::binary);
  if (file.is_open()) {
    // Read the number of users in the vector
    size_t numUsers;
    file.read(reinterpret_cast<char *>(&numUsers), sizeof(numUsers));

    // Clear the existing users vector
    users.clear();

    // Deserialize and read each user from the file
    for (size_t i = 0; i < numUsers; ++i) {
      User user;
      user.deserialize(file);
      users.push_back(user);
    }

    file.close();
  }
}
