/*
 * Common.c
 *
 *  Created on: Jan 19, 2025
 *      Author: yossef
 */

#include "Common.h"

#include <cassert>
#include <iostream>
#include <sstream>
std::vector<std::string> ReadFileLines(const std::string& path) {
  std::vector<std::string> lines{};
  std::ifstream file(path);
  std::string str;

  // check opening file
  assert(file.fail() == false);

  while (std::getline(file, str)) {
    if (str.size() == 0) continue;
    lines.push_back(str);
  }
  file.close();

  return lines;
}
void WriteFileLines(const std::string& path,
                    const std::vector<std::string>& Lines, bool append) {
  auto status = (append) ? (std::ios::app | std::ios::out)
                         : (std::ios::trunc | std::ios::out);
  std::ofstream file(path, status);
  assert(file.fail() == false);

  for (const auto& line : Lines) {
    file << line << "\n";
  }
  file.close();
}
void WriteFileLines(const std::string& path, const std::string& Line,
                    bool append) {
  auto status = (append) ? (std::ios::app | std::ios::out)
                         : (std::ios::trunc | std::ios::out);
  std::ofstream file(path, status);
  assert(file.fail() == false);

  file << Line << "\n";

  file.close();
}
/*
 * 0 1 2 3 4 5 6 7 8 9 10 11,
 * y o s s e f , a b c d   e
 *
 * prev = 6
 * pos = 12
 *
 * 12 - 6 - 1 = 5
 *
 * */
std::vector<std::string> SplitString(const std::string& str,
                                     std::string const& Deli) {
  std::vector<std::string> ret{};
  ret.reserve(7);
  size_t pos = 0;
  size_t prevPos = 0;
  while ((pos = str.find(Deli, prevPos)) != std::string::npos) {
    try {
      const auto& _s =
          str.substr(prevPos,
                     pos - prevPos);  // - 1 to not add current deli;

      prevPos = pos + 1;
      if (_s.size() != 0) ret.push_back(_s);

    } catch (const std::out_of_range& err) {
      std::cout << err.what() << std::endl;
    }
  }
  if (prevPos < str.size()) {
    try {
      ret.push_back(str.substr(prevPos, str.size() - prevPos));
    } catch (const std::out_of_range& err) {
      // std::cout << __FILE__ << " , " << __LINE__ << std::endl;
      std::cout << err.what() << std::endl;
    }
  }
  return ret;
}

int StrToInt(const std::string& str) {
  assert(str.size() > 0);
  std::istringstream iss(str);
  int ret;
  iss >> ret;
  return ret;
}
