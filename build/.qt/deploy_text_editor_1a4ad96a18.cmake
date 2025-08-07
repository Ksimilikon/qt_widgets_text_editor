include("/home/ksi/reps/text_editor/build/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/text_editor-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE /home/ksi/reps/text_editor/build/text_editor
    GENERATE_QT_CONF
)
