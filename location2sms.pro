# Add files and directories to ship with the application 
# by adapting the examples below.
# file1.source = myfile
# dir1.source = mydir
DEPLOYMENTFOLDERS = # file1 dir1

# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the
# MOBILITY variable.
CONFIG += mobility
MOBILITY += location
MOBILITY += messaging

QT += core
QT += gui
QT += webkit
QT += network
QT += xml
QT += declarative

symbian:
{

    TARGET.UID3 = 0x20041EC8
    #TARGET.UID3 = 0xE864CBE1
    ICON = location2sms.svg

    # symbian capabilities
    TARGET.CAPABILITY += NetworkServices \
                            Location \
                            ReadUserData \
                            WriteUserData \
                            ReadDeviceData \
                            WriteDeviceData

    packageheader = "$${LITERAL_HASH}{\"location2sms\"}, ($${TARGET.UID3}), 2, 0, 0"
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

SOURCES += main.cpp mainwindow.cpp \
    aboutwidget.cpp \
    menuwidget.cpp \
    mainwidget.cpp \
    reversegeocoding.cpp \
    filedownloader.cpp \
    busyindicator.cpp \
    languageswidget.cpp
HEADERS += mainwindow.h \
    aboutwidget.h \
    menuwidget.h \
    mainwidget.h \
    reversegeocoding.h \
    filedownloader.h \
    busyindicator.h \
    languageswidget.h
FORMS += mainwindow.ui

TRANSLATIONS = location2sms_bg.ts location2sms_tr.ts

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qtc_packaging/meego.spec \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog

RESOURCES += \
    l2sResource.qrc



