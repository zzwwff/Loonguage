cmake_minimum_required(VERSION 3.16)

project(Loonguage VERSION 0.1 LANGUAGES CXX)

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
    qt_add_executable(Loonguage
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Compiler/Compiler/Address.h Compiler/Compiler/Code.h Compiler/Compiler/CodeGenContext.h Compiler/Compiler/Compiler.h Compiler/Compiler/Error.h Compiler/Compiler/FunctionDeco.h Compiler/Compiler/GeneralSetting.h Compiler/Compiler/IdenDeco.h Compiler/Compiler/Label.h Compiler/Compiler/location.hh Compiler/Compiler/LoonParser.hpp Compiler/Compiler/LoonScanner.h Compiler/Compiler/Node.h Compiler/Compiler/NodeActual.h Compiler/Compiler/NodeExpr.h Compiler/Compiler/NodeFormal.h Compiler/Compiler/NodeFunction.h Compiler/Compiler/NodeProgram.h Compiler/Compiler/NodeSentence.h Compiler/Compiler/position.hh Compiler/Compiler/Register.h Compiler/Compiler/RunTime.h Compiler/Compiler/RuntimeConfig.h Compiler/Compiler/SemanticContext.h Compiler/Compiler/stack.hh Compiler/Compiler/SymbolTable.h Compiler/Compiler/Token.h Compiler/Compiler/TokenIden.h Compiler/Compiler/TokenInt.h Compiler/Compiler/TokenKeyWord.h Compiler/Compiler/Tokens.h Compiler/Compiler/TokenString.h Compiler/Compiler/TokenSymbol.h  Compiler/Compiler/BitStream.h
        Compiler/Compiler/Address.cpp Compiler/Compiler/Code.cpp Compiler/Compiler/CodeGenContext.cpp Compiler/Compiler/Compiler.cpp Compiler/Compiler/Error.cpp Compiler/Compiler/FunctionDeco.cpp Compiler/Compiler/IdenDeco.cpp Compiler/Compiler/Label.cpp Compiler/Compiler/lex.Loon_.cc Compiler/Compiler/LoonParser.cpp  Compiler/Compiler/Node.cpp Compiler/Compiler/NodeActual.cpp Compiler/Compiler/NodeExpr.cpp Compiler/Compiler/NodeFormal.cpp Compiler/Compiler/NodeFunction.cpp Compiler/Compiler/NodeProgram.cpp Compiler/Compiler/NodeSentence.cpp Compiler/Compiler/Register.cpp Compiler/Compiler/RunTime.cpp Compiler/Compiler/RuntimeConfig.cpp Compiler/Compiler/SemanticContext.cpp Compiler/Compiler/SymbolTable.cpp Compiler/Compiler/Token.cpp Compiler/Compiler/TokenIden.cpp Compiler/Compiler/TokenInt.cpp Compiler/Compiler/TokenKeyWord.cpp Compiler/Compiler/Tokens.cpp Compiler/Compiler/TokenString.cpp Compiler/Compiler/TokenSymbol.cpp  Compiler/Compiler/BitStream.cpp
        Compiler/Compiler/win_flex/FlexLexer.h
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Loonguage APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Loonguage SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Loonguage
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Loonguage PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Loonguage)
endif()
set_target_properties(Loonguage PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Loonguage
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Loonguage)
endif()
