#include "../include/OptParser.h"
#include "catch.hpp"

class testOpt : public CmdLineOptParser {
  bool Option(const char c, const char* info) {
    if (c == 'x') {
      if (info == nullptr) {
        return true;
      }
      int i;
      for (i = 0; info[i]; i++)
        ;
      if (i > 10) {
        return false;
      }

      return true;
    } else {
      return false;
    }
  }
};

TEST_CASE("Arguments parsed", "[parsing]") {
  CmdLineOptParser* parser;
  testOpt obj;
  parser = &obj;

  const char* arg0 = "programname";
  const char* arg1 = "-x";
  const char* arg2 = "-x=wert";
  const char* arg3 = "-xyz";
  const char* arg4 = "-x";
  const char* arg5 = "wert1";
  char* args[] = {const_cast<char*>(arg0), const_cast<char*>(arg1),
                  const_cast<char*>(arg2), const_cast<char*>(arg3),
                  const_cast<char*>(arg4), const_cast<char*>(arg5)};
  REQUIRE(parser->Parse(6, args) == true);
}

TEST_CASE("False for bad arguments", "[parsing]") {
  CmdLineOptParser* parser;
  testOpt obj;
  parser = &obj;
  SECTION("false for bad argument values") {
    const char* arg0 = "programname";
    const char* arg1 = "-x";
    const char* arg2 = "z";
    const char* arg3 = "u";
    const char* arg4 = "-x";
    const char* arg5 = "-";
    const char* arg6 = "-x=1234567891";
    char* args[] = {const_cast<char*>(arg0), const_cast<char*>(arg1),
                    const_cast<char*>(arg2), const_cast<char*>(arg3),
                    const_cast<char*>(arg4), const_cast<char*>(arg5),
                    const_cast<char*>(arg6)};
    REQUIRE(parser->Parse(7, args) == false);
  }

  SECTION("false if arg is not x") {
    const char* arg0 = "programname";
    const char* arg1 = "-y";
    char* args[] = {const_cast<char*>(arg0), const_cast<char*>(arg1)};
    REQUIRE(parser->Parse(2, args) == false);
  }
}
