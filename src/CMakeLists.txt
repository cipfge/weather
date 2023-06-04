set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets SvgWidgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets SvgWidgets Network)

if(${QT_VERSION_MAJOR} LESS 6)
    message(FATAL_ERROR "This project requires Qt6.")
endif()

set(PROJECT_SOURCES
    "main.cpp"
    "geo_location_provider.cpp"
    "geo_location_provider.hpp"
    "main_window.cpp"
    "main_window.hpp"
    "main_window.ui"
    "weather_provider.cpp"
    "weather_provider.hpp"
    "weather_types.hpp"
    )

qt_add_executable(weather MANUAL_FINALIZATION ${PROJECT_SOURCES})

target_link_libraries(weather
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::SvgWidgets
        Qt${QT_VERSION_MAJOR}::Network
    )

set_target_properties(weather
    PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
    )

install(TARGETS weather
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(weather)
endif()
