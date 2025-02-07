/*
 * User.h
 *
 *  Created on: Jan 19, 2025
 *      Author: yosse
 */

#ifndef USER_H_
#define USER_H_
#include <algorithm>
#include <cassert>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "Common.h"
class User {
 private:
  int UserID;
  std::string Name;
  std::string email;
  std::pair<std::string, std::string>
      LoginInfo{};  // pair , user name , password;
  std::vector<int> QuestID_FromMe;
  // Quest id to threads id for this user
  std::map<int, std::vector<int>> QuestID_ThreadsID_Map;
  bool AllowAnonyQuest;
  void IsValidUser() {
    assert(UserID > 0);
    assert(Name.size() != 0);
    assert(email.size() != 0);
    assert(LoginInfo.first.size() != 0);
    assert(LoginInfo.second.size() != 0);
  }
  const std::pair<std::string, std::string>& GetLoginInfo(void) const {
    return (this->LoginInfo);
  }
  const std::string& GetPassword(void) const {
    return (this->LoginInfo.second);
  }

 public:
  User() = default;
  User(const std::string& Name, const std::string& email,
       std::pair<std::string, std::string> LoginInfo, int UserID,
       bool AllowAnonyQuest = false)
      : Name(Name),
        email(email),
        LoginInfo(LoginInfo),
        UserID(UserID),
        AllowAnonyQuest(AllowAnonyQuest) {
    IsValidUser();
  }
  User(const std::string& Line) {
    std::vector<std::string> SubStr{SplitString(Line)};
    SetUserID(StrToInt(SubStr[0]));
    SetUserName(SubStr[1]);
    SetPassWord(SubStr[2]);
    SetName(SubStr[3]);
    SetEmail(SubStr[4]);
    SetAnonyQuest((StrToInt(SubStr[5]) == 1));
  }
  ~User() = default;
  User(const User& other) = default;
  User(User&& other) = default;
  User& operator=(const User& other) = default;
  User& operator=(User&& other) = default;

  void ClearQuestIDFromMe() { QuestID_FromMe.clear(); }
  void ClearThreadsID() { QuestID_ThreadsID_Map.clear(); }
  bool LoginCheck(std::string const& UserName,
                  std::string const& Password) const;

  // getters

  int GetUserID() const;
  const std::string& GetUserName() const { return (this->LoginInfo.first); }
  const std::string& GetName() const;
  const std::string& GetEmail() const;
  std::vector<int> const& GetQuestIDsFromMe() const;
  std::vector<int> const& GetThreadsIDsForMeForQuestion(int QuestID) const;
  bool isAnonyQuestAllowed() const { return (this->AllowAnonyQuest); }
  std::map<int, std::vector<int>> const& GetQuestID_ThreadsID_Map(void) const {
    return this->QuestID_ThreadsID_Map;
  }
  const std::string ToStr() const {
    std::ostringstream oss;
    // user id , user name , password , name , email , allow anony
    oss << "\n"
        << GetUserID() << "," << GetUserName() << "," << GetPassword() << ","
        << GetName() << "," << GetEmail() << "," << isAnonyQuestAllowed();
    return (oss.str());
  }
  // setters
  void SetUserID(int id);
  void SetName(const std::string& _name);
  void SetEmail(const std::string& _email);
  void SetUserName(const std::string& _UserName);
  void SetPassWord(const std::string& _PassWord);
  void SetAnonyQuest(bool Anony) { this->AllowAnonyQuest = Anony; }
  /**/
  void AddQuestIDFromMe(int id);
  void AddThreadIDToME(int QuestID, int ThreadID);

  void DeleteQuestionIDFromMe(int QuestID) {
    const auto& it =
        std::find(QuestID_FromMe.begin(), QuestID_FromMe.end(), QuestID);
    if (it != QuestID_FromMe.end()) {
      QuestID_FromMe.erase(it);
    }
  }
};

#endif /* USER_H_ */
