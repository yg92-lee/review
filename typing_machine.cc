// Copyright 2018 <Author>

#include "typing_machine.h"

TypingMachine::TypingMachine() {
	mCursor.setPrev(nullptr);
	mCursor.setNext(nullptr);
	mHead = nullptr;
	mEnd = nullptr;
	count = 0;
  return;
}


void TypingMachine::HomeKey() {
	mCursor.setPrev(nullptr);
	mCursor.setNext(mHead);
  return;
}

void TypingMachine::EndKey() {
	mCursor.setPrev(mEnd);
	mCursor.setNext(nullptr);
  return;
}

void TypingMachine::LeftKey() {
	if (mCursor.getPrev() != nullptr) {
		mCursor.setNext(mCursor.getPrev());
		mCursor.setPrev(mCursor.getPrev()->GetPreviousNode());
	}
  return;
}

void TypingMachine::RightKey() {
	if (mCursor.getNext() != nullptr) {
		mCursor.setPrev(mCursor.getNext());
		mCursor.setNext(mCursor.getNext()->GetNextNode());
	}
  return;
}

bool TypingMachine::TypeKey(char key) {
	if (key < 0x20 || key > 0x7E || count > 100) {
		return false;
	}

	if (mCursor.getPrev() == nullptr && mCursor.getNext() == nullptr) {
		mCursor.setPrev(new Node(key));
		mHead = mCursor.getPrev();
		mEnd = mCursor.getPrev();
		count = 1;
	}
	else if (mCursor.getPrev() == nullptr) {
		Node* next = mCursor.getNext();
		next->InsertPreviousNode(key);
		mCursor.setPrev(next->GetPreviousNode());
		mHead = next->GetPreviousNode();
	}
	else{
		Node* prev = mCursor.getPrev();
		prev->InsertNextNode(key);
		mCursor.setPrev(prev->GetNextNode());
		if (mCursor.getNext() == nullptr) {
			mEnd = prev->GetNextNode();
		}
	}
	count++;
	
  return true;
}

bool TypingMachine::EraseKey() {
	if (mCursor.getPrev() == nullptr) {
		return false;
	}
	if (mHead == mEnd && (mCursor.getNext() == nullptr || mCursor.getPrev() == nullptr)) {
		delete mHead;
		mHead = mEnd = nullptr;
		mCursor.setNext(nullptr);
		mCursor.setPrev(nullptr);
		count = 0;
		return true;
	}

	Node* temp = mCursor.getPrev();
	mCursor.setPrev(temp->GetPreviousNode());

	if (mCursor.getNext() != nullptr) {
		mCursor.getNext()->ErasePreviousNode();
		if (mCursor.getNext()->GetPreviousNode() == nullptr) {
			mHead = mCursor.getNext();
			//mCursor.setPrev(nullptr);
		}
	}
	else {
		Node* prevOfEnd = temp->GetPreviousNode();
		if (prevOfEnd != nullptr) {
			prevOfEnd->EraseNextNode();

			if (prevOfEnd->GetPreviousNode() == nullptr) {
				mEnd = mHead;
			}
			else if (prevOfEnd->GetNextNode() == nullptr) {
				mEnd = prevOfEnd;
			}
		}
	}
	count--;
	
  return true;
}

std::string TypingMachine::Print(char separator) {
	std::string str = "";
	if (mHead == nullptr)	{
		if(separator != 0)	str.append(1, separator);
		return str;
	}
	
	Node* cur = mHead;
	do{
		if (mCursor.getNext() == cur && separator != 0) {
			str.append(1, separator);
		}
		str.append(1, cur->GetData());
		cur = cur->GetNextNode();
	} while(cur != nullptr);
	
	if (mCursor.getNext() == nullptr && separator != 0) {
		str.append(1, separator);
	}

	return str;
}
