#ifndef USER_CONTROLLER_HPP
#define USER_CONTROLLER_HPP

#include "service/UserService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * User REST controller.
 */
class UserController : public oatpp::web::server::api::ApiController {
public:
    UserController(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    ) : oatpp::web::server::api::ApiController(objectMapper) {}
private:
    UserService m_userService;
public:
    static std::shared_ptr<UserController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
    ) {
        return std::make_shared<UserController>(objectMapper);
    }

    ENDPOINT_INFO(createUser) {
        info->summary = "Create new User";

        info->addConsumes<Object<UserDto>>("application/json");

        info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("POST", "/api/user", createUser,
             BODY_DTO(Object<UserDto>, userDto))
    {
        return createDtoResponse(Status::CODE_200, m_userService.createUser(userDto));
    }

    ENDPOINT_INFO(putUser) {
        info->summary = "Update User by userId";

        info->addConsumes<Object<UserDto>>("application/json");

        info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["userId"].description = "User Identifier";
    }
    ENDPOINT("PUT", "/api/user/{userId}", putUser,
             PATH(Int32, userId),
             BODY_DTO(Object<UserDto>, userDto))
    {
        userDto->id = userId;
        return createDtoResponse(Status::CODE_200, m_userService.updateUser(userDto));
    }


    ENDPOINT_INFO(getUserById) {
        info->summary = "Get one User by userId";

        info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["userId"].description = "User Identifier";
    }
    ENDPOINT("GET", "/api/user/{userId}", getUserById,
             PATH(Int32, userId))
    {
        return createDtoResponse(Status::CODE_200, m_userService.getUserById(userId));
    }


    ENDPOINT_INFO(getUsers) {
        info->summary = "get all stored users";

        info->addResponse<oatpp::Object<UserPageDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("GET", "/api/user/offset/{offset}/limit/{limit}", getUsers,
             PATH(UInt32, offset),
             PATH(UInt32, limit))
    {
        return createDtoResponse(Status::CODE_200, m_userService.getAllUser(offset, limit));
    }


    ENDPOINT_INFO(deleteUser) {
        info->summary = "Delete User by userId";

        info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["userId"].description = "User Identifier";
    }
    ENDPOINT("DELETE", "/api/user/{userId}", deleteUser,
             PATH(Int32, userId))
    {
        return createDtoResponse(Status::CODE_200, m_userService.deleteUserById(userId));
    }

};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif /* UserController_hpp */
