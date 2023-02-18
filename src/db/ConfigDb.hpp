#ifndef CONFIG_DB_HPP
#define CONFIG_DB_HPP

#include "dto/ConfigDto.hpp"
#include "oatpp-sqlite/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient)

class ConfigDb : public oatpp::orm::DbClient {
public:
    ConfigDb(const std::shared_ptr<oatpp::orm::Executor>& executor): oatpp::orm::DbClient(executor)
    {
        oatpp::orm::SchemaMigration migration(executor);


        migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/001_init.sql");
        // TODO - Add more migrations here.
        migration.migrate(); // <-- run migrations. This guy will throw on error.

        auto version = executor->getSchemaVersion();
        OATPP_LOGD("App Config Db", "Migration - OK. Version=%lld.", version);
    }


    /// Table AppConfigItem
    QUERY(createAppConfigItem,
          "INSERT INTO AppConfigItem"
          " (config_name, max_config_version, create_stamp, update_stamp)"
          " VALUES"
          " (:configItem.config_name, :configItem.max_config_version, :configItem.create_stamp, :configItem.update_stamp);",
          PARAM(oatpp::Object<ConfigItemDto>, configItem))

    QUERY(deleteAppConfigItem,
          "DELETE FROM AppConfigItem WHERE id=:id;",
          PARAM(oatpp::UInt32, id))

    QUERY(updateAppConfigItem,
          "UPDATE AppConfigItem"
          " SET"
          " config_name=:configItem.config_name,"
          " max_config_version=:configItem.max_config_version,"
          " create_stamp=:configItem.create_stamp,"
          " update_stamp=:configItem.update_stamp"
          " WHERE"
          " id=:configItem.id;",
          PARAM(oatpp::Object<ConfigItemDto>, configItem))

    QUERY(updateAppConfigItemMaxConfigVersionAndUpdateTime,
          "UPDATE AppConfigItem"
          " SET"
          " max_config_version=:configItem.max_config_version,"
          " update_stamp=:configItem.update_stamp"
          " WHERE"
          " id=:configItem.id;",
          PARAM(oatpp::Object<ConfigItemDto>, configItem))

    QUERY(getAppConfigItems,
          "SELECT * FROM AppConfigItem LIMIT :limit OFFSET :offset;",
          PARAM(oatpp::UInt32, offset),
          PARAM(oatpp::UInt32, limit))

    QUERY(getAppConfigItemById,
          "SELECT * FROM AppConfigItem WHERE id=:config_id;",
          PARAM(oatpp::UInt32, config_id))
    /// TOTO: 优化计数方式
    QUERY(getAppConfigItemTotalCount,
          "SELECT * FROM AppConfigItem;")

    /// 获取指定config_id的ConfigItem的最大版本号
    QUERY(getMaxAppConfigItemVersionByConfigId,
          "SELECT * FROM AppConfigDetail"
          " WHERE config_id=:config_id"
          " ORDER BY config_version DESC"
          " LIMIT 1;",
          PARAM(oatpp::UInt32, config_id))

    /// 获取指定config_name的ConfigItem的最大版本号
    QUERY(getMaxAppConfigItemVersionByConfigName,
          "SELECT * FROM AppConfigDetail"
          " WHERE config_name=:config_name"
          " ORDER BY config_version DESC"
          " LIMIT 1;",
          PARAM(oatpp::String, config_name))




    /// Table AppConfigDetail
    /// 创建ConfigDetail
    /// 注意：修改ConfigDetail时调用的也是本SQL，
    QUERY(createAppConfigDetail,
          "INSERT INTO AppConfigDetail"
          " (config_id, config_name, content, config_version, create_uid, create_stamp)"
          " VALUES"
          " (:configDetail.config_id, :configDetail.config_name, :configDetail.content, :configDetail.config_version, :configDetail.create_uid, :configDetail.create_stamp);",
          PARAM(oatpp::Object<ConfigDetailDto>, configDetail))

    QUERY(getAppConfigDetails,
          "SELECT * FROM AppConfigDetail"
          " LIMIT :limit"
          " OFFSET :offset;",
          PARAM(oatpp::UInt32, offset),
          PARAM(oatpp::UInt32, limit))

    /// TOTO: 优化计数方式
    QUERY(getAppConfigDetailTotalCount,
          "SELECT * FROM AppConfigDetail;")

    /// 通过唯一id获取一条ConfigDetail
    QUERY(getAppConfigDetailById,
          "SELECT * FROM AppConfigDetail"
          " WHERE"
          " id=:id;",
          PARAM(oatpp::UInt32, id))

    /// 通过config_id和config_version获取一条配置详情
    QUERY(getAppConfigDetailByConfigIdAndConfigVersion,
      "SELECT * FROM AppConfigDetail"
      " WHERE"
      " config_id=:config_id"
      " AND"
      " config_version=:config_version;",
      PARAM(oatpp::UInt32, config_id),
      PARAM(oatpp::UInt32, config_version))

    /// 通过config_name和config_version获取一条配置详情
    QUERY(getAppConfigDetailByConfigNameAndConfigVersion,
          "SELECT * FROM AppConfigDetail"
          " WHERE"
          " config_name=:config_name"
          " AND"
          " config_version=:config_version;",
          PARAM(oatpp::String, config_name),
          PARAM(oatpp::UInt32, config_version))
};

#include OATPP_CODEGEN_END(DbClient)

#endif
