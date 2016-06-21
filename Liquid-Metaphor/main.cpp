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

        FunLexer lexer(&file);
        FunParser parser(lexer);
        parser.set_debug_level(argc > 2);
        parser.parse();

        Printer pv;

        Node::root->accept(&pv);

        return 0;
    } catch (const std::exception& e) {
        cerr << "error: " << e.what() << endl;
        return 1;
    }
}
