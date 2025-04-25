#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

class TestServiceServer : public rclcpp::Node
{
    public:
    TestServiceServer() : Node("test_service_server") 
    {
        m_server = this->create_service<example_interfaces::srv::AddTwoInts>("test_service_server", 
            std::bind(&TestServiceServer::process_request, this, std::placeholders::_1, std::placeholders::_2));
        RCLCPP_INFO(this->get_logger(), "Server is waiting for requests...");
    }
    private:
    void process_request(const example_interfaces::srv::AddTwoInts::Request::SharedPtr request, 
        const example_interfaces::srv::AddTwoInts::Response::SharedPtr response) 
        {
            response->sum = request->a + request->b;
            RCLCPP_INFO(this->get_logger(), 
                "%d + %d = %d", (int)request->a, (int)request->b, (int)response->sum);
        }
    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr m_server;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TestServiceServer>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}