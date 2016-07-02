#include <iostream>
#include <fstream>
#include <stdexcept>

#include <FunLexer.h>
#include <Nodes.h>
#include <Printer.h>

using namespace std;
using namespace fun;

int main(int argc, char* argv[]) {
    try {
        if (argc < 2)
            throw std::runtime_error("no files");

        ifstream file(argv[1]);

        if (!file.is_open())
            throw std::runtime_error(string("can't open file ") + string(argv[1]));

        Statement::clear();
        FunLexer lexer(&file);
        FunParser parser(lexer);
        parser.set_debug_level(argc > 2);
        parser.parse();

        Printer pv;

        int result = Statement::apply(&pv);

        Statement::clear();

        return result;
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
}
