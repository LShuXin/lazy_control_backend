#include "ConfigService.hpp"

oatpp::Object<ConfigDto> ConfigService::createConfig(const oatpp::Object<ConfigDto>& dto) {
    auto dbResult = m_database->createConfig(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto ConfigId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

    return getConfigById((v_int32) ConfigId);
}

oatpp::Object<ConfigDto> ConfigService::updateConfig(const oatpp::Object<ConfigDto>& dto) {
    auto dbResult = m_database->updateConfig(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    return getConfigById(dto->id);
}

oatpp::Object<ConfigDto> ConfigService::getConfigById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection) {
    auto dbResult = m_database->getConfigById(id, connection);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Config not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<ConfigDto>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];
}

oatpp::Object<PageDto<oatpp::Object<ConfigDto>>> ConfigService::getAllConfigs(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {
    oatpp::UInt32 countToFetch = limit;

    if(limit > 10) {
        countToFetch = 10;
    }

    auto dbResult = m_database->getAllConfigs(offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<ConfigDto>>>();

    auto page = PageDto<oatpp::Object<ConfigDto>>::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;

    return page;
}

oatpp::Object<StatusDto> ConfigService::deleteConfigById(const oatpp::Int32& ConfigId) {
    auto dbResult = m_database->deleteConfigById(ConfigId);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto status = StatusDto::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Config was successfully deleted";
    return status;
}