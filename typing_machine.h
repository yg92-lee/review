// Copyright 2018 <Author>

#ifndef TYPING_MACHINE_H_
#define TYPING_MACHINE_H_

#include <string>

#include "node.h"

#define MAX_TYPED_TEXT_LENGTH 100
#define NULL_CHAR '\0'

class TypingMachine {
 private:
  Node* mHead;
  Node* mTail;
  Node* mCursor;
  int count;

  bool IsValidKey(char key);
  bool CanType();

 public:
  TypingMachine();
  void HomeKey();
  void EndKey();
  void LeftKey();
  void RightKey();
  bool TypeKey(char key);
  bool EraseKey();
  std::string Print(char separator);
};

#endif  // TYPING_MACHINE_H_
