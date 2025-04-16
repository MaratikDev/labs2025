QT += widgets
TARGET = 3DVisualizer
TEMPLATE = app
SOURCES += main.cpp \
           mainwindow.cpp \
           logic.cpp \
           entrypoint.cpp \
           surfacewidget.cpp
HEADERS += mainwindow.h \
           appcontext.h \
           entrypoint.h \
           logic.h \
           surfacewidget.h
FORMS += mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
