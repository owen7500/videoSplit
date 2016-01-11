#-------------------------------------------------
#
# Project created by QtCreator 2015-12-09T10:20:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoSplit
TEMPLATE = app


SOURCES += main.cpp\
        videogui.cpp \
    videoProcessor.cpp \
    vibe.cpp

HEADERS  += videogui.h \
    videoProcessor.h \
    vibe.h

FORMS    += videogui.ui

INCLUDEPATH += D:\opencv\bin\install\include\
            += D:\opencv\bin\install\include\opencv\
            += D:\opencv\bin\install\include\opencv2\

#opencv set
LIBS += D:\opencv\bin\install\x64\mingw\bin\libopencv_calib3d2410.dll
LIBS += D:\opencv\bin\install\x64\mingw\bin\libopencv_contrib2410.dll
LIBS += D:\opencv\bin\install\x64\mingw\bin\libopencv_core2410.dll
LIBS += D:\opencv\bin\install\x64\mingw\bin\libopencv_features2d2410.dll
LIBS += D:\opencv\bin\install\x64\mingw\bin\libopencv_gpu2410.dll
LIBS += D:\opencv\bin\install\x64\mingw\bin\libopencv_highgui2410.dll
LIBS += D:\opencv\bin\install\x64\mingw\bin\libopencv_imgproc2410.dll
LIBS += D:\opencv\bin\install\x64\mingw\bin\libopencv_photo2410.dll
LIBS += D:\opencv\bin\install\x64\mingw\bin\libopencv_superres2410.dll
LIBS += D:\opencv\bin\install\x64\mingw\bin\libopencv_video2410.dll
LIBS += D:\opencv\bin\install\x64\mingw\bin\libopencv_videostab2410.dll


#ffmpeg set
#INCLUDEPATH +=  D:\ffmpeg32\include\

#DEFINES += __STDC_CONSTANT_MACROS

#LIBS += D:\ffmpeg32\bin\avcodec-56.dll
#LIBS += D:\ffmpeg32\bin\avdevice-56.dll
#LIBS += D:\ffmpeg32\bin\avfilter-5.dll
#LIBS += D:\ffmpeg32\bin\avformat-56.dll
#LIBS += D:\ffmpeg32\bin\avutil-54.dll
#LIBS += D:\ffmpeg32\bin\postproc-53.dll
#LIBS += D:\ffmpeg32\bin\swresample-1.dll
#LIBS += D:\ffmpeg32\bin\swscale-3.dll

