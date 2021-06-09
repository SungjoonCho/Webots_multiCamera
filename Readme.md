## Webots multicamera simulation with ROS

## Execute

<pre>
1. $ mkdir catkin_ws
2. $ cd catkin_ws
3. $ mkdir src
4. $ cd src
5. $ git clone https://github.com/cyberbotics/webots_ros
6. $ catkin_make

7. 본 디렉토리 Webots_multiCamera 안에 있는 파일 옮기기
   * world/lab.wbt를 catkin_ws/src/webots_ros/worlds 안으로 옮기기
   * src/multisensor.cpp를 catkin_ws/src/webots_ros/src 안으로 옮기기
   * catkin_ws/src/webots_ros/CMakeListss.txt 대신 Webots_multicamera/CMakeLists.txt 덮어쓰기
   
8. $ cd src/webots_ros/worlds
9. $ webots lab.wbt
9. 아래와 같이 안 뜰 경우, File - Reload World

<p align="center">
  <img width="700" src="https://user-images.githubusercontent.com/80872528/121309865-abf3c600-c93d-11eb-89b6-bc9809e820ef.png">
</p>


</pre>

## camera, range finder description

<pre>
1. + 버튼 - Base nodes - Robot 추가 
2. Robot - children 클릭 - + 버튼 - Base nodes - Camera 클릭
3. Device shape 
    1. Robot - children - 본인이 추가한 센서 - children 더블클릭
    2. Shape 추가
    3. Shape - geometry 더블클릭 - Box
4. Object와 마찬가지로 shift + 오른쪽 마우스로 위치 이동 가능
5. 필요시 Parameter 수정 
6. Robot - controller는 ros (ros로 해놓으면 해당 robot의 camera가 본인 name 이용하여 자동으로 topic 설정 후 image publish)  
7-1. controllerArgs는 --name=sensor0으로 설정(본 디렉토리의 rangefinder.cpp에서 여러개의 센서에 service call하게 만들기 위해 name은 모두 sensor + 숫자로 통일)
7-2. 위와 같이 name을 별도로 설정하지 않을 경우, webots 실행할 때마다 device name이 계속 바뀜(처음에는 rangefinder112233, 그다음에는 rangefinder 120421 이렇게)
8. range finder도 위와 마찬가지로 진행
</pre>

## Node description - rangefinder.cpp

<pre>

controllerNameCallback 콜백 함수로 webots에서 실행되는 controller 개수 카운트, controllerCount만큼 for문 진행

for문으로 robot 1개에 있는 각 센서들에 service call "sensor(num)/range_finder/enable", webots에서 이에 응답하며 image publish

본 node에는 robot 하나에 range finder, camera 1개씩 부착되어 있음.(for문 한 번당 robot 1개)

webots에서 동일한 robot 추가시 controllerCount가 개수 자동으로 세어서 그에 맞게 반복 및 service call

그러므로 sensor 이름 통일 필요 (sensor0, sensor1,..)

</pre>


## webots-ros 설치
<pre>
https://cyberbotics.com/doc/guide/tutorial-8-using-ros?tab-ros=melodic 참조 

기본적으로 설치된 Node, launch 파일로 튜토리얼 실행 가능

local repository path
webots : /usr/local/webots
webots_ros : /opt/ros/melodic/share/webots_ros
</pre>

## Object 올리기 & world 새로 만들기

https://cyberbotics.com/doc/guide/tutorial-1-your-first-simulation-in-webots?tab-language=c++&tab-os=linux 참조

### Reference
<pre>
* https://github.com/cyberbotics/webots_ros
* https://github.com/cyberbotics/webots
* https://cyberbotics.com/doc/guide/tutorial-8-using-ros?tab-ros=melodic
* https://cyberbotics.com/doc/reference/camera?tab-language=ros
* https://cyberbotics.com/doc/reference/rangefinder?tab-language=ros
</pre>
