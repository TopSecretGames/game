cmake_policy(SET CMP0017 NEW)

cmake_minimum_required(VERSION 2.8)

set(PROJECT_TEST_NAME app-tests)  
project (${PROJECT_TEST_NAME})
include(ExternalProject)

set(EXCLUDE_PATTERNS
    main.cpp
    AppDelegate.cpp
    ) 


include_directories(${INCLUDE_DIRS})
file(GLOB TEST_SRC *.cpp ${GAME_SRC})
foreach(src ${TEST_SRC})
    foreach(excl ${EXCLUDE_PATTERNS})
        STRING(FIND ${src} ${excl} res)
        if(res EQUAL  -1)
        else(res EQUAL -1)
            list(REMOVE_ITEM TEST_SRC ${src})
        endif(res EQUAL -1)
    endforeach(excl)
endforeach(src)
message(INFO ${TEST_SRC})

add_executable(${PROJECT_TEST_NAME} ${TEST_SRC})

target_link_libraries(${PROJECT_TEST_NAME} cocos2d)

