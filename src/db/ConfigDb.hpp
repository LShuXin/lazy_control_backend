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
        OATPP_LOGD("ConfigDb", "Migration - OK. Version=%lld.", version);
    }

    QUERY(createConfig,
          "INSERT INTO AppConfig"
          " (name, app, content, version)"
          " VALUES"
          " (:config.name, :config.app, :config.content, :config.version);",
          PARAM(oatpp::Object<ConfigDto>, config))

    QUERY(updateConfig,
          "UPDATE AppUser"
          " SET"
          " name=:config.name,"
          " app=:config.app,"
          " content=:config.content,"
          " version=:config.version"
          " WHERE"
          " id=:config.id;",
          PARAM(oatpp::Object<ConfigDto>, config))

    QUERY(getConfigById,
          "SELECT * FROM AppConfig WHERE id=:id;",
          PARAM(oatpp::Int32, id))

    QUERY(getAllConfigs,
          "SELECT * FROM AppConfig LIMIT :limit OFFSET :offset;",
          PARAM(oatpp::UInt32, offset),
          PARAM(oatpp::UInt32, limit))

    QUERY(deleteConfigById,
          "DELETE FROM AppConfig WHERE id=:id;",
          PARAM(oatpp::Int32, id))

};

#include OATPP_CODEGEN_END(DbClient)

#endif
