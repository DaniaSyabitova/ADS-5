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

int culcul(char op, int x, int y) {
  switch (op) {
    case '+': return x + y;
    case '-': return x - y;
    case '*': return x * y;
    case '/': return x / y;
    default: return 0;
  }
}

std::string infx2pstfx(std::string inf) {
  std::string out;
  TStack <char, 100> sta;
  for (int i = 0; i < inf.length(); i++) {
    if (pr(inf[i]) == 5) {
      out.push_back(inf[i]); //цифры сразу в строку с пробелом
      out.push_back(' ');
    } else {
        if (pr(inf[i]) == 4) {
          continue; //пропускаем пробел
        } else if (pr(inf[i]) == 0) {
          sta.push(inf[i]);
        } else if (pr(inf[i]) > pr(sta.get())) {
          sta.push(inf[i]);
        } else if (sta.isEmpty()) {
          sta.push(inf[i]);
        } else if (pr(inf[i]) == 1) {
          while (pr(sta.get()) != 0) { //до открытой скобки
            out.push_back(sta.get());
            out.push_back(' ');
            sta.pop(); //удаление скобки
          }
          sta.pop();
        } else {
            while (!sta.isEmpty() && (pr(inf[i]) <= pr(sta.get()))) {
              out.push_back(sta.get());
              out.push_back(' ');
              sta.pop();
            }
            sta.push(inf[i]);
        }
     }
  }
  while (!sta.isEmpty()) { //извлечение остатка
    out.push_back(sta.get());
    out.push_back(' ');
    sta.pop();
  }
  out.pop_back();
  return out;
}

int eval(std::string pref) {
  TStack <int, 100> stack2;
  int res = 0, x, y;
  for (int i = 0; i < pref.length(); i++) {
    if (pr(pref[i]) == 5) {
      stack2.push(pref[i]-'0');
    } else if (pr(pref[i]) < 5) {
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
