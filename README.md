# Artinx RM2019 Guardian ROS Guide

## Author

* Nikename: NERanger
* e-mail: 11712605@mail.sustech.edu.cn
* Github: <https://github.com/NERanger/RM2019-Artinx-Guardian-ROS>

## Download

```bash
git clone https://github.com/NERanger/RM2019-Artinx-Guardian-ROS.git
```

## Usage

### start vision

```bash
roslaunch roborts_bringup gimbal_vision.launch
```

to start action, put "1" into the terminal

before use "CTRL + C" to stop the thread, put "4" into the terminal to stop the action

### start communication with STM32 USART (USART6)

```bash
rosrun serial_send serial_send_node
```

if you fail to open the serial port, try the command below

```bash
sudo chmod 666 /dev/ttyUSB0
```

## camera calibration

### launch camera driver

* ROS pkg: libuvc
* Wiki: <http://wiki.ros.org/libuvc_camera>

use the following bash command to confirm camera's idVendor and idProduct

```bash
lsusb
```

idVendor and idProduct are in the following format

> "idVendor" : "idProduct"

for example

> 046d:08cc

then find the launch file

> roborts_bringup/launch/libuvc.launch

change the following attributes to the corresponding data we found

```xml
<param name="vendor" value="0x05a3"/>
<param name="product" value="0x9210"/>
```

then try to launch the driver

```bash
roslaunch roborts_bringup libuvc.launch
```

if the launch fails due to permission denying, try the command below

```bash
sudo chmod o+w /dev/bus/usb/001/024 <-- where 024 is port number from the error code
```

### perform calibration

use the command below to check camera topic

```bash
rostopic list
```

the output is like this

```bash
/camera/camera_info
/camera/image_raw
```

then run the calibration node

```bash
rosrun camera_calibration cameracalibrator.py --size 8x6 --square 0.108 image:=/camera/image_raw camera:=/camera
```

note that "size" and "square" should match the chess board

"image" and "camera" should match the camera topic name

## Copyright and License

RoboRTS is provided under the [GPL-v3](COPYING).
