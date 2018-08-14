// Copyright 2018 Minkyu Jo

#include <string>

#include "node.h"
#include "node_test.h"
#include "test.h"

#define MAX_NUM 0x7fffffff

#define INSERT_PREV 0
#define INSERT_NEXT 1
#define ERASE_PREV 2
#define ERASE_NEXT 3
#define GO_NEXT 4
#define GO_PREV 5

static unsigned int seed = 1;

void srand(int newseed) {
  seed = (unsigned)newseed & 0x7fffffffU;
}

int rand(void) {
  seed = (seed * 1103515245U + 12345U) & 0x7fffffffU;
  return (int)seed;
}

int getKey() {
  int ret = rand() % 6;
  return ret;
}

class NodeConstructorTestSuite
{
private:
  static void SingleNodeTest() {
    Node *node = new Node('A');
    ASSERT_EQ(node->GetData(), 'A');
    delete node;
  }

public:
  static void RunTest() {
    SingleNodeTest();
    // add more..
  }
};

class InsertBasicTestSuite
{
private:
  static void InsertNextTest() {
    Node *node = new Node('B');
    node->InsertNextNode('C');
    ASSERT_EQ(node->GetNextNode()->GetData(), 'C');

    delete node->GetNextNode();
    delete node;
  }

  static void InsertPrevTest() {
    Node *node = new Node('B');
    node->InsertPreviousNode('A');
    ASSERT_EQ(node->GetPreviousNode()->GetData(), 'A');

    delete node->GetNextNode();
    delete node;
  }

public:
  static void RunTest() {
    InsertNextTest();
    InsertPrevTest();
  }
};


class InsertAdvancedTestSuite
{
private:
  static void InsertNextAdvancedTest(std::string str) {
    Node* head = new Node(str.c_str()[0]);
    Node* node = head;
    Node* nodeToBeDeleted;

    for (unsigned int i = 1; i < str.length(); i++) {
      node->InsertNextNode(str.c_str()[i]);
      node = node->GetNextNode();
    }

    node = head;
    for (unsigned int i = 0; i < str.length(); i++) {
      nodeToBeDeleted = node;
      ASSERT_EQ(node->GetData(), str.c_str()[i]);
      node = node->GetNextNode();
      delete nodeToBeDeleted;
    }
  }

  static void InsertPrevAdvancedTest(std::string str) {
    Node* tail = new Node(str.c_str()[str.length() - 1]);
    Node* node = tail;
    Node* nodeToBeDeleted;

    for (int i = str.length() - 2; i >= 0; i--) {
      node->InsertPreviousNode(str.c_str()[i]);
      node = node->GetPreviousNode();
    }

    node = tail;
    for (int i = str.length() - 1; i >= 0; i--) {
      nodeToBeDeleted = node;
      ASSERT_EQ(node->GetData(), str.c_str()[i]);
      node = node->GetPreviousNode();
      delete nodeToBeDeleted;
    }
  }

public:
  static void RunTest() {
    std::string str = "ABCDEFG";

    InsertNextAdvancedTest(str);
    InsertPrevAdvancedTest(str);
  }
};

class EraseBasicTestSuite
{
private:
  static void EraseNextTest() {
    Node *node = new Node('B');
    node->InsertNextNode('C');
    node->EraseNextNode();

    const Node* nullNode = nullptr;
    ASSERT_EQ(node->GetNextNode(), nullNode);

    delete node;
  }

  static void ErasePrevTest() {
    Node *node = new Node('B');
    node->InsertPreviousNode('A');
    node->ErasePreviousNode();

    const Node* nullNode = nullptr;
    ASSERT_EQ(node->GetPreviousNode(), nullNode);

    delete node;
  }

public:
  static void RunTest() {
    EraseNextTest();
    ErasePrevTest();
  }
};

class EraseAdvancedTestSuite
{
private:
  static void EraseAdvancedNextTest() {
    char start = 'A';
    Node* startNode = new Node(start);
    Node* curNode = startNode;

    for (int i = 1; i < 20; i++) {
      curNode->InsertNextNode(start + i);
      curNode = curNode->GetNextNode();
    }

    curNode = startNode;
    for (int i = 1; i < 20; i++) {
      curNode->EraseNextNode();
    }

    const Node* nullNode = nullptr;
    ASSERT_EQ(curNode->GetNextNode(), nullNode);

    delete curNode;
  }

  static void EraseAdvancedPrevTest() {
    char endChar = 'Z';
    Node* endNode = new Node(endChar);
    Node* curNode = endNode;

    for (int i = 1; i < 20; i++) {
      curNode->InsertPreviousNode(endChar - i);
      curNode = curNode->GetPreviousNode();
    }

    curNode = endNode;
    for (int i = 1; i < 20; i++) {
      curNode->ErasePreviousNode();
    }

    const Node* nullNode = nullptr;
    ASSERT_EQ(curNode->GetPreviousNode(), nullNode);

    delete curNode;
  }

public:
  static void RunTest() {
    EraseAdvancedNextTest();
    EraseAdvancedPrevTest();
  }
};

class AdvancedTestSuite
{
private:
  static void MaxLengthTest() {
    char start = 'A';
    Node* startNode = new Node(start);
    Node* curNode = startNode;

    for (int j = 0; j < 10; j++) {
      //A - T
      for (int i = 1; i < 20; i++) {
        curNode->InsertNextNode(start + i);
        curNode = curNode->GetNextNode();
      }
    }

    curNode = startNode;
    const Node* nullNode = nullptr;

    for (int i = 0; i < 100; i++) {
      ASSERT_NE(curNode, nullNode);
      curNode = curNode->GetNextNode();
    }
  }

  static void RandomTest() {
    char start = 'A';
    Node* node = new Node(start);

    for (int i = 0; i < 100000; i++) {
      switch (getKey()) {
      case INSERT_PREV:
        node->InsertPreviousNode(rand() % 255);
        break;
      case INSERT_NEXT:
        node->InsertNextNode(rand() % 255);
        break;
      case ERASE_PREV:
        node->ErasePreviousNode();
        break;
      case ERASE_NEXT:
        node->EraseNextNode();
        break;
      case GO_NEXT:
        if (node->GetNextNode()) {
          node = node->GetNextNode();
        }
        break;
      case GO_PREV:
        if (node->GetPreviousNode()) {
          node = node->GetPreviousNode();
        }
        break;
      default:
        break;
      }
    }

    while (node != nullptr) {
      if (node->GetNextNode()) {
        node->EraseNextNode();
        continue;
      }
      if (node->GetPreviousNode()) {
        node->ErasePreviousNode();
        continue;
      }
      break;
    }

    Node* nullNode = nullptr;
    ASSERT_EQ(node->GetPreviousNode(), nullNode);
    ASSERT_EQ(node->GetNextNode(), nullNode);
    delete node;
  }

public:
  static void RunTest() {
    MaxLengthTest();
    RandomTest();
  }
};

void NodeTest() {
  NodeConstructorTestSuite::RunTest();
  InsertBasicTestSuite::RunTest();
  InsertAdvancedTestSuite::RunTest();
  EraseBasicTestSuite::RunTest();
  EraseAdvancedTestSuite::RunTest();
  AdvancedTestSuite::RunTest();
  // add more..
}