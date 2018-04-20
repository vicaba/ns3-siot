cmake_minimum_required(VERSION 3.10)
project(ns3_dev)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DNS3_LOG_ENABLE)

include_directories(/home/vcaballero/Programs/ns3/ns3-dev/build)
link_directories(/home/vcaballero/Programs/ns3/ns3-dev/build)

set(SOURCE_FILES scratch/ns2-mobility-trace-netanim.cc src/siot/model/service-profile/profile.cc src/siot/model/service-profile/profile.h src/siot/model/service-profile/profile_writer.cc src/siot/model/service-profile/profile_writer.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
        3-dev-core-debug
        3-dev-wave-debug
        3-dev-wifi-debug
        3-dev-netanim-debug
        3-dev-network-debug
        3-dev-internet-debug
        3-dev-mobility-debug
        3-dev-visualizer-debug
        3-dev-applications-debug
        3-dev-point-to-point-debug
        3-dev-siot-debug
)