//============================================================================
// Name        : AskMe.cpp
// Author      : Youssef
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "AskMe.h"
int main() {
  Askme project{"D:/Yossef/EclipseWorkSpace/AskMe/DataBase/questions.txt",
                "D:/Yossef/EclipseWorkSpace/AskMe/DataBase/users.txt"};
  project.Run();

  return 0;
}
