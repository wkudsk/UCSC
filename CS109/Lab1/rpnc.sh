#!/bin/bash
#
# Bash Reverse Polish Notation (RPN) Calculator
#
# Accepts an single argument a RPN, evaluates it and prints the answer to stdout.
# Using code shown to us in David Harrison's lecture
# See the webcast at http://opencast-util.lt.ucsc.edu/search/?seriestitle=CMPS-109-LEC-01-2182-61545

stack=()
next=0

#replaces the * operator in the argument with x.
rpn=`echo "$1" | sed 's/\*/x/g'`

for oper in $rpn
do
	#if the character is a number,push it to stack.
	if [[ "$oper" =~ ^[0-9]+$ ]]
	then
		stack[$next]=$oper
	else
		#Else, its an operator. Pop last two from the stack and perform operation.
		(( next -= 1 ))
		oper_2=${stack[$next]}
		(( next -= 1 ))
		oper_1=${stack[$next]}

		#List of if statements check to see which operator it is.
		if [[ "$oper" == "+" ]]
		then
			(( value = $oper_1 + $oper_2 ))
		elif [[ "$oper" == "-" ]]
		then
			(( value = $oper_1 - $oper_2 ))
		elif [[ "$oper" == "/" ]]
		then
			(( value = $oper_1 / $oper_2 ))
		elif [[ "$oper" == "x" ]]
		then
			(( value = $oper_1 * $oper_2 ))
		elif [[ "$oper" == "^" ]]
		then
			(( value = $oper_1 ** $oper_2 ))
		fi
		#the new result is pushed back onto the stack
		stack[$next]=$value
	fi
	#stack point is increamented
	(( next += 1 ))
done
echo ${stack[0]}
