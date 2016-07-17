
fun test1()end
fun test2()
end

fun test3()
	if 1>0:
		fun test3_inside()
			print "test 3 inside"
		end
		test3_inside()
	end
end

fun test4()
	ret 0
end

fun test5()
	throw Error("error")
end
