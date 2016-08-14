
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
