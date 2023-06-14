#include "user.h"

void User::serialize(ofstream &stream) const
{
    // Serialize the struct into a binary stream
    stream.write(username.c_str(), username.size() + 1);                 // Write username including null terminator
    stream.write(reinterpret_cast<const char *>(&grade), sizeof(grade)); // Write grade
    stream.write(school.c_str(), school.size() + 1);                     // Write school including null terminator
}

void User::deserialize(ifstream &stream)
{
    // Deserialize the struct from a binary stream
    char buffer[256];
    stream.read(buffer, sizeof(buffer)); // Read username
    username = buffer;
    stream.read(reinterpret_cast<char *>(&grade), sizeof(grade)); // Read grade
    stream.read(buffer, sizeof(buffer));                          // Read school
    school = buffer;
}

void User::saveToFile(const vector<User> &users, const string &filename)
{
    // Save the vector of User structs to a file
    ofstream file(filename.c_str(), ios::binary);
    if (file.is_open())
    {
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

void User::readFromFile(vector<User> &users, const string &filename)
{
    // Read the vector of User structs from a file
    ifstream file(filename.c_str(), ios::binary);
    if (file.is_open())
    {
        // Read the number of users in the vector
        size_t numUsers;
        file.read(reinterpret_cast<char *>(&numUsers), sizeof(numUsers));

        // Clear the existing users vector
        users.clear();

        // Deserialize and read each user from the file
        for (size_t i = 0; i < numUsers; ++i)
        {
            User user;
            user.deserialize(file);
            users.push_back(user);
        }

        file.close();
    }
}
