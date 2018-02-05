#!/usr/bin/env python3

import random
import string
import sys

def main():
	if len(sys.argv) == 1:
		print("Usage: [test count]")
		return
	else:
		count = int(sys.argv[1])
	allOperation = "+-/*<>=^";
	inFile = open("inTests.txt", "w", encoding="utf8")
	outFile = open("outTests.txt", "w", encoding="utf8")
	for _ in range(0, count):
		number1 = random.getrandbits(random.randint(1, 500))
		number2 = random.getrandbits(random.randint(1, 500))
		operation = random.choice(allOperation);
		if operation == "+":
			res = number1 + number2
			outFile.write(str(res) + '\n')
		elif operation == "-":
			res = number1 - number2
			if res < 0:
				outFile.write('Error\n')
			else:
				outFile.write(str(res) + '\n')
		elif operation == "/":
			if number2 == 0:
				outFile.write('Error\n')
			else:
				res = int(number1 / number2)
				outFile.write(str(res) + '\n')
		elif operation == "*":
			res = number1 * number2
			outFile.write(str(res) + '\n')
		elif operation == "^":
			number2 = random.randint(0, 100)
			if number1 == 0 and number2 == 0:
				outFile.write('Error\n')
			else:
				res = pow(number1, number2)
				outFile.write(str(res) + '\n')
		elif operation == "=":
			outFile.write(('true' if number1 == number2 else 'false') + '\n')
		elif operation == "<":
			outFile.write(('true' if number1 < number2 else 'false') + '\n')
		elif operation == ">":
			outFile.write(('true' if number1 > number2 else 'false') + '\n')
		inFile.write(str(number1) + ' ' + str(number2) + ' ' + operation + '\n')
	inFile.close()
	outFile.close()

if __name__ == "__main__":
	main()