#include "AstNodes/Id.h"
#include "AstVisitors/AstVisitor.h"
#include "AstNodes/Import.h"

namespace fun {

using namespace std;

Import::Import(Id* library) :
    m_import(library) {
}

Import::~Import() {
}

void Import::accept(AstVisitor* visitor) {
    visitor->visit(this);
    m_import->accept(visitor);
}

}
