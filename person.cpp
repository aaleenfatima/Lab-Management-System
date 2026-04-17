#include "person.h"
#include <fstream>  
#include <string>   
#include <iostream>
using namespace std;

Person::Person(const string& id, const string& name, const string& email)
    : id(id), name(name), email(email) {
}

void Person::serialize(ofstream& out) const {
    // Check if stream is good before writing
    if (!out.good()) return;

    size_t len = id.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(id.c_str(), len);

    len = name.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(name.c_str(), len);

    len = email.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(email.c_str(), len);
}

void Person::deserialize(ifstream& in) {
    // Check if stream is good before reading
    if (!in.good()) return;

    size_t len;

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (in.good()) {
        id.resize(len);
        in.read(&id[0], len);
    }

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (in.good()) {
        name.resize(len);
        in.read(&name[0], len);
    }

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (in.good()) {
        email.resize(len);
        in.read(&email[0], len);
    }
}