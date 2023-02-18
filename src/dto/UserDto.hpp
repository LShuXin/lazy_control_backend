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


    DTO_FIELD_INFO(id) {
        info->description = "db user unique identifier";
    }
    DTO_FIELD(Int32, id);


    DTO_FIELD_INFO(uid) {
        info->description = "user uniquer identifier";
    }
    DTO_FIELD(String, uid);


    DTO_FIELD_INFO(email) {
        info->description = "user email";
    }
    DTO_FIELD(String, email);

    DTO_FIELD_INFO(role) {
        info->description = "user role";
    }
    DTO_FIELD(Enum<Role>::AsString, role);


    DTO_FIELD_INFO(username) {
        info->description = "username";
    }
    DTO_FIELD(String, username);


    DTO_FIELD_INFO(password) {
      info->description = "user password in md5";
    }
    DTO_FIELD(String, password);

    DTO_FIELD_INFO(nick) {
        info->description = "user nick";
    }
    DTO_FIELD(String, nick);

    DTO_FIELD_INFO(sex) {
        info->description = "user sex";
    }


    DTO_FIELD(Enum<Sex>::AsString, sex);


    DTO_FIELD_INFO(birth) {
        info->description = "user birth";
    }
    DTO_FIELD(Int64, birth);

    DTO_FIELD_INFO(token) {
        info->description = "user token";
    }
    DTO_FIELD(String, token);

    DTO_FIELD_INFO(token_expire_stamp) {
        info->description = "token expire time";
    }
    DTO_FIELD(Int64, token_expire_stamp);

    DTO_FIELD_INFO(status) {
        info->description = "user status";
    }
    DTO_FIELD(Enum<UserStatus>::AsString, status);
};

#include OATPP_CODEGEN_END(DTO)

#endif