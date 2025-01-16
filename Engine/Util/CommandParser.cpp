#include "CommandParser.h"

namespace TGE
{
    CommandParserSettings CommandParser::CommandParserSettings = TGE::CommandParserSettings();

    void CommandParser::ParseCommand(string command, string& outCommand,
                                    vector<string>& outArgs,
                                    string& outObject)
    {
        outCommand = "";
        outArgs.clear();
        outObject = "";

        size_t pos = 0;

        pos = command.find(CommandParserSettings.sCommandDelimiter);
        if (pos != string::npos)
        {
            command.erase(0, pos + CommandParserSettings.sCommandDelimiter.length());

            pos = command.find(CommandParserSettings.sArgDelimiter);
            if(pos != string::npos)
            {
                outCommand = command.substr(0, pos);
                command.erase(0, pos + CommandParserSettings.sArgDelimiter.length());

                while((pos = command.find(CommandParserSettings.sArgDelimiter)) != string::npos)
                {
                    outArgs.push_back(command.substr(0, pos));
                    command.erase(0, pos + CommandParserSettings.sArgDelimiter.length());
                }

                if(!command.empty())
                {
                    if((pos = command.find(CommandParserSettings.sObjectPrefix)) != string::npos)
                    {
                        outArgs.push_back(command.substr(0, pos));
                        command.erase(0, pos);
                    }
                }
            }

            pos = command.find(CommandParserSettings.sObjectPrefix);
            if(pos != string::npos)
            {
                if(outCommand.empty())
                {
                    outCommand = command.substr(0, pos);
                }

                command.erase(0, pos + CommandParserSettings.sObjectPrefix.length());

                pos = command.find(CommandParserSettings.sObjectAffix);
                if(pos != string::npos)
                {
                    outObject = command.substr(0, pos);
                }
            }
        }
    }

    void CommandParser::Init(TGE::CommandParserSettings settings)
    {
        CommandParserSettings = settings;
    }

    int CommandParser::ParseCommands(string commands,
                                    UITextCommandList& out)
    {
        size_t pos = 0;
        vector<string> commandsSplit;
        while((pos = commands.find(CommandParserSettings.sCommandDelimiter)) != string::npos)
        {
            size_t pos2 = commands.find(CommandParserSettings.sObjectAffix) + CommandParserSettings.sObjectAffix.length();
            commandsSplit.push_back(commands.substr(0, pos2));
            commands.erase(0, pos2);
        }

        for(auto& command : commandsSplit)
        {
            string outCommand;
            vector<string> outArgs;
            string outObject;
            ParseCommand(command, outCommand, outArgs, outObject);
            out.push_back(pair<string, vector<string>>(outCommand, outArgs));
            out.rbegin()->second.push_back(outObject);
        }

        return out.size();
    }

    void CommandParser::FormatCommand(string &out, string command,
                                      vector<string> args, string object)
    {
        out = CommandParserSettings.sCommandDelimiter + command + CommandParserSettings.sArgDelimiter;
        for(auto& arg : args)
        {
            out += arg + CommandParserSettings.sArgDelimiter;
        }
        out += CommandParserSettings.sObjectPrefix + object + CommandParserSettings.sObjectAffix;
    }
} // namespace TGE
