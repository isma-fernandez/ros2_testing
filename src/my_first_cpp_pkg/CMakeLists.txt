cmake_minimum_required(VERSION 3.8)
project(my_first_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(test_interfaces REQUIRED)

add_executable(my_first_node src/template_node/my_first_node.cpp)
add_executable(publisher_test src/tests_topics/publisher_test.cpp)
add_executable(subscriber_test src/tests_topics/subscriber_test.cpp)
add_executable(publisher_test_2 src/tests_topics/publisher_test2.cpp)
add_executable(publisher_and_subscriber_test src/tests_topics/publisher_and_subscriber_test.cpp)
add_executable(test_service_client_no_oop src/tests_services/test_service_client_no_oop.cpp)
add_executable(test_service_client src/tests_services/test_service_client.cpp)
add_executable(test_service_server src/tests_services/test_service_server.cpp)
add_executable(number_counter src/tests_services_and_topics/number_counter.cpp)
add_executable(number_publisher src/tests_services_and_topics/number_publisher.cpp)
add_executable(hardware_status_publisher src/tests_interfaces/hardware_status_publisher.cpp)

ament_target_dependencies(publisher_test_2 rclcpp example_interfaces)
ament_target_dependencies(my_first_node rclcpp)
ament_target_dependencies(publisher_test rclcpp example_interfaces)
ament_target_dependencies(subscriber_test rclcpp example_interfaces)
ament_target_dependencies(publisher_and_subscriber_test rclcpp example_interfaces)
ament_target_dependencies(test_service_client_no_oop rclcpp example_interfaces)
ament_target_dependencies(test_service_client rclcpp example_interfaces)
ament_target_dependencies(test_service_server rclcpp example_interfaces)
ament_target_dependencies(number_counter rclcpp example_interfaces)
ament_target_dependencies(number_publisher rclcpp example_interfaces)
ament_target_dependencies(hardware_status_publisher rclcpp test_interfaces)

install(TARGETS
  my_first_node 
  publisher_test
  subscriber_test
  publisher_test_2
  publisher_and_subscriber_test
  test_service_client_no_oop
  test_service_client
  test_service_server
  number_counter
  number_publisher
  hardware_status_publisher
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
