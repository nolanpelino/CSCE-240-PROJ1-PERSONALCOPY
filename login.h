// Author: Nolan Pelino
// Email: npelino@icloud.com
// Section #: 001
// Copyright 2021 Nolan Pelino
// Modified from template code @coleca24 GitHub
#ifndef LOGIN_H_
#define LOGIN_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using std::string;

const int COLS = 4;
const int ROWS = 5;

// TODO(commit 1): Commit #1 functions
void printUsers(const string data[ROWS][COLS]);
bool readUsers(string fh, string data[ROWS][COLS]);
char displayOptions();
bool validateOption(char option);
void executeOption(char option, const string data[ROWS][COLS], string);
int searchForUser(string name, const string data[ROWS][COLS]);

// TODO(commit 2): Commit #2 functions
int findAllUsers(string title, const string data[ROWS][COLS]);
bool deleteUser(string name, string data[ROWS][COLS], string fh);
string generatePassword();
string generateEmail(string name);
int checkEmpty(const string data[ROWS][COLS]);
void addUser(int index, string name, string title,
             string data[ROWS][COLS], string fh);

void printUsers(const string data[ROWS][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (j != COLS -1)
        std::cout << data[i][j] << ",";
      else
        std::cout << data[i][j] << "";
    }
    std::cout << "\n";
  }
  return;
}


bool readUsers(string fh, string data[ROWS][COLS]) {
  std::ifstream in(fh);
  char delim(',');
  string token;
  int j(0), i(0);
  if (in.is_open()) {
    string userRow;
    while (std::getline(in, userRow)) {
      std::stringstream s_line(userRow);
      j = 0;
      while (getline(s_line, token, delim)) {
          data[i][j] = token;
          j++;
      }
      i++;
    }
    in.close();
    return true;
  } else {
    in.close();
    return false;
  }
}

char displayOptions() {
  std::cout << "These are your options:" << "\n";
  std::cout << "E/e Ends the program\nP/p Calls printUsers()\nS/s Calls "
  << "searchForUser()\nF/f Calls findAllUsers()\nA/a Calls the addUser() "
  << "function\nD/d Calls the deleteUser() function" << "\n";
  char choice;
  std::cin >> choice;
  std::cin.ignore();
  char lowered = tolower(choice);
  if (validateOption(lowered))
    return lowered;

  return 'e';
}


bool validateOption(char option) {
  char lowered = tolower(option);
  switch (lowered) {
    case 'e':
      return true;
      break;
    case 'p':
      return true;
      break;
    case 's':
      return true;
      break;
    case 'f':
      return true;
      break;
    case 'a':
      return true;
      break;
    case 'd':
      return true;
      break;
  }
  return false;
}

void executeOption(char option, string data[ROWS][COLS], string fn) {
  string nameRequest;
  int matches;
  int result;
  int emptyRow;  // Sees which row is empy for addUser option
  string name, position;

  switch (option) {
    case 'p':
      printUsers(data);
      break;
    case 's':
      std::cout << "Who are you looking for?" << "\n";
      std::getline(std::cin, nameRequest);
      result = searchForUser(nameRequest, data);
      if (result == -1) {
        std::cout << "User not found." << "\n";
      } else {
        for (int i = 0; i < COLS; i++) {
          if (i == (COLS -1))
            std::cout << data[result][i] << "\n";
          else
            std::cout << data[result][i] << ", ";
        }
      }
      break;
    case 'f':
      std::cout << "What is the job title?" << "\n";
      std::getline(std::cin, nameRequest);
      matches = findAllUsers(nameRequest, data);
      std::cout << matches << " People were found with that job" << "\n";
      break;
    case 'a':
      if (checkEmpty(data) == -1) {
        std::cout << "Sorry, the database is full." << "\n";
      } else {
        std::cout << "What is the employees name?" << "\n";
        std::getline(std::cin, name);
        std::cout << "What is their position" << "\n";
        std::getline(std::cin, position);
        if (searchForUser(name, data) == -1)
          addUser(emptyRow, name, position, data, fn);
        else
          std::cout << "Sorry, the database already"
          << "contains this employee." << "\n";
      }
      break;
    case 'd':
      std::cout << "What is the employees name?" << "\n";
      std::getline(std::cin, name);
      if (searchForUser(name, data) == -1) {
        std::cout << "This employee was not found in the database." << "\n";
      } else {
        deleteUser(name, data, fn);
        std::cout << "This employee was deleted." << "\n";
      }
      break;
  }
  return;
}

int searchForUser(string name, const string data[ROWS][COLS]) {
  int i = 0;
  while (i < ROWS) {
    if (data[i][0] == name)
      return i;
    i++;
  }
  return -1;
}

int findAllUsers(string title, const string data[ROWS][COLS]) {
  int matches(0);
  for (int i = 0; i < ROWS; i++) {
    if (data[i][COLS - 1] == title)
      matches++;
  }
  return matches;
}

bool deleteUser(string name, string data[ROWS][COLS], string fh) {
  std::ofstream out(fh);
  int j(0);
  bool nameFound = false;

  for (int i = 0; i < ROWS; i++) {
    if (data[i][0] == name) {
      while (j < COLS) {
        data[i][j] = "NULL";
        j++;
      }
      nameFound = true;
    }
  }

  if (nameFound == false)
    return nameFound;

  if (out.is_open()) {
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        if (j == (COLS -1))
          out << data[i][j] << "\n";
        else
          out << data[i][j] << ",";
      }
    }
      out.close();
      return true;
    } else {
      out.close();
      return false;
      }
}

string generatePassword() {
  string password = "";
  char letterArr[8];
  for (int i = 0; i < 8; i ++) {
    if (i == 0)
      letterArr[i] = rand() % 26 + 65;
    else if (i == 1)
      letterArr[i] = rand() % 10 + 48;
    else
      letterArr[i] = rand() % 26 + 97;
  }

  for (int i = 0; i < 8; i ++) {
    password += letterArr[i];
  }
  return password;
}

string generateEmail(string name) {
  int spaceLoc;
  size_t found = name.find(" ");  // Deletes spaces in name for email
  if (found != string::npos) {
    spaceLoc = found;
    name.replace(spaceLoc, 1, "");
  }
  string combinedName = name + "@email.com";
  return combinedName;
}

int checkEmpty(const string data[ROWS][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (data[i][j] == "NULL")
      return i;
    }
  }
  return -1;
}

void addUser(int index, string name, string title,
             string data[ROWS][COLS], string fh) {
  std::ofstream out(fh);

  data[index][0] = name;
  data[index][1] = generateEmail(name);
  data[index][2] = generatePassword();
  data[index][3] = title;

  if (out.is_open()) {
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        if (j == (COLS -1))
          out << data[i][j] << "\n";
        else
          out << data[i][j] << ",";
      }
    }
      out.close();
      return;
    } else {
      out.close();
      return;
      }
}
#endif  // LOGIN_H_
