#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class PublisherTest : public rclcpp::Node
{
    public:
    PublisherTest() : Node("my_first_node") 
    {
        m_publisher = this->create_publisher<example_interfaces::msg::String>("robot_news", 10);
        m_timer = this->create_wall_timer(std::chrono::milliseconds(500), 
                                    std::bind(&PublisherTest::publish, this));
        RCLCPP_INFO(this->get_logger(), "Publisher started");                        
    }
    private:
        void publish() { 
            auto msg = example_interfaces::msg::String();
            msg.data = std::string("Cpp node publisher");
            m_publisher->publish(msg); 
        }
        rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr m_publisher;
        rclcpp::TimerBase::SharedPtr m_timer;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PublisherTest>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}