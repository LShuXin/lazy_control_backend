#ifndef CONFIG_SERVICE_HPP
#define CONFIG_SERVICE_HPP

#include "db/ConfigDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class ConfigService {
private:
    typedef oatpp::web::protocol::http::Status Status;

private:
    OATPP_COMPONENT(std::shared_ptr<ConfigDb>, m_database);

public:
    oatpp::Object<ConfigDto> createConfig(const oatpp::Object<ConfigDto>& dto);
    oatpp::Object<ConfigDto> updateConfig(const oatpp::Object<ConfigDto>& dto);
    oatpp::Object<ConfigDto> getConfigById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);
    oatpp::Object<PageDto<oatpp::Object<ConfigDto>>> getAllConfigs(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
    oatpp::Object<StatusDto> deleteConfigById(const oatpp::Int32& id);
};

#endif
