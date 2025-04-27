#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class NumberPublisher : public rclcpp::Node
{
    public:
    NumberPublisher() : Node("number_publisher") 
    {
        m_publisher = this->create_publisher<example_interfaces::msg::Int64>(
            "number", 10);
        m_timer = this->create_wall_timer(std::chrono::seconds(1), 
            std::bind(&NumberPublisher::publish, this));
        RCLCPP_INFO(this->get_logger(), "Started number publisher");
    }
    private:
        void publish()
        {
            auto msg = example_interfaces::msg::Int64();
            msg.data = 2;
            m_publisher->publish(msg);
        }
        rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr m_publisher;
        rclcpp::TimerBase::SharedPtr m_timer;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}