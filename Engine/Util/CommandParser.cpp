#include "CommandParser.h"

namespace TGE
{
    CommandParserSettings CommandParser::CommandParserSettings = TGE::CommandParserSettings();

    void CommandParser::ParseSingleObject(string command, vector<string>& outCommands,
                                    vector<vector<string>>& outArgs,
                                    string& outObject)
    {
        outCommands.clear();
        outArgs.clear();
        outObject = "";

        size_t cmdPos = 0;
        size_t argPos = 0;
        size_t objPrePos = 0;
        size_t objPostPos = 0;
        int cmdCount = 0;

        while((cmdPos = command.find(CommandParserSettings.sCommandDelimiter)) != string::npos)
        {
            command.erase(0, cmdPos + CommandParserSettings.sCommandDelimiter.length());

            size_t cmdEndPos = command.find(CommandParserSettings.sArgDelimiter);
            if(cmdEndPos == string::npos)
            {
                cmdEndPos = command.find(CommandParserSettings.sCommandDelimiter);

                if(cmdEndPos == string::npos)
                {
                    cmdEndPos = command.find(CommandParserSettings.sObjectPrefix);
                }
            }

            outCommands.push_back(command.substr(0, cmdEndPos));

            size_t nextCmdPos = command.find(CommandParserSettings.sCommandDelimiter);
            string cmdSubstr = command.substr(0, nextCmdPos);

            vector<string> args;
            while((argPos = cmdSubstr.find(CommandParserSettings.sArgDelimiter)) != string::npos)
            {
                cmdSubstr.erase(0, argPos + CommandParserSettings.sArgDelimiter.length());
                
                size_t nextArgPos = cmdSubstr.find(CommandParserSettings.sArgDelimiter);
                if(nextArgPos == string::npos)
                {
                    size_t objPrefixPos = cmdSubstr.find(CommandParserSettings.sObjectPrefix);
                    args.push_back(cmdSubstr.substr(0, objPrefixPos));
                    break;
                }

                else
                {
                    args.push_back(cmdSubstr.substr(0, nextArgPos));
                }
            }

            outArgs.push_back(args);
            cmdCount++;
        }

        if((objPrePos = command.find(CommandParserSettings.sObjectPrefix)) != string::npos)
        {
            objPrePos += CommandParserSettings.sObjectPrefix.length();
            if((objPostPos = command.find(CommandParserSettings.sObjectAffix)) != string::npos)
            {
                outObject = command.substr(objPrePos, objPostPos-objPrePos);
            }
        }

    }

    void CommandParser::Init(TGE::CommandParserSettings settings)
    {
        CommandParserSettings = settings;
    }

    int CommandParser::ParseMultipleObjects(string in,
                                        vector<CommandObject>& out)
    {
        out.clear();

        vector<string> commands;
        vector<vector<string>> args;
        string object;

        size_t objPos = 0;

        while((objPos = in.find(CommandParserSettings.sObjectAffix)) != string::npos)
        {
            string command = in.substr(0, objPos + CommandParserSettings.sObjectAffix.length());
            ParseSingleObject(command, commands, args, object);
            for(auto& arg : args)
            {
                arg.push_back(object);
            }
            
            out.push_back({object, commands, args});
            in.erase(0, objPos + CommandParserSettings.sObjectAffix.length());
        }

        return out.size();
    }

    void CommandParser::FormatObject(string &out, string in,
                                    vector<string> args, string object)
    {
        out = CommandParserSettings.sCommandDelimiter + in + CommandParserSettings.sArgDelimiter;
        for(auto& arg : args)
        {
            out += arg + CommandParserSettings.sArgDelimiter;
        }
        out += CommandParserSettings.sObjectPrefix + object + CommandParserSettings.sObjectAffix;
    }
} // namespace TGE
