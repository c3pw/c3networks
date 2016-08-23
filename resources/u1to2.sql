alter table hosts add column dhcpReservation numeric default 0;
insert into versions values(2,datetime('now'));
