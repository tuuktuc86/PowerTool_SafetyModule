# PowerTool_SafetyModule
Developing a safety module to be installed on power tools. It detects the user's safety status and stops the system in dangerous situations to ensure safety.

# 개요
안전 모듈에 전동 공구를 장착하여 사용한다. 안전 모듈은 사용자의 자세를 감지하여 위험 상태라고 판단되면 전원을 차단하여 사용자의 안전을 확보한다.
<br>
# 개발 배경
전동 공구 사용 중 발생하는 부상은 끊임없이 일어난다. 안전 장비가 존재하지만 불편함과 작업 효율 저하의 단점으로 착용률이 떨어지고 안전 사고를 온전히 예방하지 못한다. 그래서 우리는 전동 공구 자체적으로 부착하여 사용할 수 있는 안전 모듈을 만들고자 하였다. 사용중 불편함이 없고 작업의 효율성을 떨어뜨리지 않으면서 사용자의 안전을 확보할 수 있는 안전 모듈을 목표로 하였다.
<br>

# 주요 기능

1. 위험 상황 감지<br>
    IMU 센서와 초음파 센서를 활용하여 사용자의 위험 상태를 감지한다. 사용자가 넘어지거나 전동공구가 부자연스러운 동작으로 위치할 경우를 감지한다.
<br>

2. 위험 상황 알림<br>
위험 상황이 감지되면 LED와 부저를 이용하여 사용자에게 위험 상황을 전달한다.
<br>

3. 호환성 확보<br>
모듈 형태로 개발되어 배터리 접합 부분이 같은 전동 공구에 폭넓게 사용할 수 있다.

# 사용 기술 및 향후 발전 가능
IMU 센서와 초음파 센서를 이용하여 사용자의 위험도를 파악한다. 안전 모듈은 전동공구의 본체와 배터리 사이에 장착된다. 릴레이 모듈을 사용하여 위험 상황시 전원을 차단한다. 배터리에서 본체로 연결되는 전원을 차단한다.
향후 IMU Odometry 기술을 사용하여 감지의 정확도와 추정하는 pose의 다양성을 확보하는 방향으로 발전 방향성을 잡을 수 있다.

# 동영상
<figure>
  <p align="center">
    <img src="https://github.com/tuuktuc86/PowerTool_SafetyModule/blob/main/images/video.gif" width = "700">
  </p>
</figure>

# ppt
<figure>
  <img src="https://github.com/tuuktuc86/PowerTool_SafetyModule/blob/main/images/ppt/001.jpg">
  <img src="https://github.com/tuuktuc86/PowerTool_SafetyModule/blob/main/images/ppt/002.jpg">
  <img src="https://github.com/tuuktuc86/PowerTool_SafetyModule/blob/main/images/ppt/003.jpg">
  <img src="https://github.com/tuuktuc86/PowerTool_SafetyModule/blob/main/images/ppt/004.jpg">
  <img src="https://github.com/tuuktuc86/PowerTool_SafetyModule/blob/main/images/ppt/005.jpg">
  <img src="https://github.com/tuuktuc86/PowerTool_SafetyModule/blob/main/images/ppt/006.jpg">
  <img src="https://github.com/tuuktuc86/PowerTool_SafetyModule/blob/main/images/ppt/007.jpg">
  <img src="https://github.com/tuuktuc86/PowerTool_SafetyModule/blob/main/images/ppt/008.jpg">
  <img src="https://github.com/tuuktuc86/PowerTool_SafetyModule/blob/main/images/ppt/009.jpg">
  <img src="https://github.com/tuuktuc86/PowerTool_SafetyModule/blob/main/images/ppt/010.jpg">
  <img src="https://github.com/tuuktuc86/PowerTool_SafetyModule/blob/main/images/ppt/011.jpg">
  <img src="https://github.com/tuuktuc86/PowerTool_SafetyModule/blob/main/images/ppt/012.jpg">
  <img src="https://github.com/tuuktuc86/PowerTool_SafetyModule/blob/main/images/ppt/014.jpg">
</figure>
