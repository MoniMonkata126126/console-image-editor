target_sources(console_image_editor PRIVATE
        CustomNode.cpp
        CustomNode.h
        CustomQueue.cpp
        CustomQueue.h
)

target_include_directories(console_image_editor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})