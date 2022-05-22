
CREATE TABLE AppUser (
  id INTEGER PRIMARY KEY,
  uid VARCHAR UNIQUE,
  email VARCHAR UNIQUE,
  role VARCHAR,
  username VARCHAR,
  password VARCHAR,
  nick VARCHAR,
  sex VARCHAR,
  birth INTEGER,
  token VARCHAR,
  token_expire_stamp INTEGER,
  status VARCHAR
);

INSERT INTO AppUser
  (uid, email, role, username, password, nick, sex, birth, token, token_expire_stamp, status) VALUES (10001, "17853314162@163.com", "1", "lsx", "Ds123@@@@", "Ds", "0", 849369600, "token", 849369600, "1");

