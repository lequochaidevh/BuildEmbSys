# Docker with x11 and toolchain for dev.

```text
docker build -f DockerfileU22 -t yololabel:u22 .

docker run -it --rm --net=host \
-e DISPLAY=$DISPLAY \
-e XAUTHORITY=/tmp/.Xauthority \
-v $(pwd):/devh/ws \
-v /tmp/.X11-unix:/tmp/.X11-unix \
-v /run/user/1000/gdm/Xauthority:/tmp/.Xauthority:ro \
yololabel:u22 bash



```


## IGNORE BELOW

**Check XAUTHORITY**


```text
docker run -it \
--env DISPLAY=$DISPLAY \
--volume /tmp/.X11-unix:/tmp/.X11-unix \
--volume $HOME/.Xauthority:/root/.Xauthority \
--volume $(PWD):/devh/ws \
yololabel:u22
```
check miss lib :
```text
docker run -it \
--env DISPLAY=$DISPLAY \
--volume /tmp/.X11-unix:/tmp/.X11-unix \
--volume $HOME/.Xauthority:/root/.Xauthority \
--volume /home/devh/Desktop/YoloLabel/yololabel:/app/yololabel \
yololabel:u22 /bin/bash
docker run -it \
--env DISPLAY=$DISPLAY \
--volume /tmp/.X11-unix:/tmp/.X11-unix \
--volume $HOME/.Xauthority:/root/.Xauthority \
--volume /home/devh/Desktop/YoloLabel/yololabel:/app/yololabel \
yololabel:u22 xeyes
docker run -it \
    --env DISPLAY=$DISPLAY \
    --volume /tmp/.X11-unix:/tmp/.X11-unix \
    --volume $HOME/.Xauthority:/root/.Xauthority \
    yololabel:u22 xeyes
```

