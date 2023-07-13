# cvv-tutorial
Opencv 의 cvv 모듈을 활용하기 위한 튜토리얼

# Docker
```
$ xhost + local: # Add local PC to X-Server white list
$ docker run -it \
  -v <host_image_path>:/home/images \
  -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY <imagename> # Use GUI
```

# Related publications 
* [Interatice visual debugging of CV applications](https://docs.opencv.org/4.5.5/d7/dcf/tutorial_cvv_introduction.html)
* [Diatom autofocusing in brightfield microscopy: a comparative study - ICPR 2000 (link)](https://ieeexplore.ieee.org/document/903548) 
