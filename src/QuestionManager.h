/*
 * QuestionManager.h
 *
 *  Created on: Jan 19, 2025
 *      Author: yosse
 */

#ifndef QUESTIONMANAGER_H_
#define QUESTIONMANAGER_H_

#include <iostream>
#include <map>
#include <string>

#include "Common.h"
#include "Question.h"
class QuestionManager {
 private:
  std::string FilePath{};
  /*map question id to all this question threads*/
  std::map<int, std::vector<int>> QuestID_Threads_Map{};
  /*Map question ID to Question Object*/
  std::map<int, Question> QuestID_QuestObj_Map{};
  inline static int LastID = 0;

 public:
  QuestionManager() = default;
  QuestionManager(std::string const& FilePath) : FilePath(FilePath) {};
  ~QuestionManager() = default;
  QuestionManager(const QuestionManager& other) = default;
  QuestionManager(QuestionManager&& other) = default;
  QuestionManager& operator=(const QuestionManager& other) = default;
  QuestionManager& operator=(QuestionManager&& other) = default;
  inline void QuestionsClear() {
    this->QuestID_QuestObj_Map.clear();
    this->QuestID_Threads_Map.clear();
  };
  void LoadQuestions();
  void UpdateQuestionsDataBase(bool append) const;
  void AddQuestion(Question& quest);
  void FillUserQuestions(User& user) const;
  /*
   * over write if Question is already answered
   * */
  void SetFilePath(std::string const& path) {
    assert(path.size() > 0);
    this->FilePath = path;
  }
  std::string const& GetFilePath() { return (this->FilePath); }
  void AnswerQuestion(int QuestID, const std::string& Ans);
  void DeleteQuestion(int QuestID);
  void DeleteAnswer(int QuestID);
  void PrintToUserQuests(const User& user) const;
  void PrintFromUserQuests(const User& user) const;
  const Question& GetQuestionObj(int QuestID) const;
  void ListFeeds() const;
  bool is_ValidQuestID(int id) const {
    if (this->QuestID_QuestObj_Map.count(id) == 1) return true;

    return false;
  }
  static int GenerateID() { return (++LastID); }
  const std::map<int, Question>& GetQuestID_QuestObj_Map(void) const {
    return (this->QuestID_QuestObj_Map);
  }
  //  throw std::out_of_range if there is no quest with this id
  int GetToUserID(int QuestID) {
    QuestID_QuestObj_Map.at(QuestID).GetToUserID();
  }
  // throw std::out_of_range if there is no quest with this id
  int GetFromUserID(int QuestID) {
    return QuestID_QuestObj_Map.at(QuestID).GetFromUserID();
  }
  bool is_valid_User_to_answer(int UserID, int QuestID) {
    if (GetToUserID(QuestID) == UserID) return true;

    return false;
  }
};

#endif /* QUESTIONMANAGER_H_ */
