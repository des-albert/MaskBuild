//
// MaskBuild.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "WordStore.h"

int main()
{
    WordStore * ws = new WordStore;

    if (ws->Open())
    {
        cout << "Open File Success " << endl;

        ws->Sort();

        ws->Close();
    }
    else
        cout << " Open File Failed " << endl;
    delete ws;
}

