//
// Created by apple on 2022/5/15.
//

#ifndef USER_DTO_HPP
#define USER_DTO_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

ENUM(Role, v_int32,
    VALUE(GUEST, 0, "ROLE_GUEST"),
    VALUE(ADMIN, 1, "ROLE_ADMIN")
)

ENUM(Sex, v_int32,
    VALUE(M, 0, "SEX_MALE"),
    VALUE(F, 1, "SEX_FEMALE")
)

ENUM(UserStatus, v_int32,
     VALUE(CANCELED, 0, "账号注销"),
     VALUE(OK, 1, "正常"),
     VALUE(BAN, 2, "账号被禁止登陆")
)

class UserDto : public oatpp::DTO {

    DTO_INIT(UserDto, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD(String, uid);
    DTO_FIELD(String, email);
    DTO_FIELD(Enum<Role>::AsString, role, "role");
    DTO_FIELD(String, username);
    DTO_FIELD(String, password);
    DTO_FIELD(String, nick);
    DTO_FIELD(Enum<Sex>::AsString, sex);
    DTO_FIELD(Int64, birth);
    DTO_FIELD(String, token);
    DTO_FIELD(Int64, token_expire_stamp);
    DTO_FIELD(Enum<UserStatus>::AsString, status);
};

#include OATPP_CODEGEN_END(DTO)

#endif