#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class SubscriberTest : public rclcpp::Node
{
    public:
    SubscriberTest() : Node("subscriber_test") 
    {
        // Placeholder indica cuantos argumentos recibe la función de callback, en caso de haber dos
        // seria lo mismo que hay + ", std::placeholders::_2, std::placeholder::_3..."
        m_subscriber = this->create_subscription<example_interfaces::msg::String>("robot_news", 10,
                            std::bind(&SubscriberTest::subscriberCallback, this, std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(), "Subscriber started");
    }
    private:
        void subscriberCallback(const example_interfaces::msg::String::SharedPtr msg)
        {
            RCLCPP_INFO(this->get_logger(), "Received data!");
            RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
        }
        rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr m_subscriber;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SubscriberTest>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}