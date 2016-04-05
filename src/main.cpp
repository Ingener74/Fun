//
// Created by pavel on 05.04.16.
//

#include <iostream>
#include <stdexcept>

using namespace std;

int main(int argc, char *argv[]) {
    try {

    } catch (const exception &e) {
        cerr << e.what() << endl;
    }
}