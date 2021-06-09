## Webots multicamera simulation with ROS



## webots-ros 설치
<pre>
https://cyberbotics.com/doc/guide/tutorial-8-using-ros?tab-ros=melodic 참조 

기본적으로 설치된 Node, launch 파일로 튜토리얼 실행 가능

local repository path
webots : /usr/local/webots
webots_ros : /opt/ros/melodic/share/webots_ros
</pre>

## webots_ros package setting

<pre>
1. mkdir catkin_ws
2. cd catkin_ws
3. mkdir src
4. cd src
5. git clone https://github.com/cyberbotics/webots_ros
6. catkin_make
</pre>

## World 열기
<pre>
1. 본 디렉토리 Webots_multiCamera/worlds 안에 있는 lab.wbt를 catkin_ws/src/webots_ros/worlds 안으로 옮기기
2. $ webots lab.wbt
3. 아래와 같이 안 뜰 경우, File - Reload World

<p align="center">
  <img width="700" src="https://user-images.githubusercontent.com/80872528/121309865-abf3c600-c93d-11eb-89b6-bc9809e820ef.png">
</p>

4. 수정시, File - Save World
</pre>

## Object 올리기

## Device(sensor) setting

## Controller

## Modifying Node

## Visualization

### Reference
<pre>
* https://github.com/cyberbotics/webots_ros
* https://github.com/cyberbotics/webots
* https://cyberbotics.com/doc/guide/tutorial-8-using-ros?tab-ros=melodic
* https://cyberbotics.com/doc/reference/camera?tab-language=ros
* https://cyberbotics.com/doc/reference/rangefinder?tab-language=ros
</pre>
