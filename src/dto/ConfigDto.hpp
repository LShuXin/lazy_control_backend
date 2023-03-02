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


ENUM(ConfigPatchOrDetailDtoContentType, v_int32,
     VALUE(CONFIG_PATCH, 0, "content直接就是配置内容，直接取出内容当作配置即可"),
     VALUE(CONFIG_DETAIL, 1, "content是补丁，需要对客户端的部分进行打补丁从而生成完整的配置"))

/// 配置或者配置补丁
class ConfigPatchOrDetailDto : public oatpp::DTO {

    DTO_INIT(ConfigPatchOrDetailDto, DTO)

    DTO_FIELD_INFO(contentType) {
        info->description = "content类型标识，如果是0就代表配置内容，1代表配置补丁";
    }
    DTO_FIELD(Enum<ConfigPatchOrDetailDtoContentType>::AsNumber, contentType);


    DTO_FIELD_INFO(content) {
        info->description = "补丁内容或者配置内容";
    }
    DTO_FIELD(String, content);


    DTO_FIELD_INFO(config_version) {
        info->description = "对应最新配置的版本";
    }
    DTO_FIELD(UInt32 , config_version);
};



#include OATPP_CODEGEN_END(DTO)

#endif