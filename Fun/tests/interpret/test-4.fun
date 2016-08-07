
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

test4 = fun(a) 
	print "Test 4 success " + a
	ret a + 43
end

bar = test4(foo)

print "bar = " + bar

fun()
	print "Test 5 success"
end()

fun(b)
	print "Test 6 success " + b
end(bar)

fun(f)
	print "Test 7 success " + f()
end(fun()
	ret "Test 8 success "
end)

print "Test 9 " + fun()
	ret "success"
end()

print "Function tests"

