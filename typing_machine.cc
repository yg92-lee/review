// Copyright 2018 <Author>

#include "typing_machine.h"

TypingMachine::TypingMachine() {
	mCursor = nullptr;
	mHead = nullptr;
	mEnd = nullptr;
  return;
}

void TypingMachine::HomeKey() {
	mCursor = mHead;
  return;
}

void TypingMachine::EndKey() {
	mCursor = mEnd;
  return;
}

void TypingMachine::LeftKey() {
	if (mCursor->GetPreviousNode() != nullptr) {
		mCursor = mCursor->GetPreviousNode();
	}
  return;
}

void TypingMachine::RightKey() {
	if (mCursor != nullptr) {
		mCursor = mCursor->GetNextNode();
	}
  return;
}

bool TypingMachine::TypeKey(char key) {
	if (key < 0x20 || key > 0x7E) {
		return false;
	}

	if (mHead == nullptr) {
		mCursor = new Node(key);
		mHead = nullptr;
		mEnd = mCursor;
	}
	else if (mCursor == nullptr) {
		mEnd->InsertNextNode(key);
		mEnd = mEnd->GetNextNode();
	}
	else {
		mCursor->InsertPreviousNode(key);
		if (mHead == mCursor) {
			mHead = mCursor->GetPreviousNode();
		}
	}
  return true;
}

bool TypingMachine::EraseKey() {
	if (mCursor->GetNextNode() == nullptr) {
		return false;
	}

	mCursor->ErasePreviousNode();
	
  return true;
}

std::string TypingMachine::Print(char separator) {
	std::string str = "";

	Node* cur = mHead;
	if (cur == nullptr && separator != 0) {
	  str.push_back(separator);
		cur = mCursor;
	}

	while (cur != nullptr) {
		str.push_back(cur->GetData());
		cur = cur->GetNextNode();
		if (mCursor == cur && separator != 0) {
			str.push_back(separator);
		}
	} 

	return str;
}
