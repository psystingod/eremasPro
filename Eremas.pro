#-------------------------------------------------
#
# Project created by QtCreator 2018-10-15T00:46:08
#
#-------------------------------------------------

QT       += core gui sql uitools network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Eremas
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        login/loginwindow.cpp \
    dialogs/userfieldempty.cpp \
    dbconnection/mysqlconnection.cpp \
    dbinteraction/mysqlavailabledb.cpp \
    dbinteraction/mysqluserdb.cpp \
    db/availabledb.cpp \
    db/userdb.cpp \
    common/paths.cpp \
    common/setting.cpp \
    login/changedbparameters.cpp \
    common/encryption.cpp \
    common/qaesencryption.cpp \
    login/changepasswordwindow.cpp \
    appwindow/appwindow.cpp \
    main.cpp \
    mainwindow/systemusers.cpp \
    db/taxesdb.cpp \
    dbinteraction/mysqltaxesdb.cpp \
    db/unitsdb.cpp \
    dbinteraction/mysqlunitsdb.cpp \
    db/warehousedb.cpp \
    dbinteraction/mysqlwarehousedb.cpp \
    db/countrydepartmentdb.cpp \
    dbinteraction/mysqlcountrydepartmentdb.cpp \
    db/companycode.cpp \
    dbinteraction/mysqlcompanycode.cpp \
    mainwindow/systeminventoryparameters.cpp \
    dbinteraction/mysqlproductfamilydb.cpp \
    db/productfamilydb.cpp \
    mainwindow/inventory.cpp \
    db/inventorydb.cpp \
    dbinteraction/mysqlinventorydb.cpp \
    mainwindow/catalogofaccounts.cpp \
    db/accountingcatalogdb.cpp \
    dbinteraction/mysqlaccountingcatalogdb.cpp \
    mainwindow/productbilling.cpp \
    mainwindow/salerequest.cpp \
    common/numbertowords.cpp \
    mainwindow/customers.cpp \
    mainwindow/proveedores.cpp \
    mainwindow/departments.cpp


HEADERS += \
        login/loginwindow.h \
    dialogs/userfieldempty.h \
    dbconnection/mysqlconnection.h \
    dbinteraction/mysqlavailabledb.h \
    dbinteraction/mysqluserdb.h \
    db/availabledb.h \
    db/userdb.h \
    common/paths.h \
    common/setting.h \
    login/changedbparameters.h \
    common/encryption.h \
    common/qaesencryption.h \
    login/changepasswordwindow.h \
    appwindow/appwindow.h \
    mainwindow/systemusers.h \
    db/taxesdb.h \
    dbinteraction/mysqltaxesdb.h \
    db/unitsdb.h \
    dbinteraction/mysqlunitsdb.h \
    db/warehousedb.h \
    dbinteraction/mysqlwarehousedb.h \
    db/countrydepartmentdb.h \
    dbinteraction/mysqlcountrydepartmentdb.h \
    db/companycode.h \
    dbinteraction/mysqlcompanycode.h \
    mainwindow/systeminventoryparameters.h \
    dbinteraction/mysqlproductfamilydb.h \
    db/productfamilydb.h \
    mainwindow/inventory.h \
    db/inventorydb.h \
    dbinteraction/mysqlinventorydb.h \
    mainwindow/catalogofaccounts.h \
    db/accountingcatalogdb.h \
    dbinteraction/mysqlaccountingcatalogdb.h \
    mainwindow/productbilling.h \
    mainwindow/salerequest.h \
    common/numbertowords.h \
    mainwindow/customers.h \
    mainwindow/proveedores.h \
    mainwindow/departments.h


FORMS += \
        login/loginwindow.ui \
    dialogs/userfieldempty.ui \
    login/changedbparameters.ui \
    login/changepasswordwindow.ui \
    appwindow/appwindow.ui \
    mainwindow/systemusers.ui \
    mainwindow/systeminventoryparameters.ui \
    mainwindow/inventory.ui \
    mainwindow/catalogofaccounts.ui \
    mainwindow/productbilling.ui \
    mainwindow/salerequest.ui \
    mainwindow/customers.ui \
    mainwindow/proveedores.ui \
    mainwindow/departments.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
