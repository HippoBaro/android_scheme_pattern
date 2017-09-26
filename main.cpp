#include <password_space.hpp>
#include <cinttypes>

int main() {
    using hippobaro::password_cellphone::password_space;

    OPTIONAL_CONSTEXPR auto possibilities = password_space<3, 3>().resolve();

    uint64_t tot = 0;
    for (int i = 3; i < 3 * 3; ++i) {
        printf("%d nodes combinations: %" PRIu64 "\n", i+1, possibilities[i]);
        tot += possibilities[i];
    }
    printf("Total: %" PRIu64 "\n", tot);
    return EXIT_SUCCESS;
}