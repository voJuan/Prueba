cmake_minimum_required(VERSION 3.5)

project(tp_poo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tp_poo
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        recursos.qrc
        PantallaInicioUI/pantallainicioui.h PantallaInicioUI/pantallainicioui.cpp PantallaInicioUI/pantallainicioui.ui
        pantallaJuego/pantallajuego.h pantallaJuego/pantallajuego.cpp pantallaJuego/pantallajuego.ui
        PersonajeUI/personajeui.h PersonajeUI/personajeui.cpp
        LectordeArchivos/lectorarchivos.cpp LectordeArchivos/lectorarchivos.h
        niveles/nivel1.h niveles/nivel1.cpp niveles/nivel1.ui
        personajes/personajeabst.h personajes/personajeabst.cpp
        personajes/aldeano.h personajes/aldeano.cpp
        personajes/revolucionario.h personajes/revolucionario.cpp
        personajes/diplomatico.h personajes/diplomatico.cpp
        personajes/refugiadopolitico.h personajes/refugiadopolitico.cpp
        personajes/crearPersonajeAleatorio.cpp
        niveles/nivel2.h niveles/nivel2.cpp niveles/nivel2.ui

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET tp_poo APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(tp_poo SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(tp_poo
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(tp_poo PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.tp_poo)
endif()
set_target_properties(tp_poo PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS tp_poo
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(tp_poo)
endif()
