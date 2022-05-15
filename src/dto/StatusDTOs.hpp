#ifndef STATUS_DTO_HPP
#define STATUS_DTO_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */

class StatusDto : public oatpp::DTO {
    DTO_INIT(StatusDto, DTO)

    DTO_FIELD(String, status);

    DTO_FIELD(Int32, code);

    DTO_FIELD_INFO(data) {
        info->description = "响应数据";
    }
    DTO_FIELD(String, data);

    DTO_FIELD_INFO(message) {
        info->description = "额外提示信息";
    }
    DTO_FIELD(String, message);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* STATUS_DTO_HPP */
