target_sources(console_image_editor PRIVATE
        Action.h
        Image.cpp
        Image.h
        Session.cpp
        Session.h
        Transformation.cpp
        Transformation.h
)

target_include_directories(console_image_editor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
