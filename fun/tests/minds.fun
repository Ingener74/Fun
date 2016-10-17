# integrated modules
# * math
# * fs
# * system
# * thread
# * json
# * net
# * native
# * gl
# * glut
# * sqlite
# * xml
# * gui
# * debug
# * 

# c function call over native module
result = native.ccall("c_function_name_add", 10, 20)

# if and for expression like in python
foo = foo else 20

foo = 10 if x < 10 else 20

foo = 10 if x < 10 else 
	  20 if x < 20 else 30

foo = 10 if x < 10 else 
	  20 if x < 20 else 
	  30 if x < 30 else 40

bar = [x + 1 for x = 0; x < 10; x++]

foo5 = [0:2:100]

bar = range(0, 10)     # generator
foo = range(0, 2, 100) # generator

for i in range(0, 100):
	print "i = " + i
end

for i in [0:100]:
	print "i = " + i
end

foo6 = [x * 2 for x in foo5]

# dictionary to variables
x, y = {
	x = 10,
	y = 20,
}
assert(x == 10)
assert(y == 20)

# dictionary example
dictionaryExample = {
	integerField   = 42
	realField      = 3.1415
	functionField  = fun(self) ret "real field " + self.realField end
	booleanField   = false
	objectField    = Dog("Barky")
	stringField    = "Mac OS"
	nilField       = nil
}

print "dict function field return " + dictionaryExample.functionField()

class TaskQueue
	fun __init__(self)
		self.processList = {
			firstWork = fun()
				print "do hard work"
				sleepSec(3)
			end
		}
		self.isWork = true
		self.th = thread.create(self)
	end

	fun __call__(self)
		isw
		lock(self.isWork) isw = self.isWork end
		while isw:
			proc
			lock(self.processList) 
				while self.processList.len() <= 0 and isw:
					self.processList.wait()
				end
				if self.processList.len() <= 0:
					continue
				end
				proc = self.processList[0] 
				self.processList.remove(0)
			end
			proc()
		end
	end

	fun addWork(self, work)
		lock(self.processList)
			self.processList.append(work)
			self.processList.notifyOne()
		end
		ret self
	end

	fun stop(self)
		lock(self.isWork)
			self.isWork = false
		end
		self.processList.notifyOne()
		if self.th.isJoinable():
			self.th.join()
		end
	end
end

threadBody = TaskQueue().addWork(fun()
	i = 100
	while i > 0:
		print "hui 100 raz"
		i -= 1
	end
end).addWork(fun()
	print "Boo"
end)

thread.create(fun() 
	while true:
	end
end)

# type module type transform
int()
real()
str()
bool()

# debug module
debug.stacktrace()
debug.breakpoint()


file = fs.open("test", fun() end)


# __call__
# __init__
# __copy__
# __dict__
# __add__
# __sub__
# __str__
# __mul__
# __div__
# __adda__
# __suba__
# __mula__
# __diva__
# __mod__
# __moda__

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

    fun __str__(self)
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

try
    foo = 42
catch Exception as e:
    print "error: " + e
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

l1 = "test string".len()
assert(l1 == 11)

l2 = "test string".sub(2, 5)
assert(l2 == "st st")

l3 = "test".toUpper()
assert(l3 == "TEST")

l4 = "3.1415".float()
assert(l4 == 3.1415)

l5 = "format %s - %d - %f".format("test", 42, 3.1415)
assert(l5 == "format test - 42 - 3.1415")


d1 = {
	x = 10
	y = 10
}
a1 = d1.len()
assert(a1 == 2)

a2 = d1.x.float()
assert(a2 == 10.0)

a3 = d1.y.str()
assert(a3 == "10")

a4 = (d1.x + d1.y).str()
assert(a4 == "20")

class Floor()
	fun __init__()
		self.b = 42
	end
end

# add method to class
Floor.down = fun(self)
	ret self.b - 100
end

# create object of class Floor
f1 = Floor()
print "floor down: " + f1.down()

# add method to object
f1.up = fun(self)
	ret self.b + 100
end

print "floor up: " + f1.up()

# pass unnamed class devided from another as callback
class CallbackInterface()
	fun callback(self)
		throw NotImplementedError()
	end
end

data1 = "Data"

fun(callback)
	if true:
		callback.callback()
	end
end(class(CallbackInterface)
	fun __init__(self, data)
		self._data = nil
	end
	fun callback(self)
		print "callback " + self._data
	end
end(data1))

# function default parameters
fun f1(a, b, c = 1000)
	ret a, b, c
end

r1, r2, r3 = f1(10, 100)
assert(r1 == 10)
assert(r2 == 100)
assert(r3 == 1000)

# function variadic parameters
fun f2(a, b, ...)
	print a
	print b
	for i in ...:
		print i
	end
	for i = 0; i < ....len(); ++i: # are you sure about that???
	end
end

# threads
# first thread wait a value and used after
lock(var1)
	while !var1:
		var1.wait()
	end
	# use var1
end

# second thread get value for var1 and signal another
var2 = getB()
lock(var1)
	var1 = var2
	var1.signal()
end

# math
math.sin(10)
math.cos()
math.atan2()
math.atan()

# fs
f1 = fs.open("file.txt", fun(content) 
	print "content: " + content 
end)

f1 = fs.open("file.txt", ->content:
	print "content: " + content 
;)

data2 = f1.read()

f1.close()

b1 = fs.fileExist("file.txt")

b2 = fs.isDir("/dir")

# sys
sys.argv
sys.os()

# thread
thread.create(fun() end)
thread.create(->;)

# json
json.encode({
	test = 42
	f1 = 3.1415
})
json.decode("{\"test\": 42}")

# net
req1 = net.request("www.api-server.com")
ws1 = net.websocket("ws://api-server.com", fun(text) end, fun(binary) end, fun(error) end)
ws1 = net.websocket("ws://api-server.com", ->text:;, ->binary:;, ->error:;)

# native
lib1 = native.loadLibrary("./libApi.{so, dll, dylib}")
fi1 = native.create(lib1.getFunction("c_function"), native.pointer, {
	arg1 = native.int32
	arg2 = native.float32
})
res1 = native.call(fi1, {42, 3.1415})

# * gl
# * glut
# * sqlite
# * xml
# * gui
# debug
debug.backtrace()
debug.breakpoint()

# addtional function definition
test = -> a, b:
	print "a + b = " + (a + b) 
;

test = fun(a, b) 
	print "a + b = " + (a + b) 
end

test(1, 2)

doHardWork(->print "work done";)

result = nil
doHardWork(->res result = res;)

a = {
	0 = "Zero"
	1 = "One"
}[0]

if true
	b
;

a = 1
b = if a == 1 2 else 4;

math = import("math")
json = import("json")

custom = import("custom")


