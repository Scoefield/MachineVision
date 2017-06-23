#-------------------------------------------------
#
# Project created by QtCreator 2017-04-24T19:59:37
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# 一定要加这个，意思是让程序部署到树莓派上的哪个目录中来运行
target.path=/home/pi/Qt-Project
INSTALLS+=target

# 如果使用ffmpeg，一定加这个，这个是添加ffmpeg的头文件和库
INCLUDEPATH += D:/Qt/QtEmbeded5.5.0/Raspberry/arm-linux-gnueabihf/sysroot/usr/local/ffmpeg/include
LIBS += -LD:/Qt/QtEmbeded5.5.0/Raspberry/arm-linux-gnueabihf/sysroot/usr/local/ffmpeg/lib/  -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lswscale -lswresample

# 如果使用opencv，一定要加这个，这个是添加opencv的头文件和库
# INCLUDEPATH += D:/Qt/QtEmbeded5.5.0/Raspberry/arm-linux-gnueabihf/sysroot/usr/local/opencv/include
# LIBS += -LD:/Qt/QtEmbeded5.5.0/Raspberry/arm-linux-gnueabihf/sysroot/usr/local/opencv/lib/  -lopencv_calib3d -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videoio -lopencv_video -lopencv_videostab

# 如果使用opencv3.2.0，一定要加这个，这个是添加opencv的头文件和库
INCLUDEPATH += D:/Qt/QtEmbeded5.5.0/Raspberry/arm-linux-gnueabihf/sysroot/usr/local/opencv3.2.0/include
LIBS += -LD:/Qt/QtEmbeded5.5.0/Raspberry/arm-linux-gnueabihf/sysroot/usr/local/opencv3.2.0/lib/  -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_calib3d -lopencv_ccalib -lopencv_core -lopencv_datasets -lopencv_dnn -lopencv_dpm -lopencv_face -lopencv_features2d -lopencv_flann -lopencv_freetype -lopencv_fuzzy -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_line_descriptor -lopencv_ml -lopencv_objdetect -lopencv_optflow -lopencv_phase_unwrapping -lopencv_photo -lopencv_plot -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_shape -lopencv_stereo -lopencv_stitching -lopencv_structured_light -lopencv_superres -lopencv_surface_matching -lopencv_text -lopencv_tracking -lopencv_video -lopencv_videoio -lopencv_videostab -lopencv_xfeatures2d -lopencv_ximgproc -lopencv_xobjdetect -lopencv_xphoto


TARGET = tired_steer_detect_system
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        widget.cpp \
    detectObject.cpp \
    ImageUtils_0.7.cpp \
    preprocessFace.cpp \
    printmenu.cpp \
    recognition.cpp \
    tired_steer_detect_system.cpp \
    MatToQImage.cpp \
    modedialog.cpp \
    qcustomplot.cpp

HEADERS  += widget.h \
    detectObject.h \
    ImageUtils.h \
    preprocessFace.h \
    printmenu.h \
    recognition.h \
    tired_steer_detect_system.h \
    MatToQImage.h \
    modedialog.h \
    qcustomplot.h

FORMS    += widget.ui \
    modedialog.ui
