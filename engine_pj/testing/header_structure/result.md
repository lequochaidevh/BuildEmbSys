```sh
cmake -B build -DCMAKE_INSTALL_PREFIX=/tmp/module_cam
cmake --build build
cmake --install build
build$ ./apps/camera_viewer/camera_viewer 
[SimpleCamera] opened device: /dev/video0
Got: frame#1 from /dev/video0
Got: frame#2 from /dev/video0
Got: frame#3 from /dev/video0
Got: frame#4 from /dev/video0
Got: frame#5 from /dev/video0
[SimpleCamera] closed device: /dev/video0
[DEBUG] Camera internal utils
```

```text
tree /tmp/module_cam/
/tmp/module_cam/
├── include
│   └── camera_device.h
└── lib
    ├── cmake
    │   └── camera
    │       ├── cameraTargets.cmake
    │       └── cameraTargets-noconfig.cmake
    └── libcamera.a
```