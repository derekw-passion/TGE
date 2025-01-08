#pragma once

#include "../defs.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

namespace TGE
{
    struct ENGINE_API CommandParserSettings
    {
        string sCommandPrefix = "/[";
        string sCommandAffix = "]";
        string sArgDelimiter = ":";
    };

    class ENGINE_API CommandParser
    {
    private:
        static CommandParserSettings CommandParserSettings;

    private:
        static void ParseCommand(string command, string& outCommand, vector<string>& outArgs);
    public:
        static void Init(TGE::CommandParserSettings settings);
        static int ParseCommands(string commands, vector<string>& outCommands, map<string, vector<string>>& outArgs);
    };
} // namespace TGE