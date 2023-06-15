# Normalize the given path depending the platform
function(normalize_path PATH_TO_TRANSFORM TRANSFORMED_PATH_VAR)
    if(WIN32)
        execute_process(
            COMMAND cygpath -w ${PATH_TO_TRANSFORM}
            OUTPUT_VARIABLE ${TRANSFORMED_PATH_VAR}
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    set(${TRANSFORMED_PATH_VAR} ${${TRANSFORMED_PATH_VAR}} PARENT_SCOPE)
    else()
        set(TRANSFORMED_PATH_VAR ${PATH_TO_TRANSFORM})
    endif()
endfunction()
