TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

INCLUDEPATH += C:\\OpenCV2.4.10\\install\\include
LIBS += -LC:\\OpenCV2.4.10\\install\\x64\\mingw\\lib \
        -lopencv_core2410.dll \
        -lopencv_highgui2410.dll \
        -lopencv_imgproc2410.dll \
        -lopencv_features2d2410.dll \
        -lopencv_calib3d2410.dll
