#pragma once

#include <FlexLexer.h>

class MyLexer : public yyFlexLexer {
public:
    MyLexer();
    virtual ~MyLexer();
};
