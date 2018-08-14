// Copyright 2018 Minkyu Jo


#include "typing_machine.h"
#include "typing_machine_test.h"
#include "test.h"

const int KEY_START = 259;
const int KEY_LEFT = 259;
const int KEY_RIGHT = 260;
const int KEY_HOME = 261;
const int KEY_END = 262;
const int KEY_DEL = 263;
const int KEY_NUM = 6;

static unsigned int seed = 1;

void srand(int newseed) {
  seed = (unsigned)newseed & 0x7fffffffU;
}

int rand(void) {
  seed = (seed * 1103515245U + 12345U) & 0x7fffffffU;
  return (int)seed;
}

int getKey() {
  int ret = (rand() % KEY_NUM) + KEY_START;
  return ret;
}

void DoKeyTest(TypingMachine& tm, int key)
{
  switch (key) {
    case KEY_LEFT: {
      tm.LeftKey();
      break;
    }
    case KEY_RIGHT: {
      tm.RightKey();
      break;
    }
    case KEY_HOME: {
      tm.HomeKey();
      break;
    }
    case KEY_END: {
      tm.EndKey();
      break;
    }
    case KEY_DEL: {
      tm.EraseKey();
      break;
    }
    default: {
      tm.TypeKey(key);
      break;
    }
  }
}


class TmConstructorTestSuite
{
private:
  static void BarSeparatorTest() {
    TypingMachine tm;
    ASSERT_EQ(tm.Print('|'), std::string("|"));
  }

public:
  static void RunTest() {
    BarSeparatorTest();
    // add more..
  }
};

class TmTypeTestSuite
{
private:
  static void TypeTest(std::string str) {
    TypingMachine tm;
    std::string result = "ABC|DEFG";

    for (int i = 0; i < (int)(int)str.length(); i++) {
      DoKeyTest(tm, str.c_str()[i]);
    }

    DoKeyTest(tm, KEY_LEFT);
    DoKeyTest(tm, KEY_LEFT);
    DoKeyTest(tm, KEY_LEFT);
    DoKeyTest(tm, KEY_LEFT);

    ASSERT_EQ(tm.Print('|'), result);
  }

public:
  static void RunTest() {
    std::string testStr = "ABCDEFG";

    TypeTest(testStr);
    // add more..
  }
};

class TmEraseTestSuite
{
private:
  static void EraseTest(std::string str) {
    TypingMachine tm;
    std::string result = "|DEFG";

    for (int i = 0; i < (int)str.length(); i++) {
      DoKeyTest(tm, str.c_str()[i]);
    }

    DoKeyTest(tm, KEY_LEFT);
    DoKeyTest(tm, KEY_LEFT);
    DoKeyTest(tm, KEY_LEFT);
    DoKeyTest(tm, KEY_LEFT);

    DoKeyTest(tm, KEY_DEL);
    DoKeyTest(tm, KEY_DEL);
    DoKeyTest(tm, KEY_DEL);

    ASSERT_EQ(tm.Print('|'), result);
  }

public:
  static void RunTest() {
    std::string testStr = "ABCDEFG";

    EraseTest(testStr);
    // add more..
  }
};

class TmCursorTestSuite
{
private:
  static void CursorTest(std::string str) {
    TypingMachine tm;
    std::string result = "ABC|DEFG";

    for (int i = 0; i < (int)str.length(); i++) {
      DoKeyTest(tm, str.c_str()[i]);
    }

    DoKeyTest(tm, KEY_HOME);
    DoKeyTest(tm, KEY_RIGHT);
    DoKeyTest(tm, KEY_END);
    DoKeyTest(tm, KEY_LEFT);
    DoKeyTest(tm, KEY_HOME);
    DoKeyTest(tm, KEY_RIGHT);
    DoKeyTest(tm, KEY_END);

    DoKeyTest(tm, KEY_LEFT);
    DoKeyTest(tm, KEY_LEFT);
    DoKeyTest(tm, KEY_LEFT);
    DoKeyTest(tm, KEY_LEFT);
    DoKeyTest(tm, KEY_LEFT);
    DoKeyTest(tm, KEY_RIGHT);

    ASSERT_EQ(tm.Print('|'), result);
  }

public:
  static void RunTest() {
    std::string testStr = "ABCDEFG";

    CursorTest(testStr);
    // add more..
  }
};

class TmStressTestSuite
{
private:
  static void StressTest() {
    TypingMachine tm;
    std::string result = "|";

    for (int i = 0; i < 100000; i++) {
      DoKeyTest(tm, getKey());
    }

    tm.EndKey();
    for (int i = 0; i < 100; i++) {
      tm.EraseKey();
    }

    ASSERT_EQ(tm.Print('|'), result);
  }

public:
  static void RunTest() {
    StressTest();
    // add more..
  }
};

void TypingMachineTest() {
  TmConstructorTestSuite::RunTest();
  TmTypeTestSuite::RunTest();
  TmEraseTestSuite::RunTest();
  TmCursorTestSuite::RunTest();
  TmStressTestSuite::RunTest();
  // add more..
}