CREATE TABLE AppUser (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    uid VARCHAR UNIQUE,
    email VARCHAR UNIQUE,
    role VARCHAR,
    username VARCHAR,
    password VARCHAR,
    nick VARCHAR,
    sex VARCHAR,
    birth INTEGER,
    token VARCHAR,
    token_expire_stamp BIGINT,
    status VARCHAR
);


CREATE TABLE AppConfigItem (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    config_name VARCHAR UNIQUE,
    max_config_version INTEGER,
    create_stamp BIGINT,
    update_stamp BIGINT
);


CREATE TABLE AppConfigDetail (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    config_id INTEGER,
    config_name VARCHAR,
    content VARCHAR,
    config_version INTEGER,
    create_uid INTEGER,
    create_stamp BIGINT
--     FOREIGN KEY(config_id) REFERENCES AppConfigItem(id)
);


INSERT INTO AppUser (
    uid,
    email,
    role,
    username,
    password,
    nick,
    sex,
    birth,
    token,
    token_expire_stamp,
    status
)
VALUES
(
    10001,
    "17853314162@163.com",
    "1",
    "lsx",
    "Ds123@@@@",
    "Ds",
    "0",
    849369600,
    "token",
    849369600,
    "1"
);


INSERT INTO AppConfigItem (
    config_name,
    max_config_version,
    create_stamp,
    update_stamp
)
VALUES
(
  "lazy_control",
  0,
  0,
  0
);


INSERT INTO AppConfigDetail (
    config_id,
    config_name,
    content,
    config_version,
    create_uid,
    create_stamp
)
VALUES
(
    0,
    "lazy_control",
    "{}",
    0,
    0,
    0
);
