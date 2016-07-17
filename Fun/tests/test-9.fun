
try
	foo = 42
	if foo > 20:
		print "foo more 20"
	elif foo > 30:
		print "foo more 30"
	elif foo > 40:
		print "foo more 40"
	elif foo > 50:
		print "foo more 50"
	else
		print "foo less or equal 20"
	end

	throw Error("error")
catch Exception as e:
	print e
end
