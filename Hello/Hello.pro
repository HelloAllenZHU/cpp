TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS +=

INCLUDEPATH += C:\Boost\include\boost-1_70
LIBS += "-LC:\Boost\lib" "-llibboost_unit_test_framework-mgw81-mt-d-x32-1_70"
