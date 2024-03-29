#ifndef USER_SERVICE_HPP
#define USER_SERVICE_HPP

#include "db/UserDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class UserService {
private:
    typedef oatpp::web::protocol::http::Status Status;

private:
    OATPP_COMPONENT(std::shared_ptr<UserDb>, m_database);

public:
    oatpp::Object<UserDto> createUser(const oatpp::Object<UserDto>& dto);
    oatpp::Object<UserDto> updateUser(const oatpp::Object<UserDto>& dto);
    oatpp::Object<UserDto> getUserById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);
    oatpp::Object<UserPageDto> getAllUser(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
    oatpp::Object<StatusDto> deleteUserById(const oatpp::Int32& id);
};

#endif
