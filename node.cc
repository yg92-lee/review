// Copyright 2018 <Author>

#include "node.h"

Node::Node(char data) {
  mChar = data;
  mNextNode = nullptr;
  mPrevNode = nullptr;
  return;
}

char Node::GetData() {
  return mChar;
}

Node* Node::GetPreviousNode() {
  return mPrevNode;
}

Node* Node::GetNextNode() {
  return mNextNode;
}

Node* Node::InsertPreviousNode(char data) {
  Node* node = new Node(data);
  node->mPrevNode = this->mPrevNode;
  if (node->mPrevNode != nullptr) {
    node->mPrevNode->mNextNode = node;
  }
  node->mNextNode = this;
  this->mPrevNode = node;

  return node;
}

Node* Node::InsertNextNode(char data) {
  Node* node = new Node(data);
  node->mNextNode = this->mNextNode;
  if (node->mNextNode != nullptr) {
    node->mNextNode->mPrevNode = node;
  }
  node->mPrevNode = this;
  this->mNextNode = node;

  return node;
}

bool Node::ErasePreviousNode() {
  Node* node = this->mPrevNode;
  if (node == nullptr) {
    return false;
  }

  this->mPrevNode = node->mPrevNode;
  if (this->mPrevNode != nullptr) {
    this->mPrevNode->mNextNode = this;
  }
  delete node;

  return true;
}

bool Node::EraseNextNode() {
  Node* node = this->mNextNode;
  if (node == nullptr) {
    return false;
  }

  this->mNextNode = node->mNextNode;
  if (this->mNextNode != nullptr) {
    this->mNextNode->mPrevNode = this;
  }
  delete node;

  return true;
}
