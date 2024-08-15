#pragma once
#include <string>

using std::string;

struct AnimalNode {
    string question;
    string animal;
    AnimalNode* yesAns = nullptr;
    AnimalNode* noAns = nullptr;
};