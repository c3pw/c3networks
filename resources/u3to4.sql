CREATE TABLE interfaces
    (
    id integer primary key autoincrement,
    name varchar(256) not null,
    icon blob default null
    );
ALTER TABLE hosts ADD column interfaceId integer default null REFERENCES interfaces(id);
insert into versions values(4,datetime('now'));
