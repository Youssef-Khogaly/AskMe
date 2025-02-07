/*
 * UserManager.h
 *
 *  Created on: Jan 19, 2025
 *      Author: yosse
 */

#ifndef USERMANAGER_H_
#define USERMANAGER_H_
#include <list>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "Common.h"
#include "User.h"
class UserManager {
 private:
  std::map<std::string, User*>
      UserName_UserObj_Map{};  // pair<login name , user obj>
  /*Dont use it to create new obj */
  std::list<User> usersList{};
  User* CurrentUser = nullptr;
  inline static int LastUserID = 0;
  std::string DataBasePath{};
  inline void SetLastUserID(int id) { LastUserID = id; }
  inline static int GetLastUserID() { return (LastUserID); }

  // return nullptr if user not found
  const User* GetUserObj(int id) const {
    for (const auto& pair : UserName_UserObj_Map) {
      if (pair.second->GetUserID() == id) return (pair.second);
    }
    return nullptr;
  }

 public:
  UserManager() = default;
  UserManager(const std::string& DataBasePath) {
    SetDataBasePath(DataBasePath);
  }
  ~UserManager() = default;
  UserManager(const UserManager& other) = delete;
  UserManager(UserManager&& other) = delete;
  UserManager& operator=(const UserManager& other) = delete;
  UserManager& operator=(UserManager&& other) = delete;
  void SetDataBasePath(const std::string& path);
  const std::string& GetDataBasePath(void) const;
  void loadUsers();
  bool SignUp(const User& _user);
  bool Login(std::string const& UserName, std::string const& password);

  int GetCurrentUserID(void) const;
  const std::string& GetCurrnetUserName() const;
  const User& GetCurrentUserObj(void) const { return (*this->CurrentUser); }
  int GenerateID() {
    ++LastUserID;
    return (LastUserID);
  }
  const std::map<std::string, User*>& GetUserName_UserObj_map(void) const {
    return (this->UserName_UserObj_Map);
  }
  const
      /*throw std::out_of_range if there is not user with this id*/
      bool
      IsAnonyQuestAllowedForUser(int id) const {
    const User* _user = GetUserObj(id);
    if (_user == nullptr) {
      throw std::out_of_range("\nThere is no user with this id\n");
    }

    return (_user->isAnonyQuestAllowed());
  }
  bool IsUserIDExist(int id) const {
    const User* _user = GetUserObj(id);
    if (_user == nullptr)
      return false;
    else
      return true;
  }
  std::list<User>& GetUsersList() { return usersList; }
  void UpdateUsersDataBase(bool append) const;
  void DeleteQuestionFromCurrentUser(int QuestID);
};

#endif /* USERMANAGER_H_ */
