QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../controller/CalcController.cc \
    ../model/ModelCalculator.cc \
    ../model/ModelCredit.cc \
    ../model/ModelDeposit.cc \
    ../model/polishNotation.cc \
    ../model/stringValidation.cc \
    creditwindow.cpp \
    depositwindow.cpp \
    graphwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../controller/CalcController.h \
    ../model/ModelCalculator.h \
    ../model/ModelCredit.h \
    ../model/ModelDeposit.h \
    ../model/polishNotation.h \
    ../model/stringValidation.h \
    creditwindow.h \
    depositwindow.h \
    graphwindow.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    creditwindow.ui \
    depositwindow.ui \
    graphwindow.ui \
    mainwindow.ui
     macx:ICON = $${PWD}/calc_icon.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
