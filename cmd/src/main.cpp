#include "../include/OptParser.h"
int main(int argc, char* argv[]) {
  CmdLineOptParser parser;
  return !parser.Parse(argc, argv);
}
