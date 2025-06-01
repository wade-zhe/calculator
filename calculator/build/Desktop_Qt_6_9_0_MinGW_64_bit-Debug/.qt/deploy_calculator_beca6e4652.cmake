include("C:/Qt/Examples/Qt-6.9.0/widgets/widgets/calculator/build/Desktop_Qt_6_9_0_MinGW_64_bit-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/calculator-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE C:/Qt/Examples/Qt-6.9.0/widgets/widgets/calculator/build/Desktop_Qt_6_9_0_MinGW_64_bit-Debug/calculator.exe
    GENERATE_QT_CONF
)
