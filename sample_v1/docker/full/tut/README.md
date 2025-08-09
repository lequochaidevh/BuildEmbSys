# Docker with x11 and toolchain for dev.

```text
docker build -f DockerfileU22 -t devh_fullenv:u22 .

docker run -it --rm --net=host \
-e DISPLAY=$DISPLAY \
-e XAUTHORITY=/tmp/.Xauthority \
-v $(pwd):/home/$(whoami)/ws \
-v /tmp/.X11-unix:/tmp/.X11-unix \
-v /run/user/1000/gdm/Xauthority:/tmp/.Xauthority:ro \
yololabel:u22 bash



```
**Some options docker container**
```sh
docker run --name devhname

# docker run with detached (background)
docker run --name devhname -d my-image

# auto restart if stop 
docker run --name my-container --restart unless-stopped -d my-image
# if wanna stop run: docker stop

# restart container
docker restart my-container

docker exec -it my-container-name /bin/bash



```

**Check XAUTHORITY**


**Docker user**

```sh
docker run -it --rm \
--name user-container \
-v $HOME:/home/$USER \
-e HOST_UID=$(id -u) \
-e HOST_GID=$(id -g) \
-e HOST_USER=$USER \
ubuntu-user:dev
```
