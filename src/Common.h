/*
 * Common.h
 *
 *  Created on: Jan 19, 2025
 *      Author: yossef
 */

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#ifndef COMMON_H_
#define COMMON_H_

std::vector<std::string> ReadFileLines(const std::string& path);
void WriteFileLines(const std::string& path,
                    const std::vector<std::string>& Lines, bool append = true);

void WriteFileLines(const std::string& path, const std::string& Line,
                    bool append = true);
std::vector<std::string> SplitString(const std::string& str,
                                     std::string const& Deli = ",");

int StrToInt(const std::string& str);

#endif /* COMMON_H_ */
