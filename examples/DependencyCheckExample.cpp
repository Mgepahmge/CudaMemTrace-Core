#include <cudamemtrace/core/DependencyCheck.h>

#include <iostream>

int main() {
    std::cout << cudamemtrace::core::dependencyInfoJson() << '\n';
    return 0;
}
