// Shadow Art Generator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "png/PNG.h"
#include "ShadowGenerator.h"
using namespace std;
using namespace png;
using namespace SAG;

int main()
{
    bool loop = true;
    while (loop) {
        PNG image;
        string fileName;
        while (true) {
            cout << "Please include the file name to be monochromed, (.png only! Include .png in the name): ";
            cin >> fileName;
            if (image.readFromFile(fileName)) break;
            cout << "Invalid file! Try again." << endl;
        }
        while (true) {
            cout << "Would you like to set the threshold value?";
            cin >> fileName;
            if (image.readFromFile(fileName)) break;
        }

        ShadowGenerator* generator = new ShadowGenerator(image);
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
