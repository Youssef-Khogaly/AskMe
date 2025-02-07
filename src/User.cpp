/*
 * User.cpp
 *
 *  Created on: Jan 19, 2025
 *      Author: yossef
 */

#include "User.h"

bool User::LoginCheck(std::string const& UserName,
                      std::string const& Password) const {
  const auto& LoginData = GetLoginInfo();
  if (LoginData.first == UserName && LoginData.second == Password) {
    return true;
  }

  return false;
}
// getters

int User::GetUserID() const { return (this->UserID); }
const std::string& User::GetName() const { return this->Name; }
const std::string& User::GetEmail() const { return this->email; }
// setters
void User::SetUserID(int id) {
  assert(id > 0);
  this->UserID = id;
}

void User::SetName(const std::string& _name) {
  assert(_name.size() > 0);
  this->Name = _name;
}
void User::SetEmail(const std::string& _email) {
  assert(_email.size() > 0);
  this->email = _email;
}
void User::SetUserName(const std::string& _UserName) {
  assert(_UserName.size() > 0);
  this->LoginInfo.first = _UserName;
}
void User::SetPassWord(const std::string& _PassWord) {
  assert(_PassWord.size() > 0);
  this->LoginInfo.second = _PassWord;
}
void User::AddQuestIDFromMe(int id) {
  assert(id > 0);
  this->QuestID_FromMe.push_back(id);
}
void User::AddThreadIDToME(int QuestID, int ThreadID) {
  auto& map = this->QuestID_ThreadsID_Map;
  if (map.count(QuestID) != 0)
    map[QuestID].push_back(ThreadID);
  else {
    map.insert(std::make_pair(QuestID, std::vector<int>{ThreadID}));
  }
}
std::vector<int> const& User::GetQuestIDsFromMe() const {
  return (this->QuestID_FromMe);
}
std::vector<int> const& User::GetThreadsIDsForMeForQuestion(int QuestID) const {
  return (QuestID_ThreadsID_Map.at(QuestID));
}
