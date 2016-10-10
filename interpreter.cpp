#include <iostream>
#include "expTree.h"
#include "StringOperations.h"

using namespace std;

int main(){

    string input, cmd;
	ExpTree expression;
//    input = "- x x";
//    expression.build(input);
//    cout << (expression.root->getLeft()->getInfo() == expression.root->getRight()->getInfo()) ;


	while(getline(cin,input)){//read commands until file ends

		toLower(input);//make sure input is of correct case

        extractFirstWord(input, cmd);

		//choose the correct option
		if(cmd == "exp"){
            expression.build(input);
		}
        else if(cmd == "eval"){
            extractFirstWord(input, cmd);
            expression.eval(atof(cmd.c_str()));
        }
		else if(cmd == "simp"){
			expression.simplify();
		}
		else if (cmd == "print"){
			expression.printInfix(cout);
		}
		else if (cmd == "dot"){
            expression.saveAsDot(input.c_str());
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