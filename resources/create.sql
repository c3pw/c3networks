CREATE TABLE groups
    (
    id integer primary key autoincrement,
    name varchar(256) not null,
    color varchar(7) not null default '#000000'
    );

CREATE TABLE devices
    (
    id integer primary key autoincrement,
    name varchar(256) not null,
    icon integer default 0
    );

CREATE TABLE interfaces
    (
    id integer primary key autoincrement,
    name varchar(256) not null,
    icon blob default null
    );

CREATE TABLE hosts
    (
    id integer primary key autoincrement,
    ipAddress int,
    mask int,
    name varchar(1024) default '',
    mac varchar(16) default '',
    userName varchar(1024) default '',
    domain varchar(1024) default '',
    description text default '',
    inUse int default 0,
    groupId integer default null,
    location description text default '',
    dhcpReservation numeric default 0,
    deviceId integer default null,
    interfaceId integer default null,
    FOREIGN KEY(groupId) REFERENCES groups(id),
    FOREIGN KEY(deviceId) REFERENCES devices(id),
    FOREIGN KEY(interfaceId) REFERENCES interfaces(id)
    );
CREATE TABLE versions
    (
    version int  primary key not null,
    time datetime not null
    );

insert into versions values(4,datetime('now'));
