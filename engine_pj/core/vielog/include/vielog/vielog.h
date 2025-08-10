#ifndef VIELOG_H
#define VIELOG_H

#include <iostream>
#include <string>

namespace vielog {

void log_info(const std::string& msg);
void log_error(const std::string& msg);

} // namespace vielog
#endif // VIELOG_H