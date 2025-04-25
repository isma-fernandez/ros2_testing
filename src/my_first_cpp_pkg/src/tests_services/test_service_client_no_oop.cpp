#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("test_service_client_no_oop");
    
    auto client = node->create_client<example_interfaces::srv::AddTwoInts>("test_service_server");
    while (!client->wait_for_service(std::chrono::seconds(1)))
    {
        RCLCPP_WARN(node->get_logger(), "Waiting for server...");
    }
    auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
    request->a = 60000;
    request->b = 75003;
    auto future_obj = client->async_send_request(request);
    rclcpp::spin_until_future_complete(node, future_obj);

    auto response = future_obj.get();
    RCLCPP_INFO(node->get_logger(), "%d + %d = %d", (int)request->a, (int)request->b, (int)response->sum);

    rclcpp::shutdown();
    return 0;
}