cmake_minimum_required(VERSION 3.19)
project(text_editor LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

find_package(GTest REQUIRED)
include(GoogleTest)

qt_add_executable(text_editor
    WIN32 MACOSX_BUNDLE
    main.cpp


    mainlayout.h mainlayout.cpp
    mainwindow.h mainwindow.cpp
    styleclass.h styleclass.cpp
    preprocessor/preprocessor.h preprocessor/preprocessor.cpp
    io/saver.h io/saver.cpp
    io/import.h io/import.cpp
    io/export.h io/export.cpp
    preprocessor/textsegment.h preprocessor/textsegment.cpp
    preprocessor/textparagraph.h preprocessor/textparagraph.cpp
    styleform.h styleform.cpp
    styleviewwidget.h styleviewwidget.cpp
    namefileform.h namefileform.cpp

)
add_executable(tests
    tests/tst_styleclasstest.cpp
    tests/tst_executepropertyfunc.cpp

    io/saver.h io/saver.cpp
    io/import.h io/import.cpp
    io/export.h io/export.cpp
)

target_link_libraries(text_editor
    PRIVATE
        Qt::Core
        Qt::Widgets
)
target_link_libraries(text_editor PRIVATE Qt6::Widgets)

target_link_libraries(tests
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        GTest::GTest
        GTest::Main
)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
gtest_discover_tests(tests)

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
