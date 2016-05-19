#pragma once

#include <string>
#include "AstNodes/Expr.h"

namespace fun {

class AstVisitor;

class AssignExpr : public Expr {
public:
    AssignExpr(const std::string& id, Expr* value);
    virtual ~AssignExpr();

    virtual std::string toString() const ;

    virtual void visit(AstVisitor*);

    virtual int getResult(){
        return m_value->getResult();
    }

    const std::string& getId() const {
        return m_id;
    }

private:
    std::string m_id;
    Expr* m_value;
};

}
