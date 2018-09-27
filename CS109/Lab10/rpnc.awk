#
# Awk Reverse Polish Notation (RPN) Calculator
#
# Accepts an single argument in RPN, evaluates it and prints the answer to stdout.
# 
BEGIN {
    res = ARGV[1]
    split(res,needsRPNC,"\\s+")
    stackString = " "
    split(stackString, stack, " ") 
    stackNum = 0
    for(i = 0; i < length(needsRPNC); i++)
    {
    	char = needsRPNC[i]
    	#print char
    	if(char == "*")
    	{
    		stackNum = stackNum - 1
    		numOne = stack[stackNum]
    		stackNum = stackNum - 1
    		numTwo = stack[stackNum]
    		result = numTwo*numOne
    		stack[stackNum] = result
    		stackNum = stackNum + 1
    	}
    	else if(char == "-")
		{
			stackNum = stackNum - 1
			numOne = stack[stackNum]
    		stackNum = stackNum - 1
    		numTwo = stack[stackNum]
    		result = numTwo-numOne
    		stack[stackNum] = result
    		stackNum = stackNum + 1
		}
		else if(char == "+")
		{
			stackNum--
			numOne = stack[stackNum]
    		#print numOne
    		stackNum--
    		numTwo = stack[stackNum]
    		#print numTwo
    		result = numTwo+numOne
    		#print result
    		stack[stackNum] = result
    		stackNum = stackNum + 1
		}
		else if(char == "/")
		{
			stackNum = stackNum - 1
			numOne = stack[stackNum]
    		stackNum = stackNum - 1
    		numTwo = stack[stackNum]
    		result = numTwo/numOne
    		stack[stackNum] = result
    		stackNum = stackNum + 1
		}
		else if(char == "^")
		{
			stackNum = stackNum - 1
			numOne = stack[stackNum]
    		stackNum = stackNum - 1
    		numTwo = stack[stackNum]
    		result = numTwo ** numOne
    		stack[stackNum] = result
    		stackNum = stackNum + 1
		}
		else
		{
			#print char
			stack[stackNum] = char
			stackNum = stackNum + 1
		}
    }
    stackNum--
    stackNum--
    print stack[stackNum]
}
