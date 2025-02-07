/*
 * QuestionManager.cpp
 *
 *  Created on: Jan 19, 2025
 *      Author: yossef
 */

#include "QuestionManager.h"

#include <algorithm>
void QuestionManager::LoadQuestions() {
  QuestionsClear();

  std::vector<std::string> lines = ReadFileLines(this->FilePath);

  for (const auto& line : lines) {
    Question quest(line);
    LastID = std::max(quest.GetQuestID(), LastID);
    this->AddQuestion(quest);
    // last id 'd be the max
  }
}
void QuestionManager::UpdateQuestionsDataBase(bool append) const {
  for (const auto& pair : this->QuestID_QuestObj_Map) {
    WriteFileLines(FilePath, pair.second.ToStr(), append);
    append = true;
  }
}
/*
 * if quest id exist  will add it as thread question
 * */
void QuestionManager::AddQuestion(Question& Quest) {
  // Quest.SetQuestID(LastID);
  QuestID_QuestObj_Map.insert(std::make_pair(Quest.GetQuestID(), Quest));

  if (Quest.isThread()) {
    QuestID_Threads_Map.at(Quest.GetParentID()).push_back(Quest.GetQuestID());
  } else {
    QuestID_Threads_Map.insert(
        std::make_pair(Quest.GetQuestID(), std::vector{Quest.GetQuestID()}));
  }
}

void QuestionManager::FillUserQuestions(User& user) const {
  user.ClearQuestIDFromMe();
  user.ClearThreadsID();
  for (const auto& pair :
       this->QuestID_QuestObj_Map)  // pair<question id , Question obj>
  {
    const auto& Quest = pair.second;
    if (Quest.GetFromUserID() == user.GetUserID()) {
      user.AddQuestIDFromMe(Quest.GetQuestID());
    } else if (Quest.GetToUserID() == user.GetUserID()) {
      if (Quest.isThread()) {
        user.AddThreadIDToME(Quest.GetParentID(), Quest.GetQuestID());
      } else {
        user.AddThreadIDToME(Quest.GetQuestID(), Quest.GetQuestID());
      }
    }
  }
}
const Question& QuestionManager::GetQuestionObj(int QuestID) const {
  return (this->QuestID_QuestObj_Map.at(QuestID));
}
void QuestionManager::PrintToUserQuests(const User& user) const {
  std::cout << "\n";
  const auto& QuestID_ThreadsID_ToUserMap = user.GetQuestID_ThreadsID_Map();
  if (QuestID_ThreadsID_ToUserMap.size() == 0) {
    std::cout << "No Questions to you\n";
    return;
  }
  for (const auto& pair :
       QuestID_ThreadsID_ToUserMap)  // pair <int , vector<int>>
  {
    for (const auto& QuestID : pair.second) {
      GetQuestionObj(QuestID).PrintToMeQuest();
    }
  }
  std::cout << "\n";
}

void QuestionManager::PrintFromUserQuests(const User& user) const {
  const auto& QuestsIdsVec = user.GetQuestIDsFromMe();
  std::cout << "\n";
  if (QuestsIdsVec.size() == 0) {
    std::cout << "You did not ask any questions before\n";
    return;
  }
  for (const auto& QuestID : QuestsIdsVec) {
    try {
      GetQuestionObj(QuestID).PrintFromMeQuest();  // /////////////////////
    } catch (std::out_of_range& err) {
      std::cout << "map out of range , quest id = " << QuestID << "\n";
      std::cerr << err.what() << "\n";
    }
  }
  std::cout << "\n";
}

void QuestionManager::AnswerQuestion(int QuestID, const std::string& Ans) {
  try {
    this->QuestID_QuestObj_Map.at(QuestID).SetAnswer(Ans);
  } catch (std::out_of_range& err) {
    throw;
  }
}
void QuestionManager::DeleteQuestion(int QuestID) {
  auto& QuestObj = this->QuestID_QuestObj_Map.at(QuestID);
  /*if its a thread Question Delete it from threads vectors*/
  if (QuestObj.isThread()) {
    int ParentID = QuestObj.GetParentID();
    auto& ThreadVec = this->QuestID_Threads_Map.at(ParentID);
    const auto& _pos = std::find(ThreadVec.begin(), ThreadVec.end(), QuestID);
    ThreadVec.erase(_pos);
  }
  /*delete Question Object from the map*/
  this->QuestID_QuestObj_Map.erase(QuestID);
  QuestID_Threads_Map.erase(QuestID);
}

void QuestionManager::DeleteAnswer(int QuestID) {
  auto& QuestObj = this->QuestID_QuestObj_Map.at(QuestID);
  QuestObj.SetAnswer("");
}

void QuestionManager::ListFeeds() const {
  for (const auto& pair : this->QuestID_QuestObj_Map)  // pair int id, quest obj
  {
    pair.second.PrintFeedQuest();
  }
}
