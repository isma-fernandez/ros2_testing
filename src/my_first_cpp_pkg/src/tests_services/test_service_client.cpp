#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

class TestServiceClient : public rclcpp::Node
{
    public:
    TestServiceClient() : Node("test_service_client") 
    {
        m_client = this->create_client<example_interfaces::srv::AddTwoInts>("test_service_server");
        
    }
    void send_request(int a, int b)
    {
        auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = a;
        request->b = b;
        while(!m_client->wait_for_service(std::chrono::seconds(1)))
        {
            RCLCPP_WARN(this->get_logger(), "Waiting for server...");
        }
        m_client->async_send_request(request, std::bind(&TestServiceClient::callback_function, this, std::placeholders::_1));
    }   
    private:
    void callback_function(rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture future)
    {
        auto response = future.get();
        RCLCPP_INFO(this->get_logger(), "Sum: %d", (int)response->sum);
    }
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr m_client;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TestServiceClient>();
    node->send_request(1404102, 103240);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}