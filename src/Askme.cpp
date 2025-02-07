/*
 * Askme.cpp
 *
 *  Created on: Jan 19, 2025
 *      Author: yosse
 */

#include "Askme.h"

#include <algorithm>
#include <iostream>
#include <limits>
template <typename T>
T Askme::ReadInput(T low, T high, const std::string& errorMsg) {
  T input{};
  std::cin.clear();
  while (1) {
    std::cin >> input;
    if (std::cin.fail() || input < low || input > high) {
      std::cout << errorMsg << std::endl;
      std::cin.clear();
      std::cin.ignore(256, '\n');
    } else
      break;
  }

  return input;
}

template <typename T>
T Askme::ReadInput(const std::initializer_list<T>& choices, T low, T high,
                   const std::string& errorMsg) {
  T input{};
  std::cin.clear();
  while (1) {
    std::cin >> input;
    bool is_in_choices =
        (std::find(choices.begin(), choices.end(), input) != choices.end());
    if (std::cin.fail() ||
        ((is_in_choices == false) && (input < low || input > high))) {
      std::cout << errorMsg << std::endl;
      std::cin.clear();
      std::cin.ignore(256, '\n');
    } else
      break;
  }

  return input;
}
template <typename T>
T Askme::ReadInput(const std::initializer_list<T>& choices,
                   const std::string& errorMsg) {
  T input{};
  std::cin.clear();
  while (1) {
    std::cin >> input;
    if (std::cin.fail() ||
        std::find(choices.begin(), choices.end(), input) == choices.end()) {
      std::cout << errorMsg << std::endl;
      std::cin.clear();
      std::cin.ignore(256, '\n');
    } else
      break;
  }

  return input;
}
std::string Askme::ReadInput() {
  std::string ret{""};

  while (1) {
    std::cin >> ret;
    if (std::cin.fail()) {
      std::cout << "Invalid Input Try again" << std::endl;
      std::cin.clear();
      std::cin.ignore(256, '\n');
    } else
      break;
  }

  return ret;
}
void Askme::UpdateDataBase(bool append) {
  UpdateQuestionsDataBase(append);
  UpdateUsersDataBase(append);
}

void Askme::FillUsersQuestions() {
  auto& List = this->UserMgr.GetUsersList();
  for (auto& user : List) {
    QuestMgr.FillUserQuestions(user);
  }
}
void Askme::LoadDataBase() {
  LoadQuestions();
  LoadUsers();
  FillUsersQuestions();
}
void Askme::LoadUsers() { this->UserMgr.loadUsers(); }
void Askme::LoadQuestions() { this->QuestMgr.LoadQuestions(); }
bool Askme::Login() {
  std::string UserName{};
  std::string pass{};

  std::cout << "User name:";
  UserName = ReadInput();
  std::cout << "Password:";
  pass = ReadInput();

  return (UserMgr.Login(UserName, pass));
}
bool Askme::SignUp() {
  User user;
  std::cout << "name:";
  user.SetName(ReadInput());
  std::cout << "Enter login name:";
  user.SetUserName(ReadInput());
  std::cout << "Enter Password:";
  user.SetPassWord(ReadInput());
  std::cout << "Enter email:";
  user.SetEmail(ReadInput());
  std::cout << "is anonymous questions allowed?y\n:";
  std::string anonyQuest{ReadInput(
      {std::string("y"), std::string("n"), std::string("Y"), std::string("N")},
      "invalid input enter y\n:")};

  if (anonyQuest == "y" || anonyQuest == "Y")
    user.SetAnonyQuest(true);
  else
    user.SetAnonyQuest(false);
  user.SetUserID(UserMgr.GenerateID());
  return (this->UserMgr.SignUp(user));
}

