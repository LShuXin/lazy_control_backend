#ifndef USER_DB_HPP
#define USER_DB_HPP

#include "dto/UserDto.hpp"
#include "oatpp-sqlite/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient)

class UserDb : public oatpp::orm::DbClient {
public:
    UserDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
        : oatpp::orm::DbClient(executor)
    {

        oatpp::orm::SchemaMigration migration(executor);
        migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/001_init.sql");
        // TODO - Add more migrations here.
        migration.migrate(); // <-- run migrations. This guy will throw on error.

        auto version = executor->getSchemaVersion();
        OATPP_LOGD("UserDb", "Migration - OK. Version=%lld.", version);

    }

    QUERY(createUser,
          "INSERT INTO AppUser"
          " (uid, email, role, username, password, nick, sex, birth, token, token_expire_stamp, status)"
          " VALUES"
          " (:user.uid, :user.email, :user.role, :user.username, :user.password, :user.nick, :user.sex, :user.birth, :user.token, :user.token_expire_stamp, :user.status);",
          PARAM(oatpp::Object<UserDto>, user))

    QUERY(updateUser,
          "UPDATE AppUser"
          " SET"
          " uid=:user.uid,"
          " email=:user.email,"
          " role=:user.role,"
          " username=:user.username,"
          " password=:user.password,"
          " nick=:user.nick,"
          " sex=:user.sex,"
          " birth=:user.birth,"
          " token=:user.token,"
          " token_expire_stamp=:user.token_expire_stamp,"
          " status=:user.status"
          " WHERE"
          " id=:user.id;",
          PARAM(oatpp::Object<UserDto>, user))

    QUERY(getUserById,
          "SELECT * FROM AppUser WHERE id=:id;",
          PARAM(oatpp::Int32, id))

    QUERY(getAllUsers,
          "SELECT * FROM AppUser LIMIT :limit OFFSET :offset;",
          PARAM(oatpp::UInt32, offset),
          PARAM(oatpp::UInt32, limit))
    QUERY(deleteUserById,
          "DELETE FROM AppUser WHERE id=:id;",
          PARAM(oatpp::Int32, id))

};

#include OATPP_CODEGEN_END(DbClient)

#endif
