if(WIN32)
    # Find the bin directory of qmake, which is the same directory which contains
    # qtwindeploy
    get_target_property(QMAKE_EXE Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(QT_BIN_DIR "${QMAKE_EXE}" DIRECTORY)

    find_program(WINDEPLOYQT_EXE windeployqt PATHS "${QT_BIN_DIR}")

    message(STATUS "Using windeployqt.exe from ${WINDEPLOYQT_EXE}")

    function(target_qt_deploy TARGET)
        add_custom_command(
                TARGET ${TARGET}
                POST_BUILD
                COMMAND ${WINDEPLOYQT_EXE} --no-libraries "$<TARGET_FILE:${TARGET}>"
                COMMAND_EXPAND_LISTS
        )
    endfunction()
else ()
    function(target_qt_deploy TARGET)
        # no-op on non Windows platforms
    endfunction()
endif ()