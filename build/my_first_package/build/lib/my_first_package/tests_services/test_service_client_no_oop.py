#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts

def main(args=None):
    rclpy.init(args=args)
    node = Node("test_service_client_no_oop")
    client = node.create_client(AddTwoInts, "test_service_server")
    while not client.wait_for_service(1.0):
        node.get_logger().warn("Waiting for server...")
    request = AddTwoInts.Request()
    request.a = 6
    request.b = 5
    
    future_obj = client.call_async(request)
    rclpy.spin_until_future_complete(node, future_obj)
    
    response = future_obj.result()
    node.get_logger().info(str(response.sum))

    rclpy.shutdown()

if __name__ == "__main__":
    main()