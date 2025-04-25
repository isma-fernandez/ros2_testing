#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class PublisherAndSubscriberTest : public rclcpp::Node
{
    public:
    PublisherAndSubscriberTest() : Node("publisher_and_subscriber_test"), m_counter(0)
    {
        m_subscriber = this->create_subscription<example_interfaces::msg::Int64>(
            "number", 10, std::bind(&PublisherAndSubscriberTest::numberCallback, this, std::placeholders::_1));
        m_publisher = this->create_publisher<example_interfaces::msg::Int64>("number_counter", 10);
        m_timer = this->create_timer(std::chrono::seconds(1), 
            std::bind(&PublisherAndSubscriberTest::publishNumberCounter, this));
    }
    private:
    void numberCallback(const example_interfaces::msg::Int64::SharedPtr msg){
        m_counter += msg->data;
    }
    void publishNumberCounter() {
        auto msg = example_interfaces::msg::Int64();
        msg.data = m_counter;
        m_publisher->publish(msg);
    }
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr m_subscriber;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr m_publisher;
    rclcpp::TimerBase::SharedPtr m_timer;
    int m_counter;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PublisherAndSubscriberTest>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}