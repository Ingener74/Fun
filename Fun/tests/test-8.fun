
fun test1()end

test1()

fun test2()
end

test2()

fun test3()
	if 1>0:
		fun test3_inside()
			print "test 3 inside"
		end
		test3_inside()
	end
end

test3()

fun test4()
	ret 0
end

test4()

fun test5()
	throw Error("error")
end

test5()

foo[0] = "foo"
foo[1] = 1
foo[2] = 3.1415
foo[3] = "bar"
