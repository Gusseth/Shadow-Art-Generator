// Shadow Art Generator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <regex>
#include "png/PNG.h"
#include "ShadowGenerator.h"
using namespace std;
using namespace png;
using namespace SAG;

int main()
{
    cout << endl << "==== [ SAG: Shadow Art Generator ] ====" << endl << endl;

    bool loop = true;
    while (loop) {
        PNG* image = new PNG();
        string fileName;
        double threshold = NULL;
        double alphaThreshold = NULL;
        bool invert;

        // Set file name
        while (true) {
            cout << "Please include the file name to be monochromed, (.png only! Include .png in the name): " << endl
                << "File name?: ";
            cin >> fileName;
            if (image->readFromFile(fileName)) break;
            cout << "Invalid file! Try again." << endl;
            cin.clear();
        }

        // Set luminance threshold
        while (true) {
            cout << "Set the luminance threshold value demarcating which is the fore/background (default: 0.25, 0 for transparent backgrounds): " << endl
                << "Luminance threshold?: ";
            cin >> threshold;
            if (!cin.fail() && threshold >= 0 && threshold <= 1) break;
            cout << "Invalid input! Try again." << endl;
            cin.clear();
        }

        // Set alpha threshold
        while (true) {
            cout << "Set the alpha threshold value demarcating which lowest alpha value is acceptable for the foreground, otherwise becomes background (default: 0.25): " << endl
                << "Alpha threshold?: ";
            cin >> alphaThreshold;
            if (!cin.fail() && alphaThreshold >= 0 && alphaThreshold <= 1) break;
            cout << "Invalid input! Try again." << endl;
            cin.clear();
        }

        // Set invert
        while (true) {
            cout << "Would you like to invert the colours?: "
                << endl << "   1 - Black background | White foreground "
                << endl << "   0 - White background | Black foreground "
                << endl << "Invert colours?: ";
            cin >> invert;
            if (!cin.fail()) break;
            cout << "Invalid input! Try again." << endl;
            cin.clear();
        }
        cout << "Generating image..." << endl;

        ShadowGenerator* generator = new ShadowGenerator(*image, threshold, invert, alphaThreshold);
        generator->Render();
        generator->RenderToImage(*image);

        // Remove .png at the end
        fileName.pop_back();
        fileName.pop_back();
        fileName.pop_back();
        fileName.pop_back();
        fileName += "+apple.png";
        image->writeToFile(fileName);
        delete generator;
        delete image;

        bool tryAgain;

        cout << "Image saved as " << fileName << '.' << endl << endl;
        cout << "Please input 1 if you want to create another image: ";
        cin >> tryAgain;
        if (cin.fail() || !tryAgain) {
            loop = false;
            cout << "Quitting...";
            exit(0);
        }
        cout << endl << "==== [ IMAGE 2 ] ====" << endl;
    }

    return -1;
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
