#!/bin/bash
colcon build --packages-select my_first_package --symlink-install
source install/setup.bash
