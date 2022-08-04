#ifndef PAGE_DTO_HPP
#define PAGE_DTO_HPP

#include "UserDto.hpp"
#include "ConfigDto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

template<class T>
class PageDto : public oatpp::DTO {

    DTO_INIT(PageDto, DTO)

    DTO_FIELD(UInt32, offset);
    DTO_FIELD(UInt32, limit);
    DTO_FIELD(UInt32, count);
    DTO_FIELD(Vector<T>, items);

};

class UsersPageDto : public PageDto<oatpp::Object<UserDto>> {
    DTO_INIT(UsersPageDto, PageDto<oatpp::Object<UserDto>>)
};

class ConfigsPageDto : public PageDto<oatpp::Object<ConfigDto>> {
    DTO_INIT(ConfigsPageDto, PageDto<oatpp::Object<ConfigDto>>)
};

#include OATPP_CODEGEN_END(DTO)

#endif
