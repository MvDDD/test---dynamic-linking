#ifndef LIBVER_H_
#define LIBVER_H_

#define CONCAT2(a, b) a##b
#define CONCAT(a, b) CONCAT2(a, b)

#if !defined(NDEBUG) && !defined(__OPTIMIZE__)
// Debug/development build: embed version strings into .libver section
#define LIBVER_C(NAME, VER) \
    __attribute__((used)) __attribute__((section(".libver"))) static const char NAME[] = "LIBVER:" #NAME ":" VER;

#define LIBVER_H(NAME, CNAME, VER) \
    __attribute__((used)) __attribute__((section(".libver"))) static const char CONCAT(CONCAT(NAME, _), CNAME)[] = "LIBVER:" #NAME ":support:" #CNAME ":" VER;

#else
// Release: no-op macros (safe fallback)
#define LIBVER_C(NAME, VER)
#define LIBVER_H(NAME, CNAME, VER)

#endif

#endif // LIBVER_H_

