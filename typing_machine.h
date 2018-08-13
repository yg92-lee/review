// Copyright 2018 <Author>

#ifndef TYPING_MACHINE_H_
#define TYPING_MACHINE_H_

#include <string>

#include "node.h"

class Cursor{
private:
	Node* mPrev;
	Node* mNext;
public:
	Node* getPrev() { return mPrev; }
	Node* getNext() { return mNext; }
	void setPrev(Node* node)	{ mPrev = node; }
	void setNext(Node* node)	{ mNext = node; }
};

class TypingMachine {
 private:
	Node* mHead;
	Node* mEnd;
	Cursor mCursor;
	int count;

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
