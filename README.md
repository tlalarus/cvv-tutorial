# cvv-tutorial
Opencv 의 cvv 모듈을 활용하기 위한 튜토리얼

# docker
```
$ xhost + local: # Add local PC to X-Server white list
$ docker run -it \
  -v <host_image_path>:/home/images \
  -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY <imagename> # Use GUI
```
