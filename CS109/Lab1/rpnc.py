#
# Python3 Reverse Polish Notation (RPN) Calculator
#
# Accepts an single argument in RPN, evaluates it and prints the answer to stdout.
# 
if __name__ == '__main__':
	stack = []
	string = str(input())
	#http://www.pythonforbeginners.com/dictionary/python-split
	array = string.split(":")
	print(array[0])
	array = array[0].split(" ")
	for word in array:
		
		#https://stackoverflow.com/questions/5424716/how-to-check-if-string-input-is-a-number
		if(word.isdigit()):
			stack.append(int(word))
		
		elif(word != " " and word != ":"):
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
			stack.append(result)

	print(int(stack.pop()))
