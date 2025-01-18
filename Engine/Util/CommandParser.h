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
        string sCommandDelimiter = "/";
        string sArgDelimiter = ":";
        string sObjectPrefix = "[";
        string sObjectAffix = "]";
    };

    typedef vector<std::pair<vector<string>, vector<vector<string>>>> CommandObjectList;

    class ENGINE_API CommandParser
    {
    private:
        static CommandParserSettings CommandParserSettings;

    private:
        static void ParseSingleObject(string command, vector<string>& outCommands, vector<vector<string>>& outArgs, string& outObject);
    public:
        static void Init(TGE::CommandParserSettings settings);
        static int ParseMultipleObjects(string in, CommandObjectList& out);
        static void FormatObject(string& out, string command, vector<string> args, string object);
    };
} // namespace TGE