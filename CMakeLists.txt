cmake_minimum_required(VERSION 3.28)
project(Pong)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_definitions(-DUNICODE -D_UNICODE)
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

include_directories(
        ${CMAKE_SOURCE_DIR}/dependencies/rapidjson/include
        ${CMAKE_SOURCE_DIR}/dependencies/DiscordRPC/include
        ${CMAKE_SOURCE_DIR}/dependencies/SDL2_ttf/include
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/dependencies/SDL2/include
)

set(SOURCES
        src/AiPaddle/AiPaddle.cpp
        src/CourtScene/CourtScene.cpp
        src/CenterDivider/CenterDivider.cpp
        src/DiscordInterface/connection_win.cpp
        src/DiscordInterface/DiscordInterface.cpp
        src/DiscordInterface/discord_register_win.cpp
        src/DiscordInterface/discord_rpc.cpp
        src/DiscordInterface/dllmain.cpp
        src/DiscordInterface/rpc_connection.cpp
        src/DiscordInterface/serialization.cpp
        src/Goal/Goal.cpp
        src/Paddle/Paddle.cpp
        src/Score/Score.cpp
        src/EndScreen/EndScreen.cpp
        src/BoundingBox/boundingBox.cpp
        src/Draw/draw.cpp
        src/Ball/ball.cpp
        src/Game/game.cpp
        src/StartScreen/StartScreen.cpp
        main.cpp
)

set(HEADERS
        src/AiPaddle/AiPaddle.h
        src/CourtScene/CourtScene.h
        src/CenterDivider/CenterDivider.h
        src/DiscordInterface/backoff.h
        src/DiscordInterface/connection.h
        src/DiscordInterface/DiscordInterface.h
        src/DiscordInterface/msg_queue.h
        src/DiscordInterface/rpc_connection.h
        src/DiscordInterface/serialization.h
        src/Goal/Goal.h
        src/Paddle/Paddle.h
        src/Scene/Scene.h
        src/Score/Score.h
        src/EndScreen/EndScreen.h
        src/BoundingBox/boundingBox.h
        src/Draw/draw.h
        src/Ball/ball.h
        src/Game/game.h
        src/StartScreen/StartScreen.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

if(WIN32)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

    target_link_libraries(${PROJECT_NAME} PRIVATE
            ${CMAKE_SOURCE_DIR}/dependencies/SDL2_ttf/lib/x64/SDL2_ttf.lib
            ${CMAKE_SOURCE_DIR}/dependencies/SDL2/lib/x64/SDL2.lib
            ${CMAKE_SOURCE_DIR}/dependencies/SDL2/lib/x64/SDL2main.lib
    )

    foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
        set_target_properties(${PROJECT_NAME} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${CMAKE_SOURCE_DIR}/bin/${OUTPUTCONFIG}
        )
    endforeach()

    foreach(CONFIG_TYPE ${CMAKE_CONFIGURATION_TYPES})
        if(${CONFIG_TYPE} MATCHES "Debug")
            target_compile_definitions(${PROJECT_NAME} PRIVATE _DEBUG _CONSOLE)
            target_compile_options(${PROJECT_NAME} PRIVATE /W3 /sdl /permissive- /Zc:preprocessor /Zc:inline /Zc:forScope /std:c++20)
        else()
            target_compile_definitions(${PROJECT_NAME} PRIVATE NDEBUG _CONSOLE)
            target_compile_options(${PROJECT_NAME} PRIVATE /W3 /GL /sdl /permissive- /Zc:preprocessor /Zc:inline /Zc:forScope /std:c++20)
        endif()
    endforeach()

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/dependencies/SDL2/lib/x64/SDL2.dll
            ${CMAKE_SOURCE_DIR}/bin/$<CONFIGURATION>/SDL2.dll
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/dependencies/SDL2_ttf/lib/x64/SDL2_ttf.dll
            ${CMAKE_SOURCE_DIR}/bin/$<CONFIGURATION>/SDL2_ttf.dll
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/font
            ${CMAKE_SOURCE_DIR}/bin/$<CONFIGURATION>/font
    )
endif()