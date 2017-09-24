#include <password_space.hpp>

int main() {
    using hippobaro::password_cellphone::password_space;

    OPTIONAL_CONSTEXPR auto possibilities = password_space<3, 3>().resolve();

    printf("Result : %d\n", possibilities);
    return EXIT_SUCCESS;
}