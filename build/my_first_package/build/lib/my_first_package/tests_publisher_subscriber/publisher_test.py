#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import String

class PublisherTest(Node):
    def __init__(self, node_name):
        super().__init__(node_name)
        # Parámetros: tipo de dato, nombre topic, queue size del topic
        self.publisher_ = self.create_publisher(String, "robot_news", 10)
        self.timer_ = self.create_timer(0.5, self.publish)
        self.get_logger().info("Publisher test started")
    
    def publish(self):
        msg = String()
        msg.data = "Publisher test"
        self.publisher_.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    node = PublisherTest("publisher_test")
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
