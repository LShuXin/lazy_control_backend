#ifndef CONFIG_DTO_HPP
#define CONFIG_DTO_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class ConfigItemDto : public oatpp::DTO {
    DTO_INIT(ConfigItemDto, DTO)

    DTO_FIELD_INFO(id) {
        info->description = "config id";
    }
    DTO_FIELD(UInt32, id);


    DTO_FIELD_INFO(config_name) {
        info->description = "config name";
    }
    DTO_FIELD(String, config_name);


    DTO_FIELD_INFO(max_config_version) {
        info->description = "max config version, latest config version";
    }
    DTO_FIELD(UInt32, max_config_version);


    DTO_FIELD_INFO(create_stamp) {
        info->description = "createTime";
    }
    DTO_FIELD(UInt32, create_stamp);


    DTO_FIELD_INFO(update_stamp) {
        info->description = "update time";
    }
    DTO_FIELD(UInt32, update_stamp);
};

class ConfigDetailDto : public oatpp::DTO {

    DTO_INIT(ConfigDetailDto, DTO)

    DTO_FIELD_INFO(id) {
        info->description = "config unique identifier";
    }
    DTO_FIELD(UInt32, id);


    DTO_FIELD_INFO(config_id) {
        info->description = "config item id";
    }
    DTO_FIELD(UInt32, config_id);


    DTO_FIELD_INFO(config_name) {
        info->description = "used to distinguish different configurations";
    }
    DTO_FIELD(String, config_name);


    DTO_FIELD_INFO(content) {
        info->description = "complete configuration content";
    }
    DTO_FIELD(String, content);


    DTO_FIELD_INFO(config_version) {
        info->description = "config version";
    }
    DTO_FIELD(UInt32 , config_version);


    DTO_FIELD_INFO(create_uid) {
        info->description = "config version";
    }
    DTO_FIELD(UInt32 , create_uid);


    DTO_FIELD_INFO(create_stamp) {
        info->description = "update/create time";
    }
    DTO_FIELD(UInt64 , create_stamp);
};

#include OATPP_CODEGEN_END(DTO)

#endif