//
// Created by apple on 2022/5/15.
//

#ifndef USER_CONTROLLER_HPP
#define USER_CONTROLLER_HPP

#include "dto/auth/UserDTOs.hpp"
#include "service/user/UserService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

/**
 * 对用户的操作
 * */

class UserController : public oatpp::web::server::api::ApiController {
private:
    UserService m_userService;
public:
    UserController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}
public:
    static std::shared_ptr<UserController> createShared(
      OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    ) {
        return std::make_shared<UserController>(objectMapper);
    }

    ENDPOINT_INFO(createUser) {
        info->summary = "Create a User";
        info->addConsumes<Object<UserDto>>("application/json");
        info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("POST", "createuser", createUser,
             BODY_DTO(Object<UserDto>, userDto))
    {
        return createDtoResponse(Status::CODE_200, m_userService.createUser(userDto));
    }

    ENDPOINT_INFO(updateUser) {
        info->summary = "Update User by userId";

        info->addConsumes<Object<UserDto>>("application/json");

        info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["userId"].description = "User Identifier";
    }
    ENDPOINT("PUT", "users/{userId}", updateUser,
             PATH(Int32, userId),
             BODY_DTO(Object<UserDto>, userDto))
    {
        userDto->id = userId;
        return createDtoResponse(Status::CODE_200, m_userService.updateUser(userDto));
    }

    ENDPOINT_INFO(getUserById) {
        info->summary = "Get one User by userId";

        info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["userId"].description = "User Identifier";
    }
    ENDPOINT("GET", "users/{userId}", getUserById,
             PATH(Int32, userId))
    {
        return createDtoResponse(Status::CODE_200, m_userService.getUserById(userId));
    }

    ENDPOINT_INFO(getUsers) {
        info->summary = "Get Users by offset and limit params";

        info->addResponse<oatpp::Object<UsersPageDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("GET", "users/offset/{offset}/limit/{limit}", getUsers,
             PATH(UInt32, offset),
             PATH(UInt32, limit))
    {
        return createDtoResponse(Status::CODE_200, m_userService.getUsers(offset, limit));
    }

    ENDPOINT_INFO(deleteUser) {
        info-> summary = "Delete User by userId";

        info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["userId"].description = "User Identifier";
    }
    ENDPOINT("DELETE", "users/{userId}", deleteUser,
             PATH(Int32, userId))
    {
        return createDtoResponse(Status::CODE_200, m_userService.deleteUserById(userId));
    }
};

#include OATPP_CODEGEN_END(ApiController)

#endif //USERCONTROLLER_HPP
