//
// Tomás Oliveira e Silva, AED, October 2014, September 2015
//
// matched-parenthesis verification
//
#include <stdio.h>
#include <iostream>
#include "aStack.h"
#include <string.h>

using std::cout;
using std::cerr;
using std::endl;

int check_parenthesis(const char *s){

  //Initialize stack
  int i;
  int erro=0;
  aStack<int> s1 = aStack<int>();

  for ( i = 0 ; i < strlen(s) ; i++){
    //push element into stack
    if(s[i] == '('){
      s1.push(i) ;
    }
    //remove element if stack is not empty
    else if ( s[i] == ')'  && !s1.is_empty() ){
      cout << "'(' at position " << s1.pop()  << " and matching ')' at position "<<i<< '\n';
    }
    //if stack is empty and find )
    else if ( s[i] == ')'  && s1.is_empty() ) {
      cout << "unmatched ')' at position " <<i<< '\n';
      erro += 1;
    }
  }

  // if string only has (
  if( !s1.is_empty()){
    cout << "unmatched '(' at position " << s1.pop()<<'\n';
  }

  return erro;
}

int main(int argc,char **argv)
{
  if(argc == 1)
  {
    cerr << "usage: " << argv[0] << " [arguments...]" << endl;
    cerr << "example: " << argv[0] << " 'abc(def)ghi' 'x)(y'" << endl;
    return 1;
  }
  for(int i = 1;i < argc;i++)
  {
    cout << argv[i] << endl;
    if(check_parenthesis(argv[i]) == 0)
    cout << "  good" << endl;
    else
    cout << "  bad" << endl;
  }
  return 0;
}
