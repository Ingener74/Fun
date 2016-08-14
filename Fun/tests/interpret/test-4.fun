
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
	print "Test 7 success \n" + f()
end(fun()
	ret "Test 8 success "
end)

print "Test 9 " + fun()
	ret "success"
end()

fun()
	ret fun() print "Test 10 success" end
end()()

fun()
	ret fun(a) print "Test 11 " + a end
end()("success")

# a = 40
# fun test12(foo)
# 	ret a + foo
# end
# 
# fun test13(bar)
# 	ret test12(bar)
# end
# 
# if test13(40) == 80:
# 	print "Test 13 success"
# else
# 	print "Test 13 fail"
# end

# recursion
fun test14(a)
	if a < 10:
		print "a = " + a
		test14(a + 1)
	end
end
test14(0)

# not work yet
fun fib(n)
	if n > 2:
		ret (fib(n - 1) + fib(n - 2))
	else
		ret 1
	end
end

for i = 0; i < 12; i = i + 1:
	print "fib(" + i + ") = " + fib(i)
end
