#include "test_rec_data_generator_factory.hpp"
#include "command_parser.hpp"
#include "generator_param.hpp"
#include "trace.hpp"
#include <fstream>

using namespace std;

void PrintHelp()
{
    cout << "Please input parameters as follow:" << endl;
    cout << ">> ./test_data_generator --mode=<work_mode> [--table=<table_name> --nodeid=<nodeid> --realm=<realm> --rectype=<rectype> --begindate=<begin_date> --enddate=<end_date> "
        << "--begintime=<begin_timestamp> --endtime=<end_timestamp> --caller=<caller> --callee=<callee> --encflag=<encryption_flag> "
        << "--emerflag=<emergency_flag> --tag1=<tag1> --tag2=<tag2> --recnum=<recnum> --filepath=<file_path> --outfile=<filepath> --appfile=<filepath>]" << endl << endl;
    cout << "The command paramters are explained as follow:" << endl;
    cout << "<mode>         -   work mode which can be set to" << endl
        << "                    [0 - real_rec, 1 - ue_upload, 2 - ipc_upload, 3 - sds, 4 - dict]" << endl;
    cout << "<table>        -   the dest table which the record addressed in." << endl;
    cout << "<tabstatus>    -   the status of the dest table which the record addressed in." << endl;
    cout << "<nodeid>       -   the node id of the MRS host, which is configured in TBL_MRSNode.NodeId." << endl;
    cout << "<realm>        -   the ream if the MRS host, which is configured in TBL_MRSNode.Realm." << endl;
    cout << "<rectype>      -   the rec type of generated record, which can be set to" << endl
        << "                    [0 - p2p_audio, 1 - ptt_audio, 2 - video_back, 3 - p2p_video, 4 - ptt_video, 5 - camera_rec, 6 - ue_upload, 7 - sds]" << endl
        << "                    it will be set 0 as default value." << endl;
    cout << "<begindate>    -   the date of generated record, which is formed as 2022-1-1 12:12:12 and be treated as the begin time threshold of record." << endl
        << "                    it will be set the first day of this month as default value." << endl;
    cout << "<enddate>      -   the date of generated record, which is formed as 2022-1-1 12:12:12 and be treated as the end time threshold of record." << endl
        << "                    it will be set the second day of this month as default value." << endl;
    cout << "<begintime>    -   the time of generated record, which is formed as timestamp and be treated as the begin time threshold of record, and you need not use <date>." << endl
        << "                    it will be set now as default value." << endl;
    cout << "<endtime>      -   the time of generated record, which is formed as timestamp and be treated as the end time threshold of record, and you need not use <date>." << endl
        << "                    it will be set now as default value." << endl;
    cout << "<caller>       -   the caller user of generated record, it will be set 1001 as default value." << endl;
    cout << "<callee>       -   the callee user of generated record, it will be set 1002 as default value." << endl;
    cout << "<encflag>      -   the encryption flag of generated record, which can be set to" << endl
        << "                    [0 - non-encryption, 1 - encrypted, 2 - decrypted]" << endl
        << "                    it will be set 0 as default value." << endl;
    cout << "<emerflag>     -   the emergency flag of generated record, while can be to" << endl
        << "                    [0 - non-emergency, 1 - emergency]" << endl
        << "                    it will be set 0 as default value." << endl;
    cout << "<tag1>         -   the common tag of generated record, it will be set to 0 as default value." << endl;
    cout << "<tag2>         -   the permanent tag of generated record, which can be set to" << endl
        << "                    [0 - non-permanent, 1 - permanent]" << endl
        << "                    it will be set to 0 as default value." << endl;
    cout << "<recnum>       -   the number of genenered records, it will be set 1 as default value." << endl;
    cout << "<filepath>     -   the file path in genenered records." << endl;
    cout << "<outfile>      -   the output file path which is end with .sql, it will output to console if you set it to console or it is omitted." << endl;
    cout << "<appfile>      -   the append output file path which is end with .sql, it will output to console if you set it to console or it is omitted." << endl;
}

void PrintConsole(std::vector<std::string>& sqlVec)
{
    for (const std::string& sql : sqlVec)
    {
        cout << sql << endl;
    }
}

void PrintFile(const std::string& filepath, std::vector<std::string>& sqlVec, bool append = false)
{
    std::ofstream ofs(filepath, append ? std::ios::app : std::ios::out);
    if (!ofs.is_open())
    {
        throw std::exception();
    }
    for (const std::string& sql : sqlVec)
    {
        ofs << sql << endl;
    }
}

int main(int argc, char** args)
{
    if (argc < 3)
    {
        PrintHelp();
        return 0;
    }
    CommandParser parser;
    GeneratorParam param;
    for (size_t i = 1; i < argc; i++)
    {
        string cmd(args[i]);
        parser.ParseParameter(cmd);
    }
    parser.ParseParameter(param);
    cout << "==================[mode=" << param.mode << "] test data generation is beggining.======================" << endl;
    if (!param.Validate())
    {
        LOG_ERROR("param validate failed")
        return 1;
    }
    
    auto gen = DataGenFactory::CreateGenerator(DataGeneratorType(param.mode));
    if (gen == nullptr)
    {
        LOG_ERROR("invalid mode")
        return 1;
    }
    std::vector<std::string> sqlVec;
    gen->Generate(param, sqlVec);
    if (!param.appfile.empty())
    {
        PrintFile(param.appfile, sqlVec, true);
    }
    else if (!param.outfile.empty())
    {
        PrintFile(param.outfile, sqlVec);
    }
    else
    {
        PrintConsole(sqlVec);
    }
    cout << "==================[mode=" << param.mode << "] test data is generated successfully.====================" << endl << endl;
    return 0;
}