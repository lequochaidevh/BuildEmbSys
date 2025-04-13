#include <iostream>
#include <cmath>
#include <algorithm>

#define PI 3.14159265

// ===== PID Controller =====
class PID {
public:
    PID(double kp, double ki, double kd)
        : Kp(kp), Ki(ki), Kd(kd), prev_error(0), integral(0) {}

    double update(double setpoint, double current, double dt) {
        double error = setpoint - current;
        integral += error * dt;
        double derivative = (error - prev_error) / dt;
        prev_error = error;
        return Kp * error + Ki * integral + Kd * derivative;
    }

private:
    double Kp, Ki, Kd;
    double prev_error;
    double integral;
};

// ===== Compute Roll & Pitch angles from desired acceleration vector =====
void computeTargetAngles(double ax, double ay, double g,
                         double& pitch_target, double& roll_target) {
    double norm = std::sqrt(ax * ax + ay * ay + g * g);
    double x = -ax / norm;
    double y = -ay / norm;
    double z = -g / norm;

    pitch_target = std::asin(x) * 180.0 / PI;
    roll_target = std::atan2(y, -z) * 180.0 / PI;
}

int clamp(int value, int min_val, int max_val) {
    return std::max(min_val, std::min(value, max_val));
}

// ===== Main Simulation =====
int main() {
    // ===== PID Controllers =====
    PID pid_x(1.2, 0.0, 0.4);       // PID for X position
    PID pid_y(1.2, 0.0, 0.4);       // PID for Y position
    PID pid_pitch(1.0, 0.0, 0.2);   // PID for Pitch control
    PID pid_roll(1.0, 0.0, 0.2);    // PID for Roll control

    // Current state
    double pos_x = 0.0, pos_y = 0.0;
    double vel_x = 0.0, vel_y = 0.0;
    double current_pitch = 0.0, current_roll = 0.0;

    // Target coordinates
    double target_x = 2.0;
    double target_y = 2.0;

    double dt = 0.03;
    double g = 9.81;
    int base_pwm = 1500;

    std::cout << "The drone will fly to the point (" << target_x << ", " << target_y << ")\n\n";

    for (int i = 0; i < 1000; ++i) {
        // ===== 0. Check distance to target =====
        double err_dist = std::sqrt(std::pow(target_x - pos_x, 2) + std::pow(target_y - pos_y, 2));
        if (err_dist < 0.1) {
            std::cout << " Drone reached the target position at time " << i * dt << "s!\n";
            break;
        }

        // ===== 1. PID position control → desired acceleration =====
        double ax = pid_x.update(target_x, pos_x, dt);
        double ay = pid_y.update(target_y, pos_y, dt);

        // ===== 2. Compute required Roll & Pitch to create ax, ay =====
        double pitch_target = 0, roll_target = 0;
        computeTargetAngles(ax, ay, g, pitch_target, roll_target);

        // Limit tilt angles to avoid flipping the drone
        pitch_target = clamp(pitch_target, -20.0, 20.0);
        roll_target = clamp(roll_target, -20.0, 20.0);

        // ===== 3. PID to maintain desired Pitch & Roll =====
        double pitch_cmd = pid_pitch.update(pitch_target, current_pitch, dt);
        double roll_cmd = pid_roll.update(roll_target, current_roll, dt);

        // ===== 4. Simulate drone reaction =====
        current_pitch += pitch_cmd * dt;
        current_roll += roll_cmd * dt;

        // ===== 5. Simulate position change =====
        // Simplified: drone velocity is proportional to tilt angle
        vel_x += -std::sin(current_pitch * PI / 180.0) * g * dt;
        vel_y += -std::sin(current_roll * PI / 180.0) * g * dt;

        pos_x += vel_x * dt;
        pos_y += vel_y * dt;

        // ===== 6. Motor PWM signals =====
        int pwm_m1 = clamp(base_pwm - pitch_cmd + roll_cmd, 1100, 1900);
        int pwm_m2 = clamp(base_pwm - pitch_cmd - roll_cmd, 1100, 1900);
        int pwm_m3 = clamp(base_pwm + pitch_cmd - roll_cmd, 1100, 1900);
        int pwm_m4 = clamp(base_pwm + pitch_cmd + roll_cmd, 1100, 1900);

        // ===== 7. Output results =====
        std::cout << "Time: " << i * dt << "s | Pos: (" << pos_x << ", " << pos_y << ") ";
        std::cout << "| Pitch: " << current_pitch << " | Roll: " << current_roll << "\n";
        std::cout << "  PWM M1: " << pwm_m1 << " | M2: " << pwm_m2
                  << " | M3: " << pwm_m3 << " | M4: " << pwm_m4 << "\n\n";
    }

    return 0;
}