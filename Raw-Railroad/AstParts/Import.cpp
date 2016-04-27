#include <iostream>
#include "Import.h"

using namespace std;

Import::Import(const string& library) {
    cout << __PRETTY_FUNCTION__ << library << endl;
}

Import::~Import() {
}

