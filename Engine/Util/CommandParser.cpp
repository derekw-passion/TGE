#include "CommandParser.h"

namespace TGE
{
    CommandParserSettings CommandParser::CommandParserSettings = TGE::CommandParserSettings();

    void CommandParser::ParseCommand(string command, string& outCommand,
                                    vector<string>& outArgs)
    {

    }

    void CommandParser::Init(TGE::CommandParserSettings settings)
    {
        CommandParserSettings = settings;
    }

    int CommandParser::ParseCommands(string commands,
                                    vector<string>& outCommands,
                                    map<string, vector<string>> &outArgs)
    {
        return 0; // # of commands parsed
    }
} // namespace TGE
