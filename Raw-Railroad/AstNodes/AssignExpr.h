#pragma once

#include <AstNodes/Expr.h>
#include <string>


class AssignExpr : public Expr {
public:
    AssignExpr(const std::string& id, Expr* value);
    virtual ~AssignExpr();

    virtual std::string toString() const ;

    virtual void visit(Fun1Ast*);

    virtual int getResult(){
        return m_value->getResult();
    }

private:
    std::string m_id;
    Expr* m_value;
};
