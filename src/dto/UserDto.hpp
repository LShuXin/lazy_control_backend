#ifndef USER_DTO_HPP
#define USER_DTO_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

ENUM(Role, v_int32,
     VALUE(GUEST, 0, "Guest"),
     VALUE(ADMIN, 1, "Admin"))

ENUM(Sex, v_int32,
     VALUE(M, 0, "M"),
     VALUE(F, 1, "F"))

ENUM(UserStatus, v_int32,
     VALUE(CANCELED, 0, "Account Cancelled"),
     VALUE(OK, 1, "Normal"),
     VALUE(BAN, 2, "Can Not Login"))

class UserDto : public oatpp::DTO {

    DTO_INIT(UserDto, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD(String, uid);
    DTO_FIELD(String, email);
    DTO_FIELD(Enum<Role>::AsString, role);
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