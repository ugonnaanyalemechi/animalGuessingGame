#include "Debugging.h"
#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

void Debugging::pause() {
    if (allowFlowPause)
        system("pause");
}

void Debugging::show(string msg1, string msg2) { // displays message (has ability to have two differnt messages)
    if (showFlow) {
        if (msg2 != "")
            cout << "*** " << msg1 << ": " << msg2 << " ***\n";
        else
            cout << "*** " << msg1 << " ***\n";
    }
}

void Debugging::show(string msg, int num) { // displays message and value
    if (showFlow)
        cout << "*** " << msg << ": " << num << " ***\n";
}

void Debugging::showNodeContents(string nodeName, AnimalNode* node) {
    if (allowShowNodeContents) {
        cout << "\n-------------------------------------------\n";
        cout << setw(20) << "*** Contents of " << nodeName << " ***\n";
        cout << "-------------------------------------------\n";
        cout << "*** " << nodeName << "'s question: " << node->question << "\n";
        cout << "*** " << nodeName << "'s animal: " << node->animal << "\n";
        cout << "*** " << nodeName << "'s yes answer points to: " << node->yesAns << "\n";
        cout << "*** " << nodeName << "'s no answer points to: " << node->noAns << "\n\n";
    }
}