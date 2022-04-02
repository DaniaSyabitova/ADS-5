// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int pr(char op) {
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
  TStack <char, 100> sta1;
  for (int i = 0; i < inf.length(); i++) {
    if (pr(inf[i]) == 5) {
      res.push_back(inf[i]); //цифры сразу в строку с пробелом
      res.push_back(' ');
    } else {
        if (pr(inf[i]) == 4) {
          continue; //пропускаем пробел
        } else if (pr(inf[i]) == 0) {
          sta1.push(inf[i]);
        } else if (pr(inf[i]) > pr(sta1.get())) {
          sta1.push(inf[i]);
        } else if (sta1.isEmpty()) {
          sta1.push(inf[i]);
        } else if (pr(inf[i]) == 1) {
          while (pr(sta1.get()) != 0) { //до открытой скобки
            res.push_back(sta1.get());
            res.push_back(' ');
            sta1.pop(); //удаление скобки
          }
          sta1.pop();
        } else {
            while (!sta1.isEmpty() && (pr(inf[i]) <= pr(sta1.get()))) {
              res.push_back(sta1.get());
              res.push_back(' ');
              sta1.pop();
            }
            sta1.push(inf[i]);
        }
     }
  }
  while (!sta1.isEmpty()) { //извлечение остатка
    res.push_back(sta1.get());
    res.push_back(' ');
    sta1.pop();
  }
  res.pop_back();
  return res;
}      
int culcul(char op, int x, int y) {
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
  for (int i = 0; i < pref.length(); i++) {
    if (pr(pref[i] == 5)) {
      stack2.push(pref[i]);
    } else if (pr(pref[i]) < 4) {
      y = stack2.get();
      stack2.pop();
      x = stack2.get();
      stack2.pop();
      stack2.push(culcul(pref[i], x, y)); //результат предыдущего действия
    }
  }
  res = stack2.get();
  return res;
}
