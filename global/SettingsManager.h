#ifndef QSETTINGSMANAGER_H
#define QSETTINGSMANAGER_H

#include <QObject>
#include <QSettings>

class SettingsManager : public QSettings
    {
    Q_OBJECT
    public:
        SettingsManager();
    };

#endif // QSETTINGSMANAGER_H
