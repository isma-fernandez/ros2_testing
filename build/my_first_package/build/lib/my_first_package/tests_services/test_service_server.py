#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts

class TestServiceServer(Node):
    def __init__(self, node_name):
        super().__init__(node_name)
        self.server_ = self.create_service(AddTwoInts, "test_service_server", self.process_request)
        self.get_logger().info("Server started")
    def process_request(self, request: AddTwoInts.Request, response: AddTwoInts.Response):
        response.sum = request.a + request.b
        self.get_logger().info(str(request.a) + " + " + str(request.b) + " = " + str(response.sum))
        return response


def main(args=None):
    rclpy.init(args=args)
    node = TestServiceServer("test_service_server")
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()