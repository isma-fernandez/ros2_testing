#include "rclcpp/rclcpp.hpp"
#include "test_interfaces/msg/hardware_status.hpp"

class HardwareStatusPublisher : public rclcpp::Node
{
    public:
    HardwareStatusPublisher() : Node("hardware_status_publisher") 
    {
        m_timer = this->create_wall_timer(std::chrono::seconds(1), 
            std::bind(&HardwareStatusPublisher::timerCallback, this));
        m_publisher = this->create_publisher<test_interfaces::msg::HardwareStatus>("hardware_status", 10);
    }
    private:
    void timerCallback()
    {
        auto msg = test_interfaces::msg::HardwareStatus();
        msg.are_motors_ready = true;
        msg.debug_message = "Nothing to say.";
        msg.temperature = 47.3;
        m_publisher->publish(msg);
    }
    rclcpp::TimerBase::SharedPtr m_timer;
    rclcpp::Publisher<test_interfaces::msg::HardwareStatus>::SharedPtr m_publisher;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<HardwareStatusPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}