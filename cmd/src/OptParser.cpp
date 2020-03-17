#include "../include/OptParser.h"
bool CmdLineOptParser::Parse ( int argc , char * argv [])
{
    bool val = true;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            return false;
        } else {
            if (argv[i][2] == '\0') {
                if (argc > i + 1) {
                    if (argv[i + 1][0] == '-') {
                        val &= Option(argv[i][1], nullptr);
                    } else {
                        val &= Option(argv[i][1], argv[i + 1]);
                        i++;
                    }
                } else {
                    val &= Option(argv[i][1], nullptr);
                }
            } else {
                if (argv[i][2] == '=')
                {
                    val &= Option(argv[i][1], &argv[i][3]);
                } else {
                    val &= Option(argv[i][1], &argv[i][2]);
                }
            }
        }

    }
    return val;
}
bool CmdLineOptParser::Option ( const char c, const char * info)
{
    if (c == 'x') {
        if (info == nullptr) {
            return true;
        }
        int i;
        for (i = 0; info[i]; i++); 
        if (i > 10) {

            return false;

        }

        return true;
    } else {
        return false;
    }
}

