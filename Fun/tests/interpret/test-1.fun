
foo = true

if foo:
	print "Test 1 success"
end

bar = 10

if bar:
	print "Test 2 success"
end

if bar > 5:
	print "Test 3 success"
end

if bar < 15:
	print "Test 4 success"
end

if bar < 5:
	print "Test 5 fail"
else
	print "Test 5 success"
end

if bar > 15:
	print "Test 6 fail"
elif bar > 7:
	print "Test 6 success"
else
	print "Test 6 fail"
end

if bar > 15:
	print "Test 7 fail"
elif bar > 12:
	print "Test 7 fail"
elif bar > 8:
	print "Test 7 success"
else
	print "Test 7 fail"
end

if bar > 15:
	print "Test 8 fail"
elif bar > 12:
	print "Test 8 fail"
elif bar > 11:
	print "Test 8 fail"
elif bar > 8:
	print "Test 8 success"
else
	print "Test 8 fail"
end

foo = "Test 9"
if foo == "Test 1":
	print "Test 9 fail"
elif foo == "Test 2":
	print "Test 9 fail"
elif foo == "Test 3":
	print "Test 9 fail"
elif foo == "Test 9":
	print "Test 9 success"
else
	print "Test 9 fail"
end

if true:
	print "Test 10 success"
end

if false:
	print "Test 11 fail"
else
	print "Test 11 success"
end

if 0:
	print "Test 12 fail"
else
	print "Test 12 success"
end

if 1:
	print "Test 13 success"
else
	print "Test 13 fail"
end

if 0.0:
	print "Test 14 fail"
else
	print "Test 14 success"
end		

if 1.0:
	print "Test 15 success"
else
	print "Test 15 fail"
end		

if nil:
	print "Test 16 fail"
else
	print "Test 16 success"
end

if "":
	print "Test 17 fail"
else
	print "Test 17 success"
end

if "Test 18":
	print "Test 18 success"
else
	print "Test 18 fail"
end

print ""
if true:
	foo = 42
	print "foo = " + foo
else
	print "bar"
end














