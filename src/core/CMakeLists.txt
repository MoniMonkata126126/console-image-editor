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
        action/Transformer.h
        action/Transformer.cpp
        action/transformation/Grayscale.h
        action/transformation/Grayscale.cpp
        action/transformation/Monochrome.h
        action/transformation/Monochrome.cpp
        action/transformation/Negative.h
        action/transformation/Negative.cpp
        action/transformation/RotateRight.h
        action/transformation/RotateRight.cpp
        action/transformation/RotateLeft.h
        action/transformation/RotateLeft.cpp
        action/transformation/FlipTop.h
        action/transformation/FlipTop.cpp
        action/transformation/FlipLeft.h
        action/transformation/FlipLeft.cpp
)

target_include_directories(console_image_editor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
