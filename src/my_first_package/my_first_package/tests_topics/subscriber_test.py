#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import String

class SubscriberTest(Node):
    def __init__(self, node_name):
        super().__init__(node_name)
        # Parámetros = tipo de dato, nombre topic, función callback para recoger el msg, queue size
        self.subscriber_ = self.create_subscription(String, "robot_news", self.callback_robot_news, 10)

    def callback_robot_news(self, msg: String):
        self.get_logger().info(msg.data)
def main(args=None):
    rclpy.init(args=args)
    node = SubscriberTest("my_first_node")
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()  