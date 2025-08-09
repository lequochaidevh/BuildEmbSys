import os

# =========================
# PROJECT STRUCTURE
# =========================
structure = {
    "core/base": ["types.h", "macros.h", "logger.cpp"],
    "core/system": ["event_loop.h", "task_scheduler.cpp", "memory_manager.cpp"],
    "core/math": ["vector.h", "matrix.h", "quaternion.h"],
    "core/ai": ["base_model.h", "model_registry.cpp", "utils.hpp"],
    "core/net": ["socket.h", "tcp_client.cpp", "http_server.cpp"],
    
    "modules/embedded": ["gpio.cpp", "uart.cpp", "i2c_driver.cpp"],
    "modules/graphics": ["renderer.cpp", "mesh.cpp", "shader_loader.cpp"],
    "modules/camera": ["camera_device.cpp", "capture_manager.cpp", "camera_factory.cpp"],
    "modules/game": ["ecs_system.cpp", "physics_engine.cpp", "scene_manager.cpp"],
    "modules/ai_ext": ["inference_runner.cpp", "onnx_runtime_wrapper.cpp", "vision_utils.cpp"],

    "platform/windows": ["platform_init.cpp", "win_file.cpp"],
    "platform/linux": ["platform_init.cpp", "linux_file.cpp"],
    "platform/android": ["platform_init.cpp", "ndk_interface.cpp"],
    "platform/esp32": ["gpio_driver.c", "esp_platform.c"],

    "apps/test_embedded": ["main.cpp", "config.h"],
    "apps/test_graphics": ["main.cpp", "scene_config.json"],
    "apps/camera_viewer": ["main.cpp", "ui_layout.xml", "camera_config.json"],
    "apps/ai_inference_demo": ["main.py", "models/yolov5.onnx"],
    "apps/game_demo": [
        "main.cpp",
        "assets/textures/.gitkeep",
        "assets/models/.gitkeep",
        "assets/audio/.gitkeep",
        "scenes/level1.scene"
    ],

    "third_party/imgui": [],
    "third_party/opencv": [],
    "third_party/tinyxml2": [],

    "tools": ["asset_converter.py", "profiling_tool.cpp", "dump_config.py"],
    "docs": ["architecture.md", "build_guide.md", "module_overview.md", "README.md"],
    "testing": ["test_math.cpp", "test_event.cpp", "test_camera.cpp", "test_game.cpp"],
    "config": ["default_config.json", "platform_linux.json", "platform_esp32.json"],
    "scripts": ["build.sh", "setup_env.py", "deploy_to_board.sh"],
}

# =========================
# ROOT FILES
# =========================
root_files = [
    "CMakeLists.txt",
    "README.md",
    "LICENSE",
    ".gitignore"
]

# =========================
# BUILD FILE STRUCTURE
# =========================
def create_structure():
    print("Start creating project structure...")
    for path, files in structure.items():
        os.makedirs(path, exist_ok=True)
        for file in files:
            file_path = os.path.join(path, file)
            # Create parent directory if file is deeply nested
            os.makedirs(os.path.dirname(file_path), exist_ok=True)
            with open(file_path, "w") as f:
                f.write(f"// {file}\n")
            print(f"  ✅ Created: {file_path}")
    for file in root_files:
        with open(file, "w") as f:
            f.write(f"# {file}\n")
        print(f"  ✅ Created: {file}")

    print("\n Build structure completed.")

# =========================
# SCRIPT ENTRY POINT
# =========================
if __name__ == "__main__":
    create_structure()
    print("Project structure has been created successfully.")
    print("You can now start adding your code and assets to the project.")
    print("Happy coding! ")