// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int priority (char op) {
    switch (op) {
      case '(': return 0;
      case ')': return 1;
      case '+': return 2;
      case '-': return 2;
      case '*': return 3;
      case '/': return 3;
      case ' ': return 4;
      default: return 5; //цифры
    }
  }

std::string infx2pstfx(std::string inf) {
  std::string res;
  TStack <char, 100> stack1;
  for (int i = 0; i < inf.length(); i++) {
    if (priority(inf[i] == 5)) {
      res.push_back(inf[i]); //цифры сразу в строку с пробелом
      res.push_back(' ');
    }
    else {
      if (priority(inf[i] == 4)) {
        continue; //пропускаем пробел
      } else if (priority(inf[i] == 0) {
        stack1.push(inf[i]);
      } else if (priority(inf[i] > priority(stack1.get())) {
        stack1.push(inf[i]);
      } else if (stack1.isEmpty()) {
        stack1.push(inf[i]);
      } else if (priority(inf[i] == 1) {
        while (priority(stack1.get()) != 0) { //до открытой скобки
          res.push_back(stack1.get());
          res.push_back(' ');
          stack1.pop(); //удаление скобки
        }
      }
      else {
        while ((!stack1.isEmpty()) && (priority(inf[i]) <= priority(stack1.get()))) {
          res.push_back(stack1.get());
          res.push_back(' ');
          stack1.pop();
        }
        stack1.push(inf[i]);
      }
    }
  }
  while (!stack1.isEmpty()) { //извлечение остатка
    res.push_back(stack1.get());
    res.push_back(' ');
    stack1.pop();
  }
  res.pop_back();
  return res;
}
                 
int culcul (char op; int x, int y) {
  switch (op) {
    case '+': return x + y;
    case '-': return x - y;
    case '*': return x * y;
    case '/': return x / y;
    default: return 0;
  }
}

int eval(std::string pref) {
  TStack <char, 100> stack2;
  int res = 0;
  int x, y;
  for (int i = 0; i < pref.lenght(); i++) {
    if (priority(pref[i] == 5) {
      stack2.push(pref[i]);
    } else if (priority(pref[i]) < 4) {
      y = stack2.get();
      stack2.pop();
      x = stack2.get();
      stack2.pop();
      stack2.push(culcul(pref[i], x, y)); //помещаем результат предыдущего действия
    }
  }
  res = stack2.get();
  return res;
}
