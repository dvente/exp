from sympy import * 
from random import *
from string import *
import sys
import os
from subprocess import call, check_output

cmd = ["exp", "eval", "simp", "print", "diff", "dot", "end"]
expressions = ["cos", "sin", "+", "-", "*", "/", "^", "x", "y", "z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "pi"]
string = ""

def eval(var, string, point):
	return string.replace(var,str(point))

def weighted_choice(choices):
   total = sum(w for c, w in choices)
   r = uniform(0, total)
   upto = 0
   for c, w in choices:
      if upto + w >= r:
         return c
      upto += w
   assert False, "Shouldn't get here"

def genNumber(sign, integer): #still implement pi
	if sign: 
		if integer:
			return randrange(-100,0)
		else:
			if choice([True,False]):
				return uniform(-100,0)
			else:
				return "pi"
	else:
		if not integer:
			return uniform(0,100)
		else:
			return randrange(0,100)

def genVar():
	return weighted_choice([["a",1],["b",1],["c",1],["d",1],["e",1],["f",1],["g",1],["h",1],["i",1],["j",1],["k",1],["l",1],["m",1],["n",1],["o",1],["p",1],["q",1],["r",1],["s",1],["t",1],["u",1],["v",1],["w",1],["x",90],["y",1],["z",1]]).lower()


def generateSubExp(depth):
	global string
	seed()

	if depth < 0:
		return 
	if depth == 0:
		number = randrange(7,13)
		#print number 
	else:
		number = randrange(0,6)
		#print number


	if number in [0,1]: #cos,sin
		first = str(generateSubExp(depth - 1))
		return expressions[number] + " " + first
	elif number in range(2,6): # unrestricted binary
		first = str(generateSubExp(depth - 1))
		second = str(generateSubExp(choice([max(depth - 1,0), 0])))
		return expressions[number] + " " + first + " " + second
	elif number == 6: #POW
		first = str(generateSubExp(depth - 1))
		second = str(generateSubExp(0))
		return expressions[number] + " " + first + " " + second
	elif number in range(7,11):#var
		return  "x"#str(genVar())
	elif number in range(11,14):#number
		return str(genNumber(choice([True, False]),choice([True, False])))
	else:
		print "invalid..."
		print number
		return " "

length = int(sys.argv[1])

param = generateSubExp(length)
instructions = "exp " + param + "\nprint\nend"
	
open("expression.txt",'w').close()
f = open('expression.txt', 'r+')
f.write(instructions)
f.close()

answer = check_output("./interpreter < expression.txt", shell = True)
answer = answer.replace(" ","")
x = symbols('x')
diffAnswer = diff(answer,x)


instructions = "exp " + param + "\ndiff\nsimp\nprint\nend"
open("expression.txt",'w').close()
f = open('expression.txt', 'r+')
f.write(instructions)
f.close()

target = check_output("./interpreter < expression.txt", shell = True)
target = target.replace(" ","")


pyAns = diffAnswer
TreeAns = target

print "original expression: " + str(param)
print "pyAns: " + str(pyAns)
print "TreeAns: " + str(TreeAns)




