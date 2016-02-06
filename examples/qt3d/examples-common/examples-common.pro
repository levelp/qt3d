TEMPLATE = lib
CONFIG += staticlib
TARGET = examples-common
QT += core-private 3dcore 3dcore-private 3drenderer 3dinput 3dlogic qml quick

SOURCES += \
    qfirstpersoncameracontroller.cpp \
    qt3dwindow.cpp \
    qt3dquickwindow.cpp

HEADERS += \
    qfirstpersoncameracontroller.h \
    qfirstpersoncameracontroller_p.h \
    qt3dwindow.h \
    qt3dquickwindow.h


QML_FILES = \
    $$PWD/FirstPersonCameraController.qml

OTHER_FILES += \
    $$QML_FILES

# Create a resource file for qml files that need to be registered by the plugin
GENERATED_RESOURCE_FILE = $$OUT_PWD/examples-common.qrc
INCLUDED_RESOURCE_FILES = $$QML_FILES
RESOURCE_CONTENT = \
    "<RCC>" \
    "<qresource prefix=\"/\">"

for(resourcefile, INCLUDED_RESOURCE_FILES) {
    resourcefileabsolutepath = $$absolute_path($$resourcefile)
    relativepath_in = $$relative_path($$resourcefileabsolutepath, $$_PRO_FILE_PWD_)
    relativepath_out = $$relative_path($$resourcefileabsolutepath, $$OUT_PWD)
    RESOURCE_CONTENT += "<file alias=\"$$relativepath_in\">$$relativepath_out</file>"
}

RESOURCE_CONTENT += \
    "</qresource>" \
    "</RCC>"

write_file($$GENERATED_RESOURCE_FILE, RESOURCE_CONTENT)|error("Aborting.")

RESOURCES += $$GENERATED_RESOURCE_FILE
