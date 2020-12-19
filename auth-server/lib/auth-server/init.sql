create table users
(
    id serial NOT NULL PRIMARY KEY,
    user_id bigint NOT NULL UNIQUE,
    username text NOT NULL,
    password text NOT NULL,
    refresh_token text,
    access_token text
);
