#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts
from functools import partial

class TestServiceClient(Node):
    def __init__(self, node_name):
        super().__init__(node_name)
        self.client_ = self.create_client(AddTwoInts, "test_service_server")

    def send_request(self, a, b):
        # Mientras que el servidor no este listo
        while not self.client_.wait_for_service(1.0):
            self.get_logger().warn("Waiting for server...")
        request = AddTwoInts.Request()
        request.a = a
        request.b = b
        # Llamada asíncrona, rclpy.spin ejecuta continuamente el node
        # añadimos función de callback para cuando la respuesta este
        # lista
        future_obj = self.client_.call_async(request)
        future_obj.add_done_callback(partial(self.callback_response, request=request))

    def callback_response(self, future, request):
        response = future.result()
        self.get_logger().info(str(response.sum))



def main(args=None):
    rclpy.init(args=args)
    node = TestServiceClient("test_service_client")
    node.send_request(20303, 50450)
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()