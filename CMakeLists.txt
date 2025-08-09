cmake_minimum_required(VERSION 3.19)
project(text_editor LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(text_editor
    WIN32 MACOSX_BUNDLE
    main.cpp


    mainlayout.h mainlayout.cpp
    mainwindow.h mainwindow.cpp
    styleclass.h styleclass.cpp
    tests/tst_styleclasstest.cpp
    preprocessor/preprocessor.h preprocessor/preprocessor.cpp
    io/saver.h io/saver.cpp
    io/import.h io/import.cpp
    io/export.h io/export.cpp
    preprocessor/textsegment.h preprocessor/textsegment.cpp
    preprocessor/textparagraph.h preprocessor/textparagraph.cpp

)

target_link_libraries(text_editor
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS text_editor
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET text_editor
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
