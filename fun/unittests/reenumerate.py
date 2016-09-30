#!/usr/bin/env python
import re

i = 2

regex = re.compile(r"Assign, [0-9]+", re.IGNORECASE)

lines = [line.rstrip('\n') for line in open('test-assign.cpp')]

for line in lines:
    changes = regex.subn("Assign, %d" % i, line)
    if changes[1] > 0:
		i += 1
    print changes[0]

