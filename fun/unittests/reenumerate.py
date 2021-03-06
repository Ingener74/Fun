#!/usr/bin/env python
import re


def reenumerate(filename, in_template, out_template):

	regex = re.compile(in_template, re.IGNORECASE)

	i = 1
	in_lines = [line.rstrip('\n') for line in open(filename)]
	out_lines = []

	for line in in_lines:
	    changes = regex.subn(out_template % i, line)
	    if changes[1] > 0:
			i += 1
	    out_lines.append(changes[0])

	with open(filename, 'wr') as f:
		for line in out_lines:
			f.write(line + '\n')

reenumerate('test-assign.cpp', r"Assign, [0-9]+", "Assign, %d")
reenumerate('test-binary-ops.cpp', r"BinaryOp, [0-9]+", "BinaryOp, %d")
