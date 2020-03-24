#include "../include/OptParser.h"
bool CmdLineOptParser::Parse(int argc, char *argv[])
{
  bool val = true;
  int counter;
  if (argc == 0)
    return false;
  for (counter = 0; argv[counter] != nullptr; counter++);
  if(argc != counter)
    return false;
  


  for (int i = 1; i < argc; i++)
  {
    if (argv[i][0] != '-')
    {
      return false;
    }
    else
    {
      if (argv[i][2] == '\0')
      {
        if (argc > i + 1)
        {
          if (argv[i + 1][0] == '-')
          {
            val &= Option(argv[i][1], nullptr);
          }
          else
          {
            val &= Option(argv[i][1], argv[i + 1]);
            i++;
          }
        }
        else
        {
          val &= Option(argv[i][1], nullptr);
        }
      }
      else
      {
        if (argv[i][2] == '=')
        {
          val &= Option(argv[i][1], &argv[i][3]);
        }
        else
        {
          val &= Option(argv[i][1], &argv[i][2]);
        }
      }
    }
  }
  return val;
}
bool CmdLineOptParser::Option(const char c, const char *info)
{
  return (c == '\0' || info == nullptr);
}
