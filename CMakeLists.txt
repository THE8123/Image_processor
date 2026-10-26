cmake_minimum_required(VERSION 4.2)
project(Image_processor)

file(GLOB_RECURSE IMAGE_PROCESSOR_SOURCES CONFIGURE_DEPENDS "*.cpp" "*.h")

add_executable(
        image_processor
        ${IMAGE_PROCESSOR_SOURCES}
)
