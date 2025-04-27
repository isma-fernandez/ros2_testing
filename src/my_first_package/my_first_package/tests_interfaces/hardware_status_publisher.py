#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from test_interfaces.msg import HardwareStatus

class HardwareStatusPublisher(Node):
    def __init__(self, node_name):
        super().__init__(node_name)
        self.hw_status_pub_ = self.create_publisher(HardwareStatus, "hardware_status",10)
        self.create_timer(1.0, self.timer_callback)
        self.get_logger().info("Hardware status publisher started...")

    def timer_callback(self):
        msg = HardwareStatus()
        msg.are_motors_ready = True
        msg.temperature = 43.7
        msg.debug_message = "Nothing special"
        self.hw_status_pub_.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = HardwareStatusPublisher("hardware_status_publisher")
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()