#
# Python3 Reverse Polish Notation (RPN) Calculator
#
# Accepts an single argument in RPN, evaluates it and prints the answer to stdout.
# 

import sys
if __name__ == '__main__':

	#https://www.tutorialspoint.com/python/python_functions.htm
	#If word is an operator, return true, otherwise return false
	def isOperator(str):
		if(word == "+" or word == "-" or word == "*" or word == "/" or word == "^"):
			return True
		else:
			return False 
	
	stack = []

	#https://stackoverflow.com/questions/70797/python-user-input-and-commandline-arguments
	string = str(sys.argv[1])
	
	#http://www.pythonforbeginners.com/dictionary/python-split
	array = string.split(" ")

	for word in array:
		
		#https://stackoverflow.com/questions/5424716/how-to-check-if-string-input-is-a-number
		if(word.isdigit()):
			stack.append(int(word))	
		
		#For some reason array stores an element that is just an empty string, if thats the case, DON'T go into elif statment
		elif(isOperator(word)):
			b = stack.pop()
			a = stack.pop()
			result = 0
			
			if(word == '+'):
				result = a + b
			elif(word == '-'):
				result = a - b
			elif(word == '/'):
				result = a / b
			elif(word == '*'):
				result = a * b
			elif(word == '^'):
				result = a ** b
		
			#When you divide or pow, you get float. Cast as int for that float
			stack.append(int(result))

	print(str(stack.pop()))
