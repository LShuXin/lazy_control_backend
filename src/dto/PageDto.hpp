#ifndef PAGE_DTO_HPP
#define PAGE_DTO_HPP

#include "UserDto.hpp"
#include "ConfigDto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

template<class T>
class PageDto : public oatpp::DTO {

    DTO_INIT(PageDto, DTO)

    DTO_FIELD_INFO(offset) {
        info->description = "offset";
    }
    DTO_FIELD(UInt32, offset);


    DTO_FIELD_INFO(limit) {
        info->description = "limit";
    }
    DTO_FIELD(UInt32, limit);


    DTO_FIELD_INFO(count) {
        info->description = "data count";
    }
    DTO_FIELD(UInt32, count);

    DTO_FIELD_INFO(total) {
        info->description = "total records count in db";
    }
    DTO_FIELD(UInt32, total);

    DTO_FIELD_INFO(items) {
        info->description = "data Array returns";
    }
    DTO_FIELD(Vector<T>, items);

};

class UserPageDto : public PageDto<oatpp::Object<UserDto>> {
    DTO_INIT(UserPageDto, PageDto<oatpp::Object<UserDto>>)
};

class ConfigItemPageDto : public PageDto<oatpp::Object<ConfigItemDto>> {
    DTO_INIT(ConfigItemPageDto, PageDto<oatpp::Object<ConfigItemDto>>)
};

class ConfigDetailPageDto : public PageDto<oatpp::Object<ConfigDetailDto>> {
    DTO_INIT(ConfigDetailPageDto, PageDto<oatpp::Object<ConfigDetailDto>>)
};

#include OATPP_CODEGEN_END(DTO)

#endif
