
i = 10

# while : end # Error: While must have the condition expression

while false: end
while false:end

while false:
end

while i > 0:
	i -= 5
end

i = 20

while i > 0:
	print i
	i -= 1
	break
end

i = 30

while i > 5:
	if i == 10:
		continue
	end
	i -= 3
end
