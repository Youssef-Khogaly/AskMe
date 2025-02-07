/*
 * Askme.h
 *
 *  Created on: Jan 19, 2025
 *      Author: yossef
 */

#ifndef ASKME_H_
#define ASKME_H_
#include <array>
#include <functional>
#include <initializer_list>

#include "Common.h"
#include "QuestionManager.h"
#include "UserManager.h"
class Askme {
 private:
  typedef void (Askme::*FuncPtr)();

  QuestionManager QuestMgr;
  UserManager UserMgr;
  /*Helper Funcitons*/
  template <typename T>
  static T ReadInput(T low, T high, const std::string& errorMsg);
  template <typename T>
  static T ReadInput(const std::initializer_list<T>& choices,
                     const std::string& errorMsg);
  template <typename T>
  T ReadInput(const std::initializer_list<T>& choices, T low, T high,
              const std::string& errorMsg);
  static std::string ReadInput();
  bool Login();
  void SystemAccess();
  bool SignUp();
  void LoadDataBase();
  void FillUsersQuestions();
  void PrintQuestionToMe();
  void PrintQuestionFromMe();
  void AnswerQuestion();
  void DeleteQuestion();
  void AskQuestion();
  void ListSystemUsers();
  void Feeds();
  void LoadUsers();
  void LoadQuestions();
  void UpdateDataBase(bool append);
  void UpdateQuestionsDataBase(bool append) const {
    QuestMgr.UpdateQuestionsDataBase(append);
  };
  void UpdateUsersDataBase(bool append) const {
    UserMgr.UpdateUsersDataBase(append);
  }
  int ShowMenu(const std::vector<std::string>& menu) const;

  inline static FuncPtr pFuncArr[]{&Askme::PrintQuestionToMe,
                                   &Askme::PrintQuestionFromMe,
                                   &Askme::AnswerQuestion,
                                   &Askme::DeleteQuestion,
                                   &Askme::AskQuestion,
                                   &Askme::ListSystemUsers,
                                   &Askme::Feeds};

 public:
  Askme() = default;
  Askme(const std::string& Questions_Path, const std::string& Users_Path) {
    SetDataBasePathes(Questions_Path, Users_Path);
  }
  ~Askme() = default;
  Askme(const Askme& other) = delete;
  Askme(Askme&& other) = delete;
  Askme& operator=(const Askme& other) = delete;
  Askme& operator=(Askme&& other) = delete;
  void SetDataBasePathes(const std::string& Questions_Path,
                         const std::string& Users_Path) {
    assert(Questions_Path.size() > 0);
    assert(Users_Path.size() > 0);
    this->QuestMgr.SetFilePath(Questions_Path);
    this->UserMgr.SetDataBasePath(Users_Path);
  }
  void Run();
};

#endif /* ASKME_H_ */
