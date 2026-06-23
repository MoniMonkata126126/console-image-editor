target_sources(console_image_editor PRIVATE
        action/ActionType.h
        image/Image.cpp
        image/Image.h
        Session.cpp
        Session.h
        action/Action.cpp
        action/Action.h
        ConsoleActionParser.h
        ConsoleActionParser.cpp
        ActionHandler.cpp
        ActionParser.cpp
        Application.cpp
        ActionReceiver.cpp
        ConsoleActionReceiver.h
        ConsoleActionReceiver.cpp
)

target_include_directories(console_image_editor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
