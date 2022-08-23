//si usa .h per misto tra c e c++, .hpp solo per c++
//https://www.geeksforgeeks.org/header-files-in-c-cpp-and-its-uses/
/*

Including Multiple Header Files: 
You can use various header files in a program. When a header file is included twice within a program,
 the compiler processes the contents of that header file twice. This leads to an error in the program. 
 To eliminate this error, conditional preprocessor directives are used. 

#ifndef HEADER_FILE_NAME
#define HEADER_FILE_NAME

   the entire header file

#endif

*/
#include <string>


void myPrint();
void myPrint(std::string str);