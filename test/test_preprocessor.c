#ifndef HELLO
#define HELLO 3
#else
#undef HELLO
#endif

int main() {
    int x = HELLO;
    return x; // 3
}
