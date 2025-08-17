#include "vielog/vielog.h"

int main() {
    vielog::log_info("Hello from installed logging library!");
    vielog::log_error("Oops, something went wrong.");
    return 0;
}