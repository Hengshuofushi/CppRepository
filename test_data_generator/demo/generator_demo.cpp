/**
 * @file generator_demo.cpp
 * @author your name (you@domain.com)
 * @brief 使用模拟数据生成器demo,编译：g++ generator_demo.cpp -std=c++11 -g -I.. -L../lib -ltest_data_generator
 * @version 0.1
 * @date 2022-05-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "gen_test_data_itf.hpp"
#include "trace.hpp"

bool GenTestDataSql(const GeneratorParam& param, std::vector<std::string>& sqlVec);
int main()
{
    GeneratorParam param;
    param.mode = 0;
    param.tableName = "TBL_MRSFileInfo";
    param.nodeId = 1;
    param.realm = 12345;
    param.recType = 0;
    param.beginDate = "2022-05-02 16:00:00";
    param.endDate = "2022-05-02 18:00:00";
    param.filePath = "/home/ubp/rec/2022/05/02/16/123.mp4";
    param.recnum = 5;
    std::vector<std::string> sqlVec;
    GenTestDataSql(param, sqlVec);

    for (const std::string& sql : sqlVec)
    {
        LOG_INFO(sql);
    }
    return 0;
}