#include "MyUtil.hpp"

string MyUtil::myTrim(string str) {
    int beg = str.find_first_not_of(" \t");
    int end = str.find_last_not_of(" \t");
    int range = end - beg + 1;
    return str.substr(beg, range);
}

string MyUtil::leftNewLineTrim(std::string str) {
    int beg = str.find_first_not_of("\n");
    int range = str.length() - beg - 1;
    return str.substr(beg, range);
}