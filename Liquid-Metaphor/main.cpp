#include <iostream>
#include <fstream>
#include <stdexcept>

#include <FunAst.h>
#include <AstVisitors/PrintVisitor.h>
#include <AstNodes/Scope.h>

using namespace std;
using namespace fun;

int main(int argc, char* argv[]) {
    try {
        if (argc < 2)
            throw std::runtime_error("no files");

        ifstream file(argv[1]);

        FunAst ast;

        if (argc > 2)
            ast.parse(file, true);
        else
            ast.parse(file, false);

        PrintVisitor pv;

        ast.getScope()->accept(&pv);

        return 0;
    } catch (const std::exception& e) {
        cerr << "error: " << e.what() << endl;
        return 1;
    }
}
