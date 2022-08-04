#ifndef CONFIG_DTO_HPP
#define CONFIG_DTO_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class ConfigDto : public oatpp::DTO {

    DTO_INIT(ConfigDto, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD(String, config_name);
    DTO_FIELD(String, content);
    DTO_FIELD(Int32 , config_version);
    DTO_FIELD(Int32 , modify_uid);
    DTO_FIELD(Int32 , update_stamp);
};

#include OATPP_CODEGEN_END(DTO)

#endif