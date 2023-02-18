#ifndef STATUS_DTO_HPP
#define STATUS_DTO_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class StatusDto : public oatpp::DTO {

    DTO_INIT(StatusDto, DTO)

    DTO_FIELD_INFO(status) {
        info->description = "Sshort status text";
    }
    DTO_FIELD(String, status);


    DTO_FIELD_INFO(code) {
        info->description = "status code";
    }
    DTO_FIELD(Int32, code);


    DTO_FIELD_INFO(message) {
        info->description = "verbose message";
    }
    DTO_FIELD(String, message);

};

#include OATPP_CODEGEN_END(DTO)

#endif
