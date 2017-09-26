#include <password_space.hpp>
#include <cinttypes>

template<int Columns, int Rows>
auto print_result() {
    using hippobaro::password_cellphone::password_space;

    static_assert(Columns * Rows > 0, "The specified matrix should be at least 1 by 1.");

    OPTIONAL_CONSTEXPR auto possibilities = password_space<Columns, Rows>().resolve();

    uint64_t tot = 0;
    for (int i = 3; i < Columns * Rows; ++i) {
        printf("%d nodes combinations: %" PRIu64 "\n", i+1, possibilities[i]);
        tot += possibilities[i];
    }
    printf("Total: %" PRIu64 "\n", tot);
    return EXIT_SUCCESS;
};

int main() {
    return print_result<3, 3>();
}