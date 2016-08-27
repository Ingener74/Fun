
print "Test 1"
while nil:
	print "Test 1 failed"
end

print ""
print "Test 2"
foo = 10
while foo:
	print foo
	foo = foo - 1
end
print foo

print ""
print "Test 3"
foo = 10
while foo:
	if foo < 5: break end
	print foo
	foo = foo - 1
end
print foo

print ""
print "Test 4"
bar = 10
while bar:
	t = bar % 2
	print "t = " + t 
	if t: 
		bar = bar - 1
		continue
	else
		bar = bar - 1
	end
	print "bar = " + bar
end
print bar

print ""
print "Test 5"
bar = 10
while bar >= 0:
	if bar % 2: 
		print "bar = " + bar + ", bar/2 = " + bar / 2 + ", bar%2 = " + bar % 2
		bar = bar - 1
		continue
	elif bar % 3:
		print "bar = " + bar + ", bar/3 = " + bar / 3 + ", bar%3 = " + bar % 3
		bar = bar - 1
		continue
	else
		print "bar = " + bar
		bar = bar - 1
	end
end
print bar

