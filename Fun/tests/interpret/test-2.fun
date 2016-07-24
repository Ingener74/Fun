
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


