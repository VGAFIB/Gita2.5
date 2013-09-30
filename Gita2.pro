
include(VBE/VBE.pro)

INCLUDEPATH += .

SOURCES += \
	main.cpp \
	SceneMain/SceneMain.cpp \
	SceneMain/PerspectiveCamera.cpp \
	SceneMain/Map.cpp \
	SceneMain/House.cpp \
    Commons.cpp

HEADERS += \
	SceneMain/SceneMain.hpp \
	SceneMain/PerspectiveCamera.hpp \
	SceneMain/Map.hpp \
	SceneMain/House.hpp \
    Commons.hpp

OTHER_FILES += \
	data/shaders/sample.vert \
	data/shaders/sample.frag \
	data/shaders/sample2.vert \
	data/shaders/sample2.frag
