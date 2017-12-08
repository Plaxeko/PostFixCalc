#include <getopt.h>
#include <sstream>
#include <iostream>
#include <stack>
#include <stdlib.h>
#include "BigInt.h"

using std::cout;
using std::cin;
using namespace mesa;
bool verbose = false;

void printhelp();
void argselect(int argc, char** argv);



int main(int argc, char** argv)
{
cout << "\n\n1.Type (h)elp for program use information.\n2.Type (q)uit to exit.\n3.Type (c)lear to clear the screen\n\ncalc:\n";
    argselect(argc, argv);

    string input;
    string sstream;
    stringstream readline(input);
    bool flag;  
    readline >> sstream;
    //readline.ignore(input.length(),'#');
    while (getline(cin, input) || !readline.eof())
    {
        if(input.size() == 0)
            continue;
        if (input[0] == '#') continue;
        if (tolower(input[0]) == 'q') { return 0; }
        if (tolower(input[0]) == 'c'){cout<<string(100, '\n')<<"\n\n1.Type (h)elp for program use information.\n2.Type (q)uit to exit.\n3.Type (c)lear to clear the screen\n\ncalc:"<<endl; continue; } //fake clear
        if (tolower(input[0]) == 'h')
        {
            printhelp();
        }
        else {
            flag = false;
            for (int i = 0; i <(int) input.size(); i++) {
                if (!(input[i] == '*' || input[i] == '^' || input[i] == '+' || input[i] == ' ' || (input[i] >= '0' && input[i] <= '9')))
                {
                    cout << "Please give one postfix expresion with integer based operands and (+,*,^) operators. Type help.\n";
                    flag = true;
                    break;
                }
            }
            if(flag)
                continue;
            BigInt BI;
            if(verbose)
                BI.put_verbose(true);
            else
                BI.put_verbose(false);
            int index = 0;
            string op1, op2, cur;
            stack<string> operands;
            for(int i = 0; index< input.size(); i++)
            {
                cur = BI.copy_next(&index, input);
                if(cur == "*" || cur == "+" || cur == "^")
                {
                    if(operands.size() >= 2) 
                    {
                        op1 = operands.top();
                        operands.pop();
                        op2 = operands.top();
                        operands.pop();
                        if(cur == "*") operands.push(BI.multiply(op1, op2, false));
                        else if(cur == "+") operands.push(BI.add(op1, op2, false));
                        else if(cur == "^") operands.push(BI.exponent(op2, op1, false));
                    }
                    else
                    {
                        cout<<"Error with the expression: \" " <<input<<" \". Type help. " <<endl<<endl;
                        flag = true;
                        break;
                    }
                }
                else{
                    for(int j = 0; j < cur.size();j++)
                    {
                        if(cur[j]<'0' || cur[j] > '9'){
                            cout<<"Error with input: \" " << cur<<" \". Type help. "<<endl<<endl;
                            flag = true;
                            break;
                        }
                    }
                    if(flag)
                        break;
                    operands.push(cur);
                }
            }
            if(flag)
                continue;
            if(operands.size()!=1){
                cout<<"Too few operators in expression: \" "<<input <<" \". Type help. " <<endl<<endl;
                flag = true;
            }
            if(flag)
                continue;
            op1 = operands.top();
            if(verbose){
                cout<<input<<" = ";
            }
            cout << op1<<endl;
        }
    }
    return 0;
}

void printhelp()
{
  cout << "'7MM""Mq.                      mm         .d``  db                   .g8""bgd          `7MM        \n";          
  cout << "`MM   `MM.                   MM         dM`                      .dP'                  MM        \n";          
  cout << "`MM   ,M9 ,pWWq.  ,pP""Ybd mmMMmm       mMMm`7  MM  `7M'   `MF'    dM'         ,6''Yb.   MM  ,p6bo \n";  
  cout << "`MMmmdM9 6W'   `Wb 8I   `'   MM         MM    MM    `VA ,V'      MM         8)   MM    MM 6M'  OO\n";  
  cout << "`MM      8M     M8 `YMMMa.   MM         MM    MM      XMX        MM.         ,pm9MM    MM 8M     \n";       
  cout << "`MM      YA.   ,A9 L.   I8   MM         MM    MM    ,V' VA.      `Mb.     ,'8M   MM    MM YM.    \n"; 
  cout << "JMML.    `Ybmd9'   M9mmmP'   `Mbmo    .JMML..JMML..AM.   .MA.      `'bmmmd' `Moo9^Yo..JMML.YMbmd'\n";
  cout << "__________________________________________________________________________________________________\n";
  cout << "    A post fix calculator | Multi-operator capability | HUGE integer capability (no overflow)   \n\n\n";  
          
  cout << "  *********************************************************************************************\n"
                 "                                                                                               \n"
                 "    1.Give the system an operator AFTER giving two operands.                                   \n"
                 "                                                                                               \n"
                 "    2. The program will take the result of the first two operands and use the next given       \n"
                 "       operand as the second value. Follow this with another operand.                          \n"
                 "       example input: 12 8 + 2 * 3 ^                                                           \n"
                 "                                                                                               \n"
                 "    3. Use -v on execution for verbose result mode example: a b + = c                          \n"   
                 "                                                                                               \n"
                 "    You can Add (+), multiply (*), and give exponent (^). example input: a b c * +             \n"
                 "                                                                                               \n"
                 "    type 'quit' or just 'q' to exit the program                                                \n"
                 "                                                                                               \n"
                 "    You can process a file with one postfix expression(multi operator functional) per line.    \n"
                 "                                                                                               \n"
                 "    use -h on execution to launch help menu on startup.                                        \n"
                 "                                                                                               \n"    
                 "  *********************************************************************************************\n"
                 "  Created by Amir Torabi. \n"
    <<endl;
    cout << "calc:" << endl;
        //exit(1);
}

void argselect(int argc, char** argv)
{
    const char* const opt = "hv";
    while(true)
    {
        const int select = getopt(argc,argv,opt);
        if (-1 == select)
            break;
        switch(select)
        {
        case 'v':
            verbose = true;
            cout << " (verbose mode On)" << endl;
            break;
        case 'h':
            printhelp();
            break;
        case '?':
            default:
            cout <<  "Unknown command" << endl;
            break;
        }
    }
}


