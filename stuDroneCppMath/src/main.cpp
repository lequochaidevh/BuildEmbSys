/****************************
 *        Front
            ^
            |
        M1     M2
            +
        M4     M3
            |
 *******************************/


 #include <iostream>
 #include <cmath>
 #include <algorithm>
 
 #define PI 3.14159265
 
 class PID {
 public:
     PID(double kp, double ki, double kd) : Kp(kp), Ki(ki), Kd(kd), prev_error(0), integral(0) {}
 
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
 
 void computeTargetAngles(double ax, double ay, double g, double& pitch_target, double& roll_target) {
     double norm = std::sqrt(ax * ax + ay * ay + g * g);
     double x = -ax / norm;
     double y = -ay / norm;
     double z = -g / norm;
 
     pitch_target = std::asin(x) * 180 / PI;
     roll_target = std::atan2(-y, -z) * 180 / PI;
 }
 
 int clamp(int value, int min_val, int max_val) {
     return std::max(min_val, std::min(value, max_val));
 }
 
 int main() {
     PID pid_pitch(1.0, 0.0, 0.2);  // PID controller for pitch
     PID pid_roll(1.0, 0.0, 0.2);   // PID controller for roll
 
     double current_pitch = 0.0;
     double current_roll = 0.0;
 
     double ax = 1.0;  // Desired flight direction in X
     double ay = 1.0;  // Desired flight direction in Y
     double g = 9.81;  // Gravitational acceleration
 
     double pitch_target = 0, roll_target = 0;
     computeTargetAngles(ax, ay, g, pitch_target, roll_target);  // Compute target pitch and roll angles
 
     std::cout << "Desired Pitch: " << pitch_target << " deg\n";
     std::cout << "Desired Roll: " << roll_target << " deg\n\n";
 
     double dt = 0.1;  // Time step for simulation
     int base_pwm = 1500;  // Base PWM value for the motors
 
     for (int i = 0; i < 50; ++i) {
         // Compute PID control outputs for pitch and roll
         double pitch_cmd = pid_pitch.update(pitch_target, current_pitch, dt);
         double roll_cmd = pid_roll.update(roll_target, current_roll, dt);
 
         // Update current state
         current_pitch += pitch_cmd * dt;
         current_roll += roll_cmd * dt;
 
         // Simulate PWM for each motor
         int pwm_m1 = clamp(base_pwm - pitch_cmd + roll_cmd, 1100, 1900);
         int pwm_m2 = clamp(base_pwm - pitch_cmd - roll_cmd, 1100, 1900);
         int pwm_m3 = clamp(base_pwm + pitch_cmd - roll_cmd, 1100, 1900);
         int pwm_m4 = clamp(base_pwm + pitch_cmd + roll_cmd, 1100, 1900);
 
         std::cout << "Time: " << i * dt << "s | Pitch: " << current_pitch
                   << " | Roll: " << current_roll << "\n";
         std::cout << "  PWM M1: " << pwm_m1 << " | M2: " << pwm_m2
                   << " | M3: " << pwm_m3 << " | M4: " << pwm_m4 << "\n\n";
     }
 
     return 0;
 } 