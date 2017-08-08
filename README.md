# QUANTUM

**QUANTUM** is a modular and templated C language standard library
extension / replacement aiming to make cross-platform development easier.

It provides portable and high performance modules to solve common problems
and (re-)implementation of various (broken) standard library functions
with modern object-oriented design and sane interfaces.

*C99 or later is required.*

## Modules

There’s no documentation in traditional sense, but the source code is commented
and organized fairly well: check it out and see what’s there.

A brief summary of included modules:

  * **core**: fundamental definitions and language extensions.
  * **integer**: integral types, their bit-precise characteristics,
    absolute value computation, SSE-accelerated (de-)serialization,
    support for 128-bit integer types, which are provided by Clang & GCC.
  * **bitops**: bit-level manipulation of integral variables.
  * **bswap**: reverse the order of bytes in integral variables.
  * **float**: floating-point types and their characteristics.
  * **flint**: floating-point integer definitions.
  * **memory**: opaque memory buffer and generic memory pool.
  * **buffer**: binary byte buffer functions.
  * **character**: ASCII character classification and manipulation.
  * **string**: templates for character string buffer manipulation,
    find & replace, transformation, implicit (null-terminated) strings.
  * **fs**: common file system routines.
  * **io**: common input / output routines.
  * **net**: common network constants, types, macros, and host <-> network
    byte order conversion functions.
  * Lots of other little modules: **time**, **size**, **pointer**, **null**,
    **boolean**, **object**, **array**, **flexible**, etc.

## Users

**QUANTUM** has been used to great success in development of
[Ultraviolet](https://github.com/garnetius/ultraviolet)
and [Jsong](https://github.com/garnetius/jsong).

## Notice

**QUANTUM** is subject to the principle of uncertainty: it’s very experimental
and its API may change at any moment without notice.

What kind of crazy idiot would use it?

Well... You maybe?
