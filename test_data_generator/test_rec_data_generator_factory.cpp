#include "test_rec_data_generator_factory.hpp"
#include <iostream>

P_TestRecDataGenerator_T DataGenFactory::CreateGenerator(DataGeneratorType type)
{
    P_TestRecDataGenerator_T gen;
    switch (type)
    {
        case DataGeneratorType::DATA_GENERATOR_REAL_REC:
            gen = std::make_shared<MrsFileInfoDataGenerator>();
            break;
        case DataGeneratorType::DATA_GENERATOR_UE_UPLOAD:
            gen = std::make_shared<UeUploadDataGenerator>();
            break;
        case DataGeneratorType::DATA_GENERATOR_IPC_UPLOAD:
            gen = std::make_shared<IpcUploadDataGenerator>();
            break;
        case DataGeneratorType::DATA_GENERATOR_SDS:
            gen = std::make_shared<SdsDataGenerator>();
            break;
        case DataGeneratorType::DATA_GENERATOR_DICT:
            gen = std::make_shared<MrsDictInfoDataGenerator>();
            break;
        default:
            std::cout << "invalid generator type: " << (int)type << std::endl;
            break;
    }
    return gen;
}