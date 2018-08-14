// Copyright 2018 <Author>

#include "typing_machine.h"

TypingMachine::TypingMachine() {
  mHead = new Node(NULL_CHAR);
  mCursor = mTail = mHead; 
  count = 0;
  return;
}


void TypingMachine::HomeKey() {
  mCursor = mHead;
  return;
}

void TypingMachine::EndKey() {
  mCursor = mTail;
  return;
}

void TypingMachine::LeftKey() {
  if (mCursor->GetPreviousNode()) {
    mCursor = mCursor->GetPreviousNode();
  }
  return;
}

void TypingMachine::RightKey() {
  if (mCursor->GetNextNode()) {
    mCursor = mCursor->GetNextNode();
  }
  return;
}

bool TypingMachine::IsValidKey(char key) {
  return key >= 0x20 && key <= 0x7E;
}

bool TypingMachine::CanType() {
  return count < MAX_TYPED_TEXT_LENGTH;
}

bool TypingMachine::TypeKey(char key) {
  if (!IsValidKey(key) || !CanType()) {
    return false;
  }

  Node* prevOfCursor = mCursor->GetPreviousNode();
  mCursor->InsertPreviousNode(key);
  if (prevOfCursor == nullptr) {
    mHead = mCursor->GetPreviousNode();
  }
  count++;
  
  return true;
}

bool TypingMachine::EraseKey() {
  if (mCursor->GetPreviousNode() == nullptr) {
    return false;
  }

  Node* prevOfNodeToErase = mCursor->GetPreviousNode()->GetPreviousNode();
  mCursor->ErasePreviousNode();
  if (prevOfNodeToErase == nullptr) {
    mHead = mCursor;
  }
  count--;
  
  return true;
}

std::string TypingMachine::Print(char separator) {
  std::string str = "";
  
  Node* cur = mHead;
  do{
    if (cur == mCursor && separator != NULL_CHAR) {
      str.append(1, separator);
    }
    if (cur != mTail) {
      str.append(1, cur->GetData());
    }
    cur = cur->GetNextNode();
  } while(cur != nullptr);

  return str;
}
