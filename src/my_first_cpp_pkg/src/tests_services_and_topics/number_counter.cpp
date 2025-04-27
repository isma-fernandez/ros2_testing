#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"
#include "example_interfaces/srv/set_bool.hpp"

class NumberCounter : public rclcpp::Node
{
    public:
    NumberCounter() : Node("number_counter"), m_counter(0)
    {
        m_subscriber = this->create_subscription<example_interfaces::msg::Int64>(
            "number", 10, std::bind(&NumberCounter::numberCallback, this, std::placeholders::_1));
        m_publisher = this->create_publisher<example_interfaces::msg::Int64>("number_count", 10);
        m_timer = this->create_timer(std::chrono::seconds(1), 
            std::bind(&NumberCounter::publishNumberCounter, this));
        m_resetCounterSrv = this->create_service<example_interfaces::srv::SetBool>(
            "reset_counter", std::bind(&NumberCounter::process_request, this, std::placeholders::_1, std::placeholders::_2));
        RCLCPP_INFO(this->get_logger(), "Number_counter service started!");
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
    void process_request(const example_interfaces::srv::SetBool::Request::SharedPtr request,
        const example_interfaces::srv::SetBool::Response::SharedPtr response)
    {
        if(request->data == true) m_counter = 0;
        response->success = true;
        response->message = "Message received correctly!";
        if(request->data == true) RCLCPP_INFO(this->get_logger(), "Counter reset!");
        else RCLCPP_INFO(this->get_logger(), "Request was false, nothing was done.");
    }
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr m_subscriber;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr m_publisher;
    rclcpp::TimerBase::SharedPtr m_timer;
    rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr m_resetCounterSrv;
    int m_counter;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounter>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}