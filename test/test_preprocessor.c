#ifndef HELLO
#define HELLO 3
#define NEWLINE_THING                                                          \
    int x = 3;                                                                 \
    return x;
#else
#undef HELLO
#endif

int main() {
    int x = HELLO;
    return x; // 3
}
