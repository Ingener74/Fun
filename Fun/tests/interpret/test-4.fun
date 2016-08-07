
fun test1()
	print "Test 1 success"
end

test1()

fun test2(foo)
	print "Test 2 " + foo
end

test2("success")

fun test3()
	print "Test 3 success"
	ret 42
end

print "call test 3"

foo = test3()

print "foo = " + foo

print "Function tests"

