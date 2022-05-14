#ifndef AuthDTOS_hpp
#define AuthDTOS_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */

class LoginResponseDto : public oatpp::DTO {
    DTO_INIT(LoginResponseDto, DTO)

    DTO_FIELD(Int32, statusCode);

    DTO_FIELD_INFO(data) {
        info->description = "用户登陆token";
    }
    DTO_FIELD(String, data);

    DTO_FIELD_INFO(message) {
        info->description = "登陆结果提示语";
    }
    DTO_FIELD(String, message);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* AuthDTOS_hpp */
