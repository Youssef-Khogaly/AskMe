/*
 * UserManager.cpp
 *
 *  Created on: Jan 19, 2025
 *      Author: yossef
 */

#include "UserManager.h"

#include <iostream>
void UserManager::SetDataBasePath(const std::string& path) {
  assert(path.size() > 0);
  this->DataBasePath = path;
}
const std::string& UserManager::GetDataBasePath(void) const {
  return (this->DataBasePath);
}
void UserManager::loadUsers() {
  UserName_UserObj_Map.clear();
  usersList.clear();
  std::vector<std::string> Lines{ReadFileLines(GetDataBasePath())};
  for (const auto& line : Lines) {
    User user{line};
    usersList.push_back(user);
    User* ptrUser = &(*usersList.rbegin());
    UserName_UserObj_Map.insert(std::make_pair(user.GetUserName(), ptrUser));
    SetLastUserID(std::max(GetLastUserID(), user.GetUserID()));
  }

  return;
}
bool UserManager::SignUp(const User& _user) {
  bool ret = false;
  if (this->UserName_UserObj_Map.count(_user.GetUserName()) == 0) {
    WriteFileLines(GetDataBasePath(), _user.ToStr());
    usersList.push_back(_user);
    User* ptrUser = &(*usersList.rbegin());
    this->UserName_UserObj_Map.insert(
        std::make_pair(_user.GetUserName(), ptrUser));
    ret = true;
  }

  return ret;
}
bool UserManager::Login(std::string const& UserName,
                        std::string const& password) {
  bool ret{false};
  try {
    auto& _user = this->UserName_UserObj_Map.at(UserName);
    if (_user->LoginCheck(UserName, password)) {
      this->CurrentUser = _user;
      ret = true;
    }
  } catch (std::out_of_range& err) {
    ret = false;
  }

  return ret;
}

int UserManager::GetCurrentUserID(void) const {
  return (this->CurrentUser->GetUserID());
}
const std::string& UserManager::GetCurrnetUserName() const {
  return (this->CurrentUser->GetName());
}

void UserManager::UpdateUsersDataBase(bool append) const {
  for (const auto& user : usersList) {
    WriteFileLines(GetDataBasePath(), user.ToStr(), append);
    append = true;
  }
}

void UserManager::DeleteQuestionFromCurrentUser(int QuestID) {
  CurrentUser->DeleteQuestionIDFromMe(QuestID);
}
