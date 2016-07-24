
print "Test 1"
for i = 0; i < 10; nil:
	print "i = " + i
	i = i + 1
end

print ""
print "Test 2"
for i = 0; i < 10; nil:
	print "i = " + i

	if i > 5:
		print "test 2 break"
		break
	end

	i = i + 1
end

print ""
print "Test 3"
for i = 0; i < 10; nil:
	if i > 5:
		print "test 3 break on i == " + i
		break
	end

	i = i + 1
	continue

	print "i = " + i
end

