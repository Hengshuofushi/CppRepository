#include "gen_test_data_itf.hpp"
#include "generator_param.hpp"

bool GenTestDataSql(const GeneratorParam& param, std::vector<std::string>& sqlVec)
{
    GeneratorParam innerParam(param);
    if (!innerParam.Validate())
    {
        return false;
    }
    
    auto gen = DataGenFactory::CreateGenerator(DataGeneratorType(innerParam.mode));
    if (gen == nullptr)
    {
        return false;
    }
    
    gen->Generate(param, sqlVec);
    return true;
}