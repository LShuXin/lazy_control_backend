#ifndef CONFIG_SERVICE_HPP
#define CONFIG_SERVICE_HPP

#include "utils/TimeUtils.hpp"
#include "db/ConfigDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class ConfigService {
private:
    typedef oatpp::web::protocol::http::Status Status;

private:
    OATPP_COMPONENT(std::shared_ptr<ConfigDb>, m_database);

public:
    /// Table AppConfigItem
    /**
     * 创建一个新的配置项目，config_name 必须与已有的配置不同
     * 通常来来说，同一个应用，手机端一个配置文件，桌面端一个配置文件，小程序一个配置文件
     * */
    oatpp::Object<ConfigItemDto> createAppConfigItem(const oatpp::Object<ConfigItemDto>& dto);

    /**
     * 获取配置列表，常用
     **/
    oatpp::Object<ConfigItemPageDto> getAppConfigItems(const oatpp::UInt32& offset, const oatpp::UInt32& limit);

    /**
     * 根据config_Id获取配置列表，常用
     **/
    oatpp::Object<ConfigItemDto> getAppConfigItem(const oatpp::UInt32& configId);

    /**
     * 删除配置项
     * */
    oatpp::Object<StatusDto> deleteAppConfigItem(const oatpp::Int32& configId);




    /// Table AppConfigDetail
    /**
     * 获取ConfigItem的ConfigDetail列表
     * */
    oatpp::Object<ConfigDetailPageDto> getAppConfigDetails(const oatpp::UInt32& offset, const oatpp::UInt32& limit);

    /**
     * 通过id唯一获取一条ConfigDetail
     * */
    oatpp::Object<ConfigDetailDto> getAppConfigDetailById(const oatpp::UInt32& id);

    /**
     * 直接通过config_id获取最新的ConfigDetail(用于非增量更新配置文件)
     * */
    oatpp::Object<ConfigDetailDto> getLatestAppConfigDetail(const oatpp::UInt32& configId);

    /**
     * 直接通过config_name获取最新的ConfigDetail(用于非增量更新配置文件)
     * */
    oatpp::Object<ConfigDetailDto> getLatestAppConfigDetail(const oatpp::String& configName);

    /**
     * 修改配置文件
     * 这里修改配置文件必须是创建一条新的配置文件，并且让版本号加1
     * */
    oatpp::Object<ConfigDetailDto> updateAppConfigDetail(const oatpp::Object<ConfigDetailDto>& dto);

    /**
     * 根据配置名和版本号获取配置
     * */
    oatpp::Object<ConfigDetailDto> getAppConfigDetailByNameVersion(const oatpp::String& configName, const oatpp::UInt32& version);

    /**
     * 根据配置名和配置版本号获取配置补丁，常用
     *
     * 具体过程是：
     *   1. 如果配置名不存在则抛出错误
     *   2. 如果版本号为0，则直接返回整个配置文件
     *   3. 如果版本号大于0，则使用diff_match_patch算法计算数据库内该配置的最新版本和传入的版本之间的diff，将diff作为patch字段传入
     *   4. 前端通过diff计算新的配置或者直接存储完整配置
     * */
    oatpp::Object<ConfigPatchOrDetailDto> getAppConfigDetailPatch(const oatpp::String &configName, const oatpp::UInt32& configVersion, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);


};

#endif
