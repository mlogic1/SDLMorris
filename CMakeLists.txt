cmake_minimum_required(VERSION 3.10.2)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(lib/lib-morris)

project(SDLMorris CXX)

SET (INCLUDE_DIR ./include/MorrisSDL/)
SET (SRC_DIR ./src/MorrisSDL/)

SET (SDL2_INCLUDE_DIR ./lib/SDL2-2.0.16/include)
SET (SDL2_IMAGE_INCLUDE_DIR ./lib/SDL2_image-2.0.5/include)
SET (SDL2_MIXER_INCLUDE_DIR ./lib/SDL2_mixer-2.0.4/include)

SET (SDL2_LIB_DIR ./lib/SDL2-2.0.16/lib/x64/)
SET (SDL2_IMAGE_LIB_DIR ./lib/SDL2_image-2.0.5/lib/x64/)
SET (SDL2_MIXER_LIB_DIR ./lib/SDL2_mixer-2.0.4/lib/x64/)

SET (HEADER_FILES
	${INCLUDE_DIR}SDLEliminationPanelView.h
	${INCLUDE_DIR}SDLEndGamePanelView.h
	${INCLUDE_DIR}SDLEvent.h
	${INCLUDE_DIR}SDLMarkerView.h
	${INCLUDE_DIR}SDLMarkerViewEliminatorController.h
	${INCLUDE_DIR}SDLMarkerViewMode.h
	${INCLUDE_DIR}SDLMarkerViewMover.h
	${INCLUDE_DIR}SDLScene.h
	${INCLUDE_DIR}SDLSceneGame.h
	${INCLUDE_DIR}SDLSceneMainMenu.h
	${INCLUDE_DIR}SDLSprite.h
	${INCLUDE_DIR}SDLTextureLoader.h
	${INCLUDE_DIR}SDLWindow.h
	${INCLUDE_DIR}ISDLSprite.h
	${INCLUDE_DIR}SDLAnimatedSprite.h
	${INCLUDE_DIR}SDLAudioLoader.h
	${INCLUDE_DIR}SDLButton.h
)
SET (SRC_FILES 
	./src/main.cpp
	${SRC_DIR}SDLButton.cpp
	${SRC_DIR}SDLEliminationPanelView.cpp
	${SRC_DIR}SDLEndGamePanelView.cpp
	${SRC_DIR}SDLEvent.cpp
	${SRC_DIR}SDLMarkerView.cpp
	${SRC_DIR}SDLMarkerViewEliminatorController.cpp
	${SRC_DIR}SDLMarkerViewMover.cpp
	${SRC_DIR}SDLScene.cpp
	${SRC_DIR}SDLSceneGame.cpp
	${SRC_DIR}SDLSceneMainMenu.cpp
	${SRC_DIR}SDLSprite.cpp
	${SRC_DIR}SDLTextureLoader.cpp
	${SRC_DIR}SDLWindow.cpp
	${SRC_DIR}SDLAnimatedSprite.cpp
)

add_executable(SDLMorris ${HEADER_FILES} ${SRC_FILES})

target_include_directories(SDLMorris PRIVATE ${INCLUDE_DIR})
target_link_libraries(SDLMorris libMorris)

#SDL2
target_link_directories(SDLMorris PRIVATE ${SDL2_LIB_DIR})
target_link_directories(SDLMorris PRIVATE ${SDL2_IMAGE_LIB_DIR})
target_link_directories(SDLMorris PRIVATE ${SDL2_MIXER_LIB_DIR})

target_link_libraries(SDLMorris SDL2)
target_link_libraries(SDLMorris SDL2main)
target_link_libraries(SDLMorris SDL2_image)
target_link_libraries(SDLMorris SDL2_mixer)

target_include_directories(SDLMorris PRIVATE ${SDL2_INCLUDE_DIR})
target_include_directories(SDLMorris PRIVATE ${SDL2_IMAGE_INCLUDE_DIR})
target_include_directories(SDLMorris PRIVATE ${SDL2_MIXER_INCLUDE_DIR})

# copy dlls - TODO:  this should only be done on windows
file(COPY ${SDL2_LIB_DIR}SDL2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_IMAGE_LIB_DIR}SDL2_image.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_IMAGE_LIB_DIR}zlib1.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_IMAGE_LIB_DIR}libjpeg-9.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_IMAGE_LIB_DIR}libpng16-16.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_MIXER_LIB_DIR}libopus-0.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_MIXER_LIB_DIR}libopusfile-0.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_MIXER_LIB_DIR}libvorbis-0.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_MIXER_LIB_DIR}libvorbisfile-3.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_MIXER_LIB_DIR}SDL2_mixer.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_MIXER_LIB_DIR}libFLAC-8.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_MIXER_LIB_DIR}libmodplug-1.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_MIXER_LIB_DIR}libmpg123-0.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SDL2_MIXER_LIB_DIR}libogg-0.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})