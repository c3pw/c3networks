#-------------------------------------------------
#
# Project created by QtCreator 2015-12-17T19:19:49
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = c3Networks
TEMPLATE = app

VERSION = 0.0.1.3

SOURCES += main.cpp \
    database/IfDbTable.cpp \
    database/InterfaceItem.cpp \
    database/NetworkItem.cpp \
    models/IfTabeModel.cpp \
    models/IfTableSortProxy.cpp \
    gui/MainWindow.cpp \
    gui/AboutWindow.cpp \
    gui/SelectDbWindow.cpp \
    database/DbFileItem.cpp \
    global/SettingsManager.cpp \
    gui/helpers/HtmlHelper.cpp \
    gui/selectDb/AddEditDbFileWindow.cpp \
    gui/interfaces/AddEditIfWindow.cpp \
    database/GroupItem.cpp \
    models/GrTableModel.cpp \
    gui/groupsManager/GropusManagerWindow.cpp \
    gui/groupsManager/AddEditGroupWindow.cpp \
    gui/validators/IpValidator.cpp \
    gui/validators/NetMaskValidator.cpp \
    gui/SettingsWindow.cpp \
    models/DbFileModel.cpp \
    gui/interfaces/ChangeGroupWindow.cpp \
    gui/validators/MacValidator.cpp \
    gui/interfaces/AddRangeWindow.cpp \
    gui/ExportWindow.cpp \
    gui/textCodecs/CP852PLCodec.cpp \
    global/LocalSettings.cpp \
    database/DatabaseUpdater.cpp \
    gui/selectDb/DatabaseUpdateWindow.cpp \
    database/InterfaceTypeItem.cpp \
    models/IfTypeTableModel.cpp \
    gui/ifTypeManager/IfTypeManagerWindow.cpp \
    gui/ifTypeManager/AddEditIfTypeWindow.cpp \
    database/ExternalAppItem.cpp \
    models/ExternalAppModel.cpp \
    gui/externalApps/AddEditExternalAppWindow.cpp \
    gui/externalApps/ExternalAppWindow.cpp

HEADERS  += \
    database/IfDbTable.h \
    database/InterfaceItem.h \
    database/NetworkItem.h \
    models/IfTabeModel.h \
    models/IfTableSortProxy.h \
    gui/MainWindow.h \
    gui/AboutWindow.h \
    gui/SelectDbWindow.h \
    database/DbFileItem.h \
    global/SettingsManager.h \
    gui/helpers/HtmlHelper.h \
    gui/selectDb/AddEditDbFileWindow.h \
    gui/interfaces/AddEditIfWindow.h \
    database/GroupItem.h \
    models/GrTableModel.h \
    gui/groupsManager/GropusManagerWindow.h \
    gui/groupsManager/AddEditGroupWindow.h \
    gui/validators/IpValidator.h \
    gui/validators/NetMaskValidator.h \
    gui/SettingsWindow.h \
    models/DbFileModel.h \
    gui/interfaces/ChangeGroupWindow.h \
    gui/validators/MacValidator.h \
    gui/interfaces/AddRangeWindow.h \
    gui/ExportWindow.h \
    gui/textCodecs/CP852PLCodec.h \
    global/LocalSettings.h \
    database/DatabaseUpdater.h \
    gui/selectDb/DatabaseUpdateWindow.h \
    database/InterfaceTypeItem.h \
    models/IfTypeTableModel.h \
    gui/ifTypeManager/IfTypeManagerWindow.h \
    gui/ifTypeManager/AddEditIfTypeWindow.h \
    database/ExternalAppItem.h \
    models/ExternalAppModel.h \
    gui/externalApps/AddEditExternalAppWindow.h \
    gui/externalApps/ExternalAppWindow.h

FORMS    += \
    gui/MainWindow.ui \
    gui/AboutWindow.ui \
    gui/SelectDbWindow.ui \
    gui/selectDb/AddEditDbFileWindow.ui \
    gui/interfaces/AddEditIfWindow.ui \
    gui/groupsManager/GropusManagerWindow.ui \
    gui/groupsManager/AddEditGroupWindow.ui \
    gui/SettingsWindow.ui \
    gui/interfaces/ChangeGroupWindow.ui \
    gui/interfaces/AddRangeWindow.ui \
    gui/ExportWindow.ui \
    gui/selectDb/DatabaseUpdateWindow.ui \
    gui/ifTypeManager/IfTypeManagerWindow.ui \
    gui/ifTypeManager/AddEditIfTypeWindow.ui \
    gui/externalApps/AddEditExternalAppWindow.ui \
    gui/externalApps/ExternalAppWindow.ui

CONFIG += c++11 #console

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

win32:RC_ICONS += c3Network.ico

RESOURCES += \
    resources/resources.qrc


QMAKE_TARGET_PRODUCT = c3Network
#QMAKE_TARGET_DESCRIPTION = description
QMAKE_TARGET_COPYRIGHT = Pawel Worwag

DISTFILES += \
    resources/create.sql \
    resources/u1to2.sql \
    resources/u2to3.sql \
    c3Network.ico \
    resources/u3to4.sql \
    resources/u4to5.sql
