QT += core gui opengl widgets #проверить по одному
include(QtGifImage/src/gifimage/qtgifimage.pri)

#INCLUDEPATH += $$[QT_INSTALL_HEADERS] #проверить вообще нужен ли?

equals(QT_MAJOR_VERSION, 6): QT += openglwidgets
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    mainwindow.cpp \
    ../3d_viewer_2.0.cpp \
    ../controller/controller.cpp \
    ../viewer/paint/figure.cpp \
    ../viewer/obj/model_info.cpp \
    ../viewer/obj/setting_info.cpp \
    ../viewer/obj/parse.cpp \
    ../viewer/paint/myopenglrenderer.cpp \
    ../viewer/paint/point.cpp \

HEADERS += \
    mainwindow.h \
    ../controller/controller.h \
    ../viewer/paint/figure.h \
    ../viewer/obj/obj.hpp \
    ../viewer/obj/model_info.h \
    ../viewer/obj/setting_info.h \
    ../viewer/obj/tiny_obj_loader.h \
    ../viewer/obj/parse.h \
    ../viewer/paint/myopenglrenderer.h \
    ../viewer/paint/point.h \

FORMS += \
    mainwindow.ui

LIBS += -lgif
#LIBS += -lGL -lGLU

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
