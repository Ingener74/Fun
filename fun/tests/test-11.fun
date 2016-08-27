
class Animal()

	DOG = 1
	CAT = 2

	fun __init__()
		foo = DOG
		if foo == CAT:
			print "is Cat"
		elif foo == DOG:
			print "is Dog"
		else
			print "is Something else"
		end
	end

	fun __str__()
		class Format()
			fun __init__()
			end

			fun __call__()
			end
		end

		frmt = Format()

		ret "test string" + frmt()
	end
end
