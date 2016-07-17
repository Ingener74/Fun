
class Animal()

	DOG = 1
	CAT = 2

	fun init()
		foo = DOG
		if foo == CAT:
			print "is Cat"
		elif foo == DOG:
			print "is Dog"
		else
			print "is Something else"
		end
	end

	fun str()

		class Format()
			fun init()
			end
		end

		frmt = Format()

		ret "test string" + frmt()
	end
end
