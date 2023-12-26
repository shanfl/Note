project(CMAKE_TEST)

#joblib
SET(DOWNLOAD_PATH "/home/shanfl/works/liver-biso_build")
#SET(DOWNLOAD_PATH ${PROJECT_BINARY_DIR})
SET(JOBLIB_URL "https://pypi.python.org/packages/source/j/joblib/joblib-0.4.6.dev.tar.gz")

SET(JOBLIB_NAME joblib-0.4.6.dev.tar.gz)


FIND_FILE(LOCAL_JOBLIB 
    NAMES ${JOBLIB_NAME}
    PATHS ${DOWNLOAD_PATH}
)

IF(NOT LOCAL_JOBLIB)
    file(DOWNLOAD ${JOBLIB_URL}  "${DOWNLOAD_PATH}/joblib-0.4.6.dev.tar.gz" SHOW_PROGRESS)
ENDIF()

MESSAGE(STATUS "LOCAL_JOBLIB:" ${LOCAL_JOBLIB})
MESSAGE(STATUS "cmake:" ${CMAKE_COMMAND})

EXECUTE_PROCESS(
    COMMAND ${CMAKE_COMMAND} -E tar xfz "${JOBLIB_NAME}"
    WORKING_DIRECTORY "${DOWNLOAD_PATH}"
    RESULT_VARIABLE tar_result
)

MESSAGE("begin install setup joblib")

#(cd ./joblib-0.4.6.dev;  ../Slicer-build/Slicer4 --launch ../python-build/bin/python setup.py install)
# ./python -m pip install scipy
# ./python -m pip install scikit-image
EXECUTE_PROCESS(
    COMMAND ../Slicer-build/Slicer --launch ../python-build/bin/python setup.py install
    WORKING_DIRECTORY "${DOWNLOAD_PATH}/joblib-0.4.6.dev"
    RESULT_VARIABLE tar_result
)

EXECUTE_PROCESS(
    COMMAND ./python-build/bin/python -m pip install scipy
    WORKING_DIRECTORY "${DOWNLOAD_PATH}"
    RESULT_VARIABLE tar_result
)

EXECUTE_PROCESS(
    COMMAND ./python-build/bin/python -m pip install scikit-image
    WORKING_DIRECTORY "${DOWNLOAD_PATH}"
    RESULT_VARIABLE tar_result
)




