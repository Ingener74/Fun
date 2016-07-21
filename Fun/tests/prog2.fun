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
    fun __init__(self, test)
        self.m_test = test
        self.copy("one hundred is ", 100)
    end
    
    fun __copy__(self, other)
    end
end

fun main()
    print "main"
end

if isProgram:
    main()
end

class Animal
    fun __init__(self)
        self.animal_type = ""
    end

    fun print(self)
        print "Animal: " + self._animal_type
    end

    fun __str__()
        throw NotImplementedError()
    end
end

class Cat(Animal)
    fun __init(self)
        super.__init__(self)
        self.animal_type = "Cat"
    end
end

class Dog(Animal)
    fun __init(self)
        super.__init__(self)
        self.animal_type = "Dog"
    end
end

dog = Dog()

dog.print()

dictionaryExample = {
    integerField  = 42,
    realField     = 3.1415,
    booleanField  = false,
    stringField   = "foo bar"
    nilField      = nil,
    objectField   = Dog(),
    functionField = fun()end,
}

try
    foo = 42
catch Exception as e:
    print "error: " + e
end

# integrated modules
# * math
# * thread
# * net
# * json
# * xml
# * 