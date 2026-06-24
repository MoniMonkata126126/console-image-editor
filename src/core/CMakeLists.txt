target_sources(console_image_editor PRIVATE
        action/ActionType.h
        image/Image.cpp
        image/Image.h
        Session.cpp
        Session.h
        action/Action.cpp
        action/Action.h
        receive/ConsoleActionParser.h
        receive/ConsoleActionParser.cpp
        ActionHandler.cpp
        receive/ActionParser.cpp
        Application.cpp
        receive/ActionReceiver.cpp
        receive/ConsoleActionReceiver.h
        receive/ConsoleActionReceiver.cpp
)

target_include_directories(console_image_editor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
