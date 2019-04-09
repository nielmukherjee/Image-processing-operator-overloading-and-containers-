#include "imageops.h"
#include <iostream>
#include <ios>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//int main(int argc, char *argv[])
int main () {
   // local variable declaration:
   int a = 100;
   int b = 200;
   int ret;
 
   // calling a function to get max value.
   ret = max(a, b);
   cout << "Max value is : " << ret << endl;
 
   return 0;
}