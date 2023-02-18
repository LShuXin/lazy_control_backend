#ifndef CONFIG_CONTROLLER_HPP
#define CONFIG_CONTROLLER_HPP

#include "service/ConfigService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "Filters.hpp"
#include "ConstVariables.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

class ConfigController : public oatpp::web::server::api::ApiController {
public:
    ConfigController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper)
    {}
private:
    ConfigService m_configService; // Create user service.
public:

    static std::shared_ptr<ConfigController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    {
        return std::make_shared<ConfigController>(objectMapper);
    }


    /// Table AppConfig
    ENDPOINT_INFO(createAppConfigItem)
    {
        info->summary = "create new app config item";
        info->addConsumes<Object<ConfigItemDto>>("application/json");
        info->addResponse<Object<ConfigItemDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("POST", "/api/config/item", createAppConfigItem,
             BODY_DTO(Object<ConfigItemDto>, configItemDto))
    {
        return createDtoResponse(Status::CODE_200, m_configService.createAppConfigItem(configItemDto));
    }


    ENDPOINT_INFO(getAppConfigItems) {
        info->summary = "get all stored app config items";
        info->addResponse<oatpp::Object<ConfigItemPageDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ADD_CORS(getAppConfigItems)
    ENDPOINT("GET", "/api/config_item", getAppConfigItems,
             QUERIES(QueryParams, queryParams))
    {
        OATPP_LOGD(INFO_TAG, "1")
        QueryParamsMathRes<NormalFilterDto> queryParamsMathRes = matchQueryParams(queryParams);
        UInt32 offset = queryParamsMathRes.range[0];
        UInt32 limit = queryParamsMathRes.range[1] - queryParamsMathRes.range[0];
        return createDtoResponse(Status::CODE_200, m_configService.getAppConfigItems(offset, limit));
    }


    ENDPOINT_INFO(getAppConfigItem) {
        info->summary = "get app config item by config id";
        info->addResponse<oatpp::Object<ConfigItemDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ADD_CORS(getAppConfigItem)
    ENDPOINT("GET", "/api/config/item/{config_id}", getAppConfigItem,
             PATH(UInt32, config_id))
    {
        OATPP_LOGD(INFO_TAG, "2")
        return createDtoResponse(Status::CODE_200, m_configService.getAppConfigItem(config_id));
    }


    ENDPOINT_INFO(deleteAppConfigItem) {
        info->summary = "delete app config item";
        info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
        info->pathParams["configId"].description = "config item identifier";
    }
    ENDPOINT("DELETE", "/api/config/item/{configId}", deleteAppConfigItem,
             PATH(Int32, configId))
    {
        OATPP_LOGD(INFO_TAG, "3")
        return createDtoResponse(Status::CODE_200, m_configService.deleteAppConfigItem(configId));
    }




    /// Table AppConfigDetail
    ENDPOINT_INFO(updateAppConfigDetail) {
        info->summary = "update app config detail, always create new one";
        info->addConsumes<Object<ConfigDetailDto>>("application/json");
        info->addResponse<Object<ConfigDetailDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
        info->pathParams["id"].description = "Config Identifier";
    }
    ADD_CORS(
            updateAppConfigDetail,
            "*",
            "POST, PUT, GET, DELETE, OPTIONS, UPDATE",
            "DNT, User-Agent, Authorization, X-Requested-With, If-Modified-Since, Cache-Control, Content-Type, Range, Referer, Accept",
            "1728000"
    );
    ENDPOINT("PUT", "/api/config_detail/{id}", updateAppConfigDetail,
             PATH(UInt32, id),
             BODY_DTO(Object<ConfigDetailDto>, configDetailDto))
    {
        OATPP_LOGD(INFO_TAG, "4")
        configDetailDto->id = id;
        return createDtoResponse(Status::CODE_200, m_configService.updateAppConfigDetail(configDetailDto));
    }


    ENDPOINT_INFO(getAppConfigDetails)
    {
        info->summary = "get app config detail List";
        info->addResponse<Object<ConfigDetailPageDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ADD_CORS(getAppConfigDetails)
    ENDPOINT("GET", "/api/config_detail", getAppConfigDetails,
             QUERIES(QueryParams, queryParams))
    {
        OATPP_LOGD(INFO_TAG, "5")
        QueryParamsMathRes<NormalFilterDto> queryParamsMathRes = matchQueryParams(queryParams);
        UInt32 offset = queryParamsMathRes.range[0];
        UInt32 limit = queryParamsMathRes.range[1] - queryParamsMathRes.range[0];
        return createDtoResponse(Status::CODE_200, m_configService.getAppConfigDetails(offset, limit));
    }


    ENDPOINT_INFO(getAppConfigDetailById) {
        info->summary = "get app config detail by id";

        info->addResponse<oatpp::Object<ConfigDetailDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ADD_CORS(
            getAppConfigDetailById,
            "*",
            "POST, PUT, GET, DELETE, OPTIONS, UPDATE",
            "DNT, User-Agent, Authorization, X-Requested-With, If-Modified-Since, Cache-Control, Content-Type, Range, Referer, Accept",
            "1728000"
    );
    ENDPOINT("GET", "/api/config_detail/{id}", getAppConfigDetailById,
             PATH(UInt32, id))
    {
        OATPP_LOGD(INFO_TAG, "6")
        return createDtoResponse(Status::CODE_200, m_configService.getAppConfigDetailById(id));
    }


    ENDPOINT_INFO(getLatestAppConfigDetailByConfigId) {
        info->summary = "get app config detail by config_id";
        info->addResponse<oatpp::Object<ConfigDetailDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ADD_CORS(
            getLatestAppConfigDetailByConfigId,
            "*",
            "POST, PUT, GET, DELETE, OPTIONS, UPDATE",
            "DNT, User-Agent, Authorization, X-Requested-With, If-Modified-Since, Cache-Control, Content-Type, Range, Referer, Accept",
            "1728000"
    );
    ENDPOINT("GET", "/api/latest_config_detail/config_id/{config_id}", getLatestAppConfigDetailByConfigId,
             PATH(UInt32, config_id))
    {
        OATPP_LOGD(INFO_TAG, "7")
        return createDtoResponse(Status::CODE_200, m_configService.getLatestAppConfigDetail(config_id));
    }


    ENDPOINT_INFO(getLatestAppConfigDetailByConfigName) {
        info->summary = "get app config detail by config_name";
        info->addResponse<oatpp::Object<ConfigDetailDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ADD_CORS(
            getLatestAppConfigDetailByConfigName,
            "*",
            "POST, PUT, GET, DELETE, OPTIONS, UPDATE",
            "DNT, User-Agent, Authorization, X-Requested-With, If-Modified-Since, Cache-Control, Content-Type, Range, Referer, Accept",
            "1728000"
    );
    ENDPOINT("GET", "/api/latest_config_detail/config_name/{config_name}", getLatestAppConfigDetailByConfigName,
             PATH(String, config_name))
    {
        OATPP_LOGD(INFO_TAG, "8")
        return createDtoResponse(Status::CODE_200, m_configService.getLatestAppConfigDetail(config_name));
    }


    ENDPOINT_INFO(getAppConfigDetailPatch) {
        info->summary = "Get config patch by local config version";
        info->addResponse<Object<ConfigDetailDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
        info->pathParams["app"].description = "App name or Config name";
        info->pathParams["version"].description = "Local config version";
    }
    ENDPOINT("GET", "/api/config/patch/app/{app}/version/{version}", getAppConfigDetailPatch,
             PATH(String, app),
             PATH(UInt32, version))
    {
        OATPP_LOGD(INFO_TAG, "9")
        return createDtoResponse(Status::CODE_200, m_configService.getAppConfigDetailPatch(app, version));
    }
};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif /* ConfigController_hpp */
