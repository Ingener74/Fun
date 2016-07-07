# Test Fun language script
# 

import Jupiter
import So
import Dll

foo = 42 + 21 - 3 * 2 / 3
bar = 54

quz = 65
quuuuz = 123

piConstant = 3.1415

hasHead = true

hasThirdLeg = false

loremImsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit."

print foo

fun test1 ( bla1 )
    t1 = 100500
    t2 = 42
end

fun test2 (bla2, bla3, bla4) b1 = 100 b2=2 end

fun test3 (bla5, bla6, bla7, bla8) end

fun quzMore()
    print foo
end

fun quzLess()

    i = 10
    
    while i > 0:
        print i
    end

    print quuuuz
end

fun testFunction(x, y)
    quz_res
    if quz > 100:
        quz_res = quzMore(x)
    else
        quz_res = quzLess(y)
    end
    
    tf = 52345
    
    print x
    print y
    print tf
    
    ret quz_res
end

fun testExc(t)
    try
        if t:
            throw "if t"
        else
            throw "it not t"
        end
    catch Exception as e:
        print "caugth error " + e
    end

    try
        if true:
            throw "if true"
        else
            throw "if false"
        end
    catch IOError, RuntimeError as e:
        print e
    end
end

testFunction(100, 200)

class TestClass
    fun init(self, test)
        self.m_test = test
        self.copy("one hundred is ", 100)
    end
    
    fun copy(self, arg1, arg2)
        print arg1 + arg2
    end
end

fun main()
    print "main"
end

if isProgram:
    main()
end

