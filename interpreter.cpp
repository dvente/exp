#include <iostream>
#include "expTree.h"
#include "StringOperations.h"

using namespace std;

int main(){

	string input, expr, cmd;
	ExpTree expression;

	while(getline(cin,input)){//read commands until file ends

		toLower(input);//make sure input is of correct case

		splitOffFirstWord(input, cmd, expr);
		
		//choose the correct option
		if(cmd == "exp"){
			expression.build(expr);
		}
//		else if(cmd == "eval"){
//			extractFirstWord(expr, cmd, expr);
//			if(isDouble(cmd.c_str()))
//				expression.eval(atof(cmd.c_str()));
//			else
//				expression.evalInt(atoi(cmd.c_str()));
//		}
        else if(cmd == "eval"){
            splitOffFirstWord(expr, cmd, expr);
            expression.eval(atof(cmd.c_str()));
            //if(isDouble(cmd.c_str()))
            //else
            //    expression.evalInt(atoi(cmd.c_str()));
        }
		else if(cmd == "simp"){
			expression.simplify();
		}
		else if (cmd == "print"){
			expression.printInfix(cout);
		}
		else if (cmd == "dot"){
			expression.saveAsDot(expr.c_str());
		}
		else if (cmd == "diff"){
			expression.diff();
		}
		else if (cmd == "end"){
			exit(EXIT_SUCCESS);
		}
		else{
			cout << "invalid input... " << endl;
		}
	
	}//while

	return 0;

}//main