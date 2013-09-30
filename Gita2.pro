CONFIG(debug,debug|release) {
  DEFINES += "__DEBUG"
}
DEFINES += "__LOG"
#DEFINES += "__DLOG"

#__DEBUG will make asserts on all risky operations, and will output a detailed error message if it fails
#__LOG will output all VBE_LOG(..). This is general (important) info such as resource loading, etc
#__DLOG will output all VBE_DLOG(..). This is detailed log info, use it for debugging.
# Disable all three for faster internets

TEMPLATE = app
CONFIG -= qt
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGL
INCLUDEPATH += $$PWD/
QMAKE_CXXFLAGS += -std=c++11
SOURCES += \
	$$PWD/main.cpp \
	$$PWD/SceneMain/SceneMain.cpp \
	$$PWD/SceneMain/PerspectiveCamera.cpp \
	$$PWD/SceneMain/Map.cpp \
	$$PWD/SceneMain/House.cpp

HEADERS += \
	$$PWD/SceneMain/SceneMain.hpp \
	$$PWD/SceneMain/PerspectiveCamera.hpp \
	$$PWD/SceneMain/Map.hpp \
	$$PWD/SceneMain/House.hpp

OTHER_FILES += \
	$$PWD/data/shaders/sample.vert \
	$$PWD/data/shaders/sample.frag \
	$$PWD/data/shaders/sample2.vert \
	$$PWD/data/shaders/sample2.frag
