ALTER TABLE hosts ADD column switchPort varchar(256) default null;
insert into versions values(5,datetime('now'));
