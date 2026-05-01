#include "formatter_ex.h"
#include "formatter.h"

void formatter_ex(const std::string& message, std::ostream& out) {
    out << formatter(message);
}
