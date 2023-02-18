#ifndef QUERY_PARAMS_HPP
#define QUERY_PARAMS_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class NormalFilterDto : public oatpp::DTO {
    DTO_INIT(NormalFilterDto, DTO)

    DTO_FIELD_INFO(post_id) {
        info->description = "record id for filter";
    }
    DTO_FIELD(UInt32 , post_id);
};

#include OATPP_CODEGEN_END(DTO)

#endif
