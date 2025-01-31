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
    bool Readfile(vector <string> &line );
    Lecture(const string &fileName);
    virtual ~Lecture();

private:
    std::fstream file; 

};




#endif //LECTURE_H
