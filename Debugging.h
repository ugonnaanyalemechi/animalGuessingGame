#pragma once
#include "AnimalNode.h"
#include <string>

using std::string;

class Debugging 
{
private:
    bool showFlow = false;
    bool allowShowNodeContents = false;
    bool allowFlowPause = false;
public:
    void pause();
    void show(string, string = "");
    void show(string, int);
    void showNodeContents(string, AnimalNode*);
};