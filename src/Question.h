/*
 * Question.h
 *
 *  Created on: Jan 19, 2025
 *      Author: yosse
 */

#ifndef QUESTION_H_
#define QUESTION_H_
#include <cassert>
#include <string>

#include "Common.h"
#include "User.h"
class Question {
 private:
  int QuestID;
  std::string QuestStr;
  std::string QuestAns;
  int ParentQuestID;  // == -1 no parent Question
  bool IsAnonyQuest;
  int FromUserID;
  int ToUserID;

 public:
  Question() = default;
  Question(int QuestID, const std::string& QuestStr, int FromUserID,
           int ToUserID, const std::string& QuestAns = "",
           bool IsAnonyQuest = false, int ParentQuestID = -1)
      : QuestID(QuestID),
        QuestStr(QuestStr),
        QuestAns(QuestAns),
        IsAnonyQuest(IsAnonyQuest),
        ParentQuestID(ParentQuestID),
        FromUserID(FromUserID),
        ToUserID(ToUserID) {
    assert(this->QuestID > 0);
    assert(this->QuestStr.size() != 0);
    assert(FromUserID > 0 && ToUserID > 0);
  }
  Question(const std::string& Line) {
    assert(Line.size() > 0);
    std::vector<std::string> substrs{SplitString(Line)};
    SetQuestID(StrToInt(substrs[0]));
    SetParentID(StrToInt(substrs[1]));
    SetFromUserID(StrToInt(substrs[2]));
    SetToUserID(StrToInt(substrs[3]));
    this->IsAnonyQuest = (StrToInt(substrs[4]) == 1);
    SetQuestStr(substrs[5]);
    try {
      SetAnswer(substrs.at(6));
    } catch (std::out_of_range& err) {
      SetAnswer("");
    }
  }
  ~Question() = default;
  Question(const Question& other) = default;
  Question& operator=(const Question& other) = delete;
  // getters
  int GetQuestID() const;
  int GetParentID(void) const;  // return -1 if there is no parent
  int GetToUserID() const;
  int GetFromUserID() const;
  const std::string& GetQuestStr() const;
  const std::string& GetAnswer(void) const;
  // setters
  void SetQuestID(int id);
  void SetParentID(int id);
  void SetToUserID(int id);
  void SetFromUserID(int id);
  void SetAnswer(const std::string& ans);
  void SetQuestStr(std::string const& Quest) {
    assert(Quest.size() > 0);
    this->QuestStr = Quest;
  }
  void SetIsAnonyQuest(bool anony) { this->IsAnonyQuest = anony; }
  void PrintFeedQuest() const;
  int isAnonyQuest(void) const;
  bool isAnswered(void) const;
  bool isThread(void) const;
  std::string ToStr(void) const;
  void PrintToMeQuest(void) const;
  void PrintFromMeQuest(void) const;
};

#endif /* QUESTION_H_ */
