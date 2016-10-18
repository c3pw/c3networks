#include "CP852PLCodec.h"

QString CP852PLCodec::fromCP852PL(QByteArray array)
	{
	QString string;
	for(int i=0;i<array.count();i++)
		{
		switch(array.at(i))
			{
			case '\xA5':{string.append(QStringLiteral("ą"));break;}//ą 0xA5
			case '\x86':{string.append(QStringLiteral("ć"));break;}//ć 0x86
			case '\xA9':{string.append(QStringLiteral("ę"));break;}//ę 0xA9
			case '\x88':{string.append(QStringLiteral("ł"));break;}//ł 0x88
			case '\xE4':{string.append(QStringLiteral("ń"));break;}//ń 0xE4
			case '\xA2':{string.append(QStringLiteral("ó"));break;}//ó 0xA2
			case '\x98':{string.append(QStringLiteral("ś"));break;}//ś 0x98
			case '\xBE':{string.append(QStringLiteral("ż"));break;}//ż 0xBE
			case '\xAB':{string.append(QStringLiteral("ź"));break;}//ź 0xAB
			case '\xA4':{string.append(QStringLiteral("Ą"));break;}//Ą 0xA4
			case '\x8F':{string.append(QStringLiteral("Ć"));break;}//Ć 0x8F
			case '\xA8':{string.append(QStringLiteral("Ę"));break;}//Ę 0xA8
			case '\x9D':{string.append(QStringLiteral("Ł"));break;}//Ł 0x9D
			case '\xE3':{string.append(QStringLiteral("Ń"));break;}//Ń 0xE3
			case '\xE0':{string.append(QStringLiteral("Ó"));break;}//Ó 0xE0
			case '\x97':{string.append(QStringLiteral("Ś"));break;}//Ś 0x97
			case '\xBD':{string.append(QStringLiteral("Ż"));break;}//Ż 0xBD
			case '\x8D':{string.append(QStringLiteral("Ź"));break;}//Ź 0x8D
			default:{string.append(array.at(i));break;}
			}
		}
	return string;
	}
