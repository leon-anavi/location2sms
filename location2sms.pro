# Add more folders to ship with the application, here
folder_01.source = qml/TestView
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
CONFIG += qdeclarative-boostable

CONFIG += mobility
MOBILITY += location
MOBILITY += messaging

QT += core
QT += gui
QT += webkit
QT += network
QT += xml
QT += declarative

# Add dependency to Symbian components
# CONFIG += qt-components

symbian:
{
    #TARGET.UID3 = 0x20041EC8
    TARGET.UID3 = 0xE864CBE1
    ICON = location2sms.svg

    # symbian capabilities
    TARGET.CAPABILITY += NetworkServices \
                            Location \
                            ReadUserData \
                            WriteUserData \
                            ReadDeviceData \
                            WriteDeviceData

    packageheader = "$${LITERAL_HASH}{\"location2sms\"}, ($${TARGET.UID3}), 2, 1, 4"
    name_deployment.pkg_prerules = packageheader
    DEPLOYMENT += name_deployment

    vendorinfo = "%{\"Leon Anavi\"}" \
        ":\"Leon Anavi\""
    my_deployment.pkg_prerules = vendorinfo
    DEPLOYMENT += my_deployment
}

# Smart Installer package's UID
# This UID is from the protected range
# and therefore the package will fail to install if self-signed
# By default qmake uses the unprotected range value if unprotected UID is defined for the application
# and 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    proxywidget.cpp \
    urlshortener.cpp \
    settings.cpp \
    reversegeocoding.cpp \
    menuwidget.cpp \
    mainwindow.cpp \
    mainwidget.cpp \
    languageswidget.cpp \
    filedownloader.cpp \
    busyindicator.cpp \
    aboutwidget.cpp

TRANSLATIONS = location2sms_bg.ts location2sms_tr.ts location2sms_de.ts location2sms_ro.ts location2sms_el.ts location2sms_nl.ts location2sms_cs.ts location2sms_id.ts

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog

HEADERS += \
    proxywidget.h \
    urlshortener.h \
    settings.h \
    reversegeocoding.h \
    proxywidget.h \
    menuwidget.h \
    mainwindow.h \
    mainwidget.h \
    languageswidget.h \
    filedownloader.h \
    busyindicator.h \
    aboutwidget.h

RESOURCES += \
    l2sResource.qrc

contains(MEEGO_EDITION,harmattan) {
    icon.files = location2sms.png
    icon.path = /usr/share/icons/hicolor/80x80/apps
    INSTALLS += icon
}

contains(MEEGO_EDITION,harmattan) {
    desktopfile.files = location2sms.desktop
    desktopfile.path = /usr/share/applications
    INSTALLS += desktopfile
}