void Askme::PrintQuestionToMe() {
  this->QuestMgr.PrintToUserQuests(this->UserMgr.GetCurrentUserObj());
}
void Askme::PrintQuestionFromMe() {
  this->QuestMgr.PrintFromUserQuests(this->UserMgr.GetCurrentUserObj());
}
void Askme::AnswerQuestion() {
  int id;
  std::cout << "Enter Question id or -1 to cancel:";
  while (1) {
    std::cin >> id;
    if (id == -1) return;
    if (std::cin.fail() || id < -1 || id == 0) {
      std::cout << "invalid number";
      std::cin.clear();
      std::cin.ignore(256, '\n');
    } else
      break;
  }
  // check if this question asked to current user or not
  if (QuestMgr.is_valid_User_to_answer(UserMgr.GetCurrentUserID(), id)) {
    std::cout << "Enter answer:";
    std::string answer{};
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, answer);
    this->QuestMgr.AnswerQuestion(id, answer);
    UpdateQuestionsDataBase(false);
  } else {
    std::cout << "You can't Answer Question did not asked for you\n\n";
  }
}
void Askme::DeleteQuestion() {
  int questid{};
  int FromUser_ID{-1};
  std::cout << "Quest ID or enter -1 to back:";
  questid = ReadInput(std::initializer_list<int>{-1}, 1, INT_MAX,
                      "invalid id try again:");
  if (questid == -1) return;

  try {
    FromUser_ID = QuestMgr.GetFromUserID(questid);
  } catch (std::out_of_range& err) {
    std::cout << "There is no Question with this ID:" << questid << "\n\n";
    return;
  }
  if (FromUser_ID != UserMgr.GetCurrentUserID()) {
    std::cout << "You can't Delete other people question!! \n\n";
    return;
  }
  QuestMgr.DeleteQuestion(questid);
  UpdateQuestionsDataBase(false);
  FillUsersQuestions();
  std::cout << "Question Deleted successfully\n\n";
}
void Askme::AskQuestion() {
  Question quest;
  int to_userID{};
  int parentQuestID{-1};
  std::string QuestStr{};
  std::cout << "Enter user id or -1 to back:";
  to_userID = ReadInput(std::initializer_list<int>{-1}, 1, INT_MAX,
                        "invalid user id try again");
  if (to_userID == -1)
    return;
  else if (false == UserMgr.IsUserIDExist(to_userID)) {
    std::cout << "There is no user with this ID \n\n";
    return;
  }
  quest.SetToUserID(to_userID);

  if (UserMgr.IsAnonyQuestAllowedForUser(quest.GetToUserID())) {
    std::cout << "Note: anonymous questions to this user is not allowed\n";
  } else {
    std::cout << "do you want to ask this question anonymously? y\\n:";
    quest.SetIsAnonyQuest((ReadInput({std::string("y"), std::string("n")},
                                     "invalid input try again:")) == "y");
  }
  quest.SetFromUserID(this->UserMgr.GetCurrentUserID());
  std::cout << "For thread Question add question ID or -1 for new Question:";

  parentQuestID = ReadInput({-1}, 1, INT_MAX, "invalid input");
  if (parentQuestID != -1 && false == QuestMgr.is_ValidQuestID(parentQuestID)) {
    std::cout << "Parent Quesiton ID not exist";
    return;
  }
  quest.SetParentID(parentQuestID);
  std::cout << "Question:";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::getline(std::cin, QuestStr);
  quest.SetQuestStr(QuestStr);
  quest.SetQuestID(QuestionManager::GenerateID());
  try {
    this->QuestMgr.AddQuestion(quest);
  } catch (std::out_of_range& err) {
    std::cout << "Adding Question Failed!!\n"
              << quest.GetQuestID() << std::endl;
  }
  UpdateQuestionsDataBase(false);  // ////
  FillUsersQuestions();
}
void Askme::ListSystemUsers() {
  const auto& ListUsers =
      this->UserMgr.GetUsersList(); /*vector of pointers to constant user obj*/
  std::cout << std::endl;
  for (const auto& user : ListUsers)  // pair id , name
  {
    std::cout << "ID:" << user.GetUserID() << "\tName:" << (user.GetName())
              << std::endl;
  }
}
void Askme::Feeds() { this->QuestMgr.ListFeeds(); }

int Askme::ShowMenu(const std::vector<std::string>& menu) const {
  int i{1};
  int input{};
  for (const auto& str : menu) {
    std::cout << i++ << "-" << str << std::endl;
  }
  input =
      ReadInput(1, 8, std::string("Invalid number enter number in rage 1 ~ 8"));

  return input;
}

void Askme::SystemAccess() {
  int input{0};

  while (1) {
    std::cout << "1-SignUp\n2-Login\n";
    input = ReadInput(1, 2, "invalid number\n1-SignUp\n2-Login\n");
    if (input == 1) {
      if (SignUp()) {
        std::cout << "Signed up successfully!!\n";
        LoadDataBase();
      } else {
        std::cout << "Signed up failed!!\n";
      }
    } else if (input == 2) {
      if (Login()) {
        break;
      } else {
        std::cout << "Wrong user name or password!!\n";
      }
    }
  }
}
void Askme::Run() {
  this->LoadDataBase();
  this->SystemAccess();

  std::vector<std::string> menu;
  menu.push_back("Print Questions To Me");
  menu.push_back("Print Questions From Me");
  menu.push_back("Answer Question");
  menu.push_back("Delete Question");
  menu.push_back("Ask Question");
  menu.push_back("List System Users");
  menu.push_back("Feed");
  menu.push_back("Logout");

  while (true) {
    int choice = ShowMenu(menu);
    if (choice == 8) {
      this->LoadDataBase();
      this->SystemAccess();
    } else if (choice - 1 >= 0 && choice - 1 <= 7) {
      (this->*pFuncArr[choice - 1])();
    }
  }
}
