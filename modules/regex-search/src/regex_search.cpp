﻿// Copyright 2017 Kazakov Andrew

#include "include/regex_search.h"

RegexSearch::RegexSearch() {
    regex_ = std::string("");
}

RegexSearch::RegexSearch(const std::string regex) {
    regex_ = regex;
}

RegexSearch::RegexSearch(const RegexSearch& regex) {
    regex_ = regex.regex_;
}

RegexSearch& RegexSearch::operator=(const RegexSearch& regex) {
    regex_ = regex.regex_;

    return *this;
}

void RegexSearch::SetRegex(const std::string regex) {
    regex_ = regex;
}

std::string RegexSearch::GetRegex() const {
    return regex_;
}

RegexSearchResult RegexSearch::Find(std::string str) {
    std::smatch matches;
    std::regex regex(regex_);
    RegexSearchResult res;

    while (std::regex_search(str, matches, regex)) {
        res.push_back(matches.length());
        res.push_back(matches.position());
        str = matches.suffix().str();
    }

    return res;
}

RegexSearchResult RegexSearch::FindInFile(std::string filename) {
    std::smatch matches;
    std::regex regex(regex_);
    RegexSearchResult res;
    std::string str, temp_str;
    std::ifstream file;

    file.open(filename);
    while (std::getline(file, temp_str)) {
        str += temp_str + "\n";
    }
    file.close();

    while (std::regex_search(str, matches, regex)) {
        res.push_back(matches.length());
        res.push_back(matches.position());
        str = matches.suffix().str();
    }

    return res;
}
