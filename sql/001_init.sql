
CREATE TABLE AppUser (
  id INTEGET PRIMARY KEY,
  uid VARCHAR UNIQUE,
  email VARCHAR UNIQUE,
  role CHAR,
  username VARCHAR,
  password VARCHAR,
  nick VARCHAR,
  sex CHAR,
  birth INTEGER,
  token VARCHAR,
  token_expire_time INTEGER,
  status CHAR
);

INSERT INTO AppUser
  (UID, EMAIL, ROLE, USERNAME, PASSWORD, NICK, SEX, BIRTH, TOKEN, TOKEN_EXPIRE_TIME, STATUS)
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
      "",
      "0",
      "1"
  );

