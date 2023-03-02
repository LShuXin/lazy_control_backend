#include "ConfigService.hpp"
#include "utils/DiffMatchPatch.hpp"
#include "utils/PatchGenerator.cpp"
#include "dto/ConfigDto.hpp"

oatpp::Object<ConfigItemDto> ConfigService::createAppConfigItem(const oatpp::Object<ConfigItemDto>& dto)
{
    // TODO: 毫秒
    unsigned long long seconds = tool_time::now_to_seconds();
    dto->create_stamp = seconds;
    dto->update_stamp = seconds;
    dto->max_config_version = 1;

    auto dbResult = m_database->createAppConfigItem(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    return oatpp::Object<ConfigItemDto>();
}

oatpp::Object<StatusDto> ConfigService::deleteAppConfigItem(const oatpp::Int32 &configId)
{
    return oatpp::Object<StatusDto>();
}

oatpp::Object<ConfigItemPageDto> ConfigService::getAppConfigItems(const oatpp::UInt32 &offset, const oatpp::UInt32 &limit)
{
    oatpp::UInt32 countToFetch = limit;

    if(limit > 10) {
        countToFetch = 10;
    }

    auto dbResult = m_database->getAppConfigItems(offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto dbCntResult = m_database->getAppConfigItemTotalCount();
    OATPP_ASSERT_HTTP(dbCntResult->isSuccess(), Status::CODE_500, dbCntResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<ConfigItemDto>>>();
    // TOTO
    auto total = dbCntResult->fetch<oatpp::Vector<oatpp::Object<ConfigItemDto>>>()->size();

    auto page = ConfigItemPageDto::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;
    page->total = total;

    return page;
}

oatpp::Object<ConfigItemDto> ConfigService::getAppConfigItem(const oatpp::UInt32 &config_id)
{
    auto dbResult = m_database->getAppConfigItemById(config_id);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<ConfigItemDto>>>();

    return items[0];
}



oatpp::Object<ConfigDetailDto> ConfigService::updateAppConfigDetail(const oatpp::Object<ConfigDetailDto> &dto)
{
    unsigned long long updateSeconds = tool_time::now_to_seconds();
    dto->create_stamp = updateSeconds;
    // TODO: query config_version from DateBase rather than use put data
    dto->config_version = dto->config_version + 1;

    auto serializeConfig = oatpp::parser::json::mapping::Serializer::Config::createShared();
    serializeConfig->useBeautifier = true;
    auto deserializeConfig = oatpp::parser::json::mapping::Deserializer::Config::createShared();

    auto jsonObjectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared(serializeConfig, deserializeConfig);
    oatpp::String json = jsonObjectMapper->writeToString(dto);
    OATPP_LOGD("json", "value='%s'", json->c_str()); ///< print json


    auto dbResult = m_database->createAppConfigDetail(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    return dto;
}

oatpp::Object<ConfigDetailPageDto> ConfigService::getAppConfigDetails(const oatpp::UInt32 &offset, const oatpp::UInt32 &limit)
{
    oatpp::UInt32 countToFetch = limit;

    if(limit > 10) {
        countToFetch = 10;
    }

    auto dbResult = m_database->getAppConfigDetails(offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto dbCntResult = m_database->getAppConfigDetailTotalCount();
    OATPP_ASSERT_HTTP(dbCntResult->isSuccess(), Status::CODE_500, dbCntResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<ConfigDetailDto>>>();
    /// TOTO: 优化计数方式
    auto total = dbCntResult->fetch<oatpp::Vector<oatpp::Object<ConfigDetailDto>>>()->size();

    auto page = ConfigDetailPageDto::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;
    page->total = total;

    return page;
}

oatpp::Object<ConfigDetailDto> ConfigService::getAppConfigDetailById(const oatpp::UInt32& id)
{
    auto detailDbResult = m_database->getAppConfigDetailById(id);
    OATPP_ASSERT_HTTP(detailDbResult->isSuccess(), Status::CODE_500, detailDbResult->getErrorMessage());
    auto items = detailDbResult->fetch<oatpp::Vector<oatpp::Object<ConfigDetailDto>>>();
    return items[0];
}

oatpp::Object<ConfigDetailDto> ConfigService::getLatestAppConfigDetail(const oatpp::UInt32& configId)
{
    auto maxVersionRecordDbResult = m_database->getMaxAppConfigItemVersionByConfigId(configId);
    OATPP_ASSERT_HTTP(maxVersionRecordDbResult->isSuccess(), Status::CODE_500, maxVersionRecordDbResult->getErrorMessage());
    auto maxVersionRecord = maxVersionRecordDbResult->fetch<oatpp::Vector<oatpp::Object<ConfigDetailDto>>>();
    auto maxVersion = maxVersionRecord[0]->config_version;

    auto detailDbResult = m_database->getAppConfigDetailByConfigIdAndConfigVersion(configId, maxVersion);
    OATPP_ASSERT_HTTP(detailDbResult->isSuccess(), Status::CODE_500, detailDbResult->getErrorMessage());
    auto items = detailDbResult->fetch<oatpp::Vector<oatpp::Object<ConfigDetailDto>>>();

    return items[0];
}

oatpp::Object<ConfigDetailDto> ConfigService::getLatestAppConfigDetail(const oatpp::String& configName)
{
    auto maxVersionRecordDbResult = m_database->getMaxAppConfigItemVersionByConfigName(configName);
    OATPP_ASSERT_HTTP(maxVersionRecordDbResult->isSuccess(), Status::CODE_500, maxVersionRecordDbResult->getErrorMessage());
    auto maxVersionRecord = maxVersionRecordDbResult->fetch<oatpp::Vector<oatpp::Object<ConfigDetailDto>>>();
    auto maxVersion = maxVersionRecord[0]->config_version;

    auto detailDbResult = m_database->getAppConfigDetailByConfigNameAndConfigVersion(configName, maxVersion);
    OATPP_ASSERT_HTTP(detailDbResult->isSuccess(), Status::CODE_500, detailDbResult->getErrorMessage());
    auto items = detailDbResult->fetch<oatpp::Vector<oatpp::Object<ConfigDetailDto>>>();

    return items[0];
}


oatpp::Object<ConfigDetailDto> ConfigService::getAppConfigDetailByNameVersion(const oatpp::String &configName, const oatpp::UInt32 &version) {
    auto detailDbResult = m_database->getAppConfigDetailByConfigNameAndConfigVersion(configName, version);
    OATPP_ASSERT_HTTP(detailDbResult->isSuccess(), Status::CODE_500, detailDbResult->getErrorMessage());
    auto items = detailDbResult->fetch<oatpp::Vector<oatpp::Object<ConfigDetailDto>>>();

    return items[0];
}


/// 根据传过来的配置版本号以及配置名称生成配置补丁
/// 版本号为1及以下时认为客户端没有配置，直接返回配置内容
oatpp::Object<ConfigPatchOrDetailDto> ConfigService::getAppConfigDetailPatch(const oatpp::String &configName, const oatpp::UInt32 &configVersion, const oatpp::provider::ResourceHandle<oatpp::orm::Connection> &connection) {
    oatpp::Object<ConfigDetailDto> latestConfigDetail = getLatestAppConfigDetail(configName);

    oatpp::Object<ConfigPatchOrDetailDto> configPatchOrDetail = oatpp::Object<ConfigPatchOrDetailDto>::createShared();
    configPatchOrDetail->contentType = 1 >= configVersion ? ConfigPatchOrDetailDtoContentType::CONFIG_DETAIL : ConfigPatchOrDetailDtoContentType::CONFIG_PATCH;
    configPatchOrDetail->config_version = latestConfigDetail->config_version;

    if (configPatchOrDetail->contentType == ConfigPatchOrDetailDtoContentType::CONFIG_DETAIL) {
        configPatchOrDetail->content = latestConfigDetail->content;
        return configPatchOrDetail;
    }


    oatpp::Object<ConfigDetailDto> clientConfigDetail = getAppConfigDetailByNameVersion(configName, configVersion);
    PatchGenerator patchGenerator;

    configPatchOrDetail->content = patchGenerator.generatePatch(clientConfigDetail->content, latestConfigDetail->content);

    return configPatchOrDetail;
}


//oatpp::Object<ConfigDto> ConfigService::getPatch(const oatpp::String &configName, const oatpp::UInt32 &configVersion,
//                                                 const oatpp::provider::ResourceHandle<oatpp::orm::Connection> &connection) {
//    auto dbResult = m_database->getConfigByNameAndVersion(configName, configVersion, connection);
//    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
//    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Config not found");
//
//    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<ConfigDto>>>();
//    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");
//
//    return result[0];
//}
