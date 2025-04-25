#include "rclcpp/rclcpp.hpp"

class MyFirstNode : public rclcpp::Node
{
    public:
    MyFirstNode() : Node("my_first_node") 
    {
        m_timer = this->create_wall_timer(std::chrono::seconds(1), 
            std::bind(&MyFirstNode::timerCallback, this));
    }
    private:
    void timerCallback()
    {
        RCLCPP_INFO(this->get_logger(), "Hello world");
    }
    rclcpp::TimerBase::SharedPtr m_timer;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyFirstNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}