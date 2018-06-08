/*
 * Node.js / JavaScript Reverse Polish Notation (RPN) Calculator
 *
 * Accepts an single argument in RPN, evaluates it and prints the answer to stdout.
 * 
 */

//https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Functions
var CalcRPNC = function(needsRPNC)
{
	var stack = [];
	for (var i = 0; i < needsRPNC.length; i++)
	{
		var char = needsRPNC[i];
		//console.log(char);
		if(char == '*')
		{
			var intOne = stack.pop();
			var intTwo = stack.pop();
			var result = intTwo*intOne;
			//console.log(intTwo + " * " + intOne + " = " + result);
			stack.push(result);
		}
		else if(char == "-")
		{
			var intOne = stack.pop();
			var intTwo = stack.pop();
			var result = intTwo-intOne;
			//console.log(intTwo + " - " + intOne + " = " + result);
			stack.push(result);
		}
		else if(char == "+")
		{
			var intOne = stack.pop();
			var intTwo = stack.pop();
			var result = intTwo+intOne;
			//console.log(intTwo + " + " + intOne + " = " + result);
			stack.push(result);
		}
		else if(char == "/")
		{
			var intOne = stack.pop();
			var intTwo = stack.pop();
			var result = intTwo/intOne;
			//console.log(intTwo + " / " + intOne + " = " + result);
			stack.push(result);
		}
		else if(char == "^")
		{
			var intOne = stack.pop();
			var intTwo = stack.pop();
			var result = Math.pow(intTwo, intOne);
			//console.log(intTwo + " ^ " + intOne + " = " + result);
			stack.push(result);
		}
		else
		{
			//console.log(char);
			var num = parseInt(char); 
			stack.push(num);
		}
	}
	return stack[0];
}

//https://stackoverflow.com/questions/4351521/how-do-i-pass-command-line-arguments-to-a-nodejs-program
var needsRPNC = process.argv[2].split(" ");
var done = CalcRPNC(needsRPNC);
console.log(done);
