#if ! defined ( LECTURE_H )
#define LECTURE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
using namespace std;

class Lecture {

public:
    bool Readfile(const string &fileName, vector <string> &line );

};

#endif //LECTURE_H
