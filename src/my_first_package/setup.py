from setuptools import find_packages, setup

package_name = 'my_first_package'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='neverdiedooms',
    maintainer_email='neverdiedooms@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "my_first_node = my_first_package.template_node.my_first_node:main",
            "publisher_test = my_first_package.tests_topics.publisher_test:main",
            "subscriber_test = my_first_package.tests_topics.subscriber_test:main",
            "test_service_server = my_first_package.tests_services.test_service_server:main",
            "test_service_client_no_oop = my_first_package.tests_services.test_service_client_no_oop:main",
            "test_service_client = my_first_package.tests_services.test_service_client:main",
            "test_hardware_status = my_first_package.tests_interfaces.hardware_status_publisher:main"
        ],
    },
)
