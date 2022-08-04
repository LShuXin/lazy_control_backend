#ifndef CONFIG_CONTROLLER_HPP
#define CONFIG_CONTROLLER_HPP

#include "service/ConfigService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

class ConfigController : public oatpp::web::server::api::ApiController {
public:
    ConfigController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper)
    {}
private:
    ConfigService m_configService; // Create user service.
public:

    static std::shared_ptr<ConfigController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
    ){
        return std::make_shared<ConfigController>(objectMapper);
    }

    ENDPOINT_INFO(createConfig) {
        info->summary = "Create new Config";

        info->addConsumes<Object<ConfigDto>>("application/json");

        info->addResponse<Object<ConfigDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("POST", "configs", createConfig,
             BODY_DTO(Object<ConfigDto>, configDto))
    {
        return createDtoResponse(Status::CODE_200, m_configService.createConfig(configDto));
    }

    ENDPOINT_INFO(putConfig) {
        info->summary = "Update Config by configId";

        info->addConsumes<Object<ConfigDto>>("application/json");

        info->addResponse<Object<ConfigDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["configId"].description = "Config Identifier";
    }
    ENDPOINT("PUT", "configs/{configId}", putConfig,
             PATH(Int32, configId),
             BODY_DTO(Object<ConfigDto>, configDto))
    {
        configDto->id = configId;
        return createDtoResponse(Status::CODE_200, m_configService.updateConfig(configDto));
    }


    ENDPOINT_INFO(getConfigById) {
        info->summary = "Get one Config by Id";

        info->addResponse<Object<ConfigDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["configId"].description = "Config Identifier";
    }
    ENDPOINT("GET", "configs/{configId}", getConfigById,
             PATH(Int32, configId))
    {
        return createDtoResponse(Status::CODE_200, m_configService.getConfigById(configId));
    }


    ENDPOINT_INFO(getConfigs) {
        info->summary = "get all stored configs";

        info->addResponse<oatpp::Object<ConfigsPageDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("GET", "configs/offset/{offset}/limit/{limit}", getConfigs,
             PATH(UInt32, offset),
             PATH(UInt32, limit))
    {
        return createDtoResponse(Status::CODE_200, m_configService.getAllConfigs(offset, limit));
    }


    ENDPOINT_INFO(deleteConfig) {
        info->summary = "Delete Config by Id";

        info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["configId"].description = "Config Identifier";
    }
    ENDPOINT("DELETE", "configs/{configId}", deleteConfig,
             PATH(Int32, configId))
    {
        return createDtoResponse(Status::CODE_200, m_configService.deleteConfigById(configId));
    }

};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif /* ConfigController_hpp */
