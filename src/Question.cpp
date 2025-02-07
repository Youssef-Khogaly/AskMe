/*
 * Question.cpp
 *
 *  Created on: Jan 19, 2025
 *      Author: yossef
 */

#include <iostream>
#include <sstream>

#include "Question.h"
int Question::GetQuestID() const { return (this->QuestID); }
void Question::SetQuestID(int id) { this->QuestID = id; }
int Question::GetParentID(void) const { return (this->ParentQuestID); }
void Question::SetParentID(int id) { this->ParentQuestID = id; }
void Question::SetAnswer(const std::string& ans) {
  if (ans.size() == 0)
    this->QuestAns = "";
  else
    this->QuestAns = ans;
}
const std::string& Question::GetAnswer(void) const { return (this->QuestAns); }
void Question::SetToUserID(int id) {
  assert(id > 0);
  this->ToUserID = id;
}
void Question::SetFromUserID(int id) {
  assert(id > 0);
  this->FromUserID = id;
}
int Question::GetToUserID() const { return this->ToUserID; }
int Question::GetFromUserID() const { return this->FromUserID; }
const std::string& Question::GetQuestStr() const { return (this->QuestStr); }
std::string Question::ToStr(void) const {
  std::ostringstream oss;
  oss << GetQuestID() << "," << GetParentID() << "," << GetFromUserID() << ","
      << GetToUserID() << "," << isAnonyQuest() << "," << GetQuestStr() << ","
      << GetAnswer();

  return (oss.str());
}
bool Question::isAnswered(void) const {
  auto& Ans = GetAnswer();
  if (Ans.size() == 0) return false;

  return true;
}
int Question::isAnonyQuest(void) const {
  if (this->IsAnonyQuest) return 1;

  return 0;
}
void Question::PrintToMeQuest(void) const {
  using namespace std;
  std::string prefix = "";

  if (GetParentID() != -1) prefix = "\tThread: ";

  cout << prefix << "Question Id (" << GetQuestID() << ")";
  if (!isAnonyQuest()) cout << " from user id(" << GetFromUserID() << ")";
  cout << "\t Question: " << GetQuestStr() << "\n";

  if (isAnswered()) cout << prefix << "\tAnswer: " << GetAnswer() << "\n";
  cout << "\n";
}
void Question::PrintFromMeQuest(void) const {
  std::cout << "Question Id (" << GetQuestID() << ")";
  if (isAnonyQuest()) std::cout << " !AQ";

  std::cout << " to user id(" << GetToUserID() << ")";
  std::cout << "\t Question: " << GetQuestStr();

  if (isAnswered())
    std::cout << "\tAnswer: " << GetAnswer() << "\n";
  else
    std::cout << "\tNOT Answered YET\n";
}

bool Question::isThread(void) const {
  if (GetParentID() == -1) return false;

  return true;
}

void Question::PrintFeedQuest() const {
  using namespace std;
  if (isThread())
    cout << "Thread Parent Question ID (" << GetParentID() << ") ";

  cout << "Question Id (" << GetQuestID() << ")";
  if (false == isAnonyQuest())
    cout << " from user id(" << GetFromUserID() << ")";

  cout << " To user id(" << GetToUserID() << ")";

  cout << "\t Question: " << GetQuestStr() << "\n";
  if (isAnswered())
    cout << "\tAnswer: " << GetAnswer() << "\n";
  else
    cout << "\t Not Answered Yet \n";
}
