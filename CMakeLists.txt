cmake_minimum_required(VERSION 3.13)
project(operator)

set(CMAKE_CXX_STANDARD 11)

add_executable(operator src/operator.cpp
        #在raspberry 上再把注释删掉
#include/Motor_Control.cpp include/Motor_Control.h
        include/cascade_classifer.cpp include/cascade_classifer.h
        include/AI_modular.cpp include/AI_modular.h
        )

#在raspberry 上再把注释删掉
#find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
find_package(OpenCV REQUIRED)


target_link_libraries(operator ${OpenCV_LIBS}
#在raspberry 上再把注释删掉
# ${WIRINGPI_LIBRARIES}

)
