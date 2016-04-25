#include <iostream>
#include <fstream>
#include <stdexcept>

#include "MyAst.h"

using namespace std;

int main(int argc, char* argv[]) {
    try {
        if (argc < 2)
            throw std::runtime_error("no files");

        ifstream file(argv[1]);

        MyAst ast;
        ast.parse(file);

        return 0;
    } catch (const std::exception& e) {
        cerr << "error: " << e.what() << endl;
        return 1;
    }
}
