CREATE TABLE devices
    (
    id integer primary key autoincrement,
    name varchar(256) not null,
    icon integer default 0
    );
ALTER TABLE hosts ADD column deviceId integer default null REFERENCES devices(id);
insert into versions values(3,datetime('now'));
