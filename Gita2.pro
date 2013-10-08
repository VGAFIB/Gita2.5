
include(VBE/VBE.pro)

INCLUDEPATH += .

SOURCES += \
	main.cpp \
	SceneMain/SceneMain.cpp \
	SceneMain/PerspectiveCamera.cpp \
	SceneMain/Map.cpp \
	SceneMain/House.cpp \
    Commons.cpp \
    SceneMain/Character.cpp \
    SceneMain/Animation.cpp \
    SceneMain/Npc.cpp \
    SceneMain/Person.cpp \
    SceneMain/Population.cpp \
    SceneMain/Police.cpp \
    SceneMain/Player.cpp \
    SceneMain/PlayerInput.cpp \
    SceneMain/CameraController.cpp \
    SceneMain/Blood.cpp

HEADERS += \
	SceneMain/SceneMain.hpp \
	SceneMain/PerspectiveCamera.hpp \
	SceneMain/Map.hpp \
	SceneMain/House.hpp \
    Commons.hpp \
    SceneMain/Character.hpp \
    SceneMain/Animation.hpp \
    SceneMain/Npc.hpp \
    SceneMain/Person.hpp \
    SceneMain/Population.hpp \
    SceneMain/Police.hpp \
    SceneMain/Player.hpp \
    SceneMain/PlayerInput.hpp \
    SceneMain/CameraController.hpp \
    SceneMain/Blood.hpp

OTHER_FILES += \
    data/shaders/map.vert \
    data/shaders/map.frag \
    data/shaders/house.vert \
    data/shaders/house.frag \
    data/shaders/character.vert \
    data/shaders/character.frag
