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

    typedef vector<std::pair<string, vector<string>>> UITextCommandList;

    class ENGINE_API CommandParser
    {
    private:
        static CommandParserSettings CommandParserSettings;

    private:
        // ie: "/c:0:255:0:255[this text is green]"
        static void ParseCommand(string command, string& outCommand, vector<string>& outArgs, string& outObject);
    public:
        static void Init(TGE::CommandParserSettings settings);

        // ie: "/c:0:255:0:255[this text is green] /c:255:0:0:255[this text is red]"
        static int ParseCommands(string commands, UITextCommandList& out);
        static void FormatCommand(string& out, string command, vector<string> args, string object);
    };
} // namespace TGE