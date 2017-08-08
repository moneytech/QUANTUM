// =============================================================================
// <buffer/macros.h>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_C185145C197B48079367DB25A51604E0
#define H_C185145C197B48079367DB25A51604E0

// -----------------------------------------------------------------------------
// Write a constant to memory
// -----------------------------------------------------------------------------

#if CPU(UNALIGNED_ACCESS) && HAVE(INT32) && HAVE(INT16)

  #if CPU(LITTLE_ENDIAN)

    #define buf_set2(b, b0, b1) do {\
      *(u16*)(b) = ((u16)(b1) << 8) | (u16)(b0);\
    } while (0)

    #define buf_set3(b, b0, b1, b2) do {\
      *(u16*)(b) = ((u16)(b1) << 8) | (u16)(b0);\
      (b)[2] = (b2);\
    } while (0)

    #define buf_set4(b, b0, b1, b2, b3) do {\
      *(u32*)(b) = ((u32)(b3) << 24) | ((u32)(b2) << 16) | ((u32)(b1) << 8) | (u32)(b0);\
    } while (0)

    #define buf_set5(b, b0, b1, b2, b3, b4) do {\
      *(u32*)(b) = ((u32)(b3) << 24) | ((u32)(b2) << 16) | ((u32)(b1) << 8) | (u32)(b0);\
      (b)[4] = (b4);\
    } while (0)

    #define buf_set6(b, b0, b1, b2, b3, b4, b5) do {\
      *(u32*)(b) = ((u32)(b3) << 24) | ((u32)(b2) << 16) | ((u32)(b1) << 8) | (u32)(b0);\
      *(u16*)((b) + 4) = ((u16)(b5) << 8) | (u16)(b4);\
    } while (0)

    #define buf_set7(b, b0, b1, b2, b3, b4, b5, b6) do {\
      *(u32*)(b) = ((u32)(b3) << 24) | ((u32)(b2) << 16) | ((u32)(b1) << 8) | (u32)(b0);\
      *(u16*)((b) + 4) = ((u16)(b5) << 8) | (u16)(b4);\
      (b)[6] = (b6);\
    } while (0)

    #if CPU(64BIT) && HAVE(INT64)

      #define buf_set8(b, b0, b1, b2, b3, b4, b5, b6, b7) do {\
        *(u64*)(b) = ((u64)(b7) << 56) | ((u64)(b6) << 48) | ((u64)(b5) << 40) | ((u64)(b4) << 32)\
        | ((u64)(b3) << 24) | ((u64)(b2) << 16) | ((u64)(b1) << 8) | (u64)(b0);\
      } while (0)

    #else // (CPU(64BIT) && HAVE(INT64)) ][

      #define buf_set8(b, b0, b1, b2, b3, b4, b5, b6, b7) do {\
        *(u32*)(b) = ((u32)(b3) << 24) | ((u32)(b2) << 16) | ((u32)(b1) << 8) | (u32)(b0);\
        *(u32*)((b) + 4) = ((u32)(b7) << 24) | ((u32)(b6) << 16) | ((u32)(b5) << 8) | (u32)(b4);\
      } while (0)

    #endif // !(CPU(64BIT) && HAVE(INT64))

  #else // CPU(LITTLE_ENDIAN) ][

    #define buf_set2(b, b0, b1) do {\
      *(u16*)(b) = ((u16)(b0) << 8) | (u16)(b1);\
    } while (0)

    #define buf_set3(b, b0, b1, b2) do {\
      *(u16*)(b) = ((u16)(b0) << 8) | (u16)(b1);\
      (b)[2] = (b2);\
    } while (0)

    #define buf_set4(b, b0, b1, b2, b3) do {\
      *(u32*)(b) = ((u32)(b0) << 24) | ((u32)(b1) << 16) | ((u32)(b2) << 8) | (u32)(b3);\
    } while (0)

    #define buf_set5(b, b0, b1, b2, b3, b4) do {\
      *(u32*)(b) = ((u32)(b0) << 24) | ((u32)(b1) << 16) | ((u32)(b2) << 8) | (u32)(b3);\
      (b)[4] = (b4);\
    } while (0)

    #define buf_set6(b, b0, b1, b2, b3, b4, b5) do {\
      *(u32*)(b) = ((u32)(b0) << 24) | ((u32)(b1) << 16) | ((u32)(b2) << 8) | (u32)(b3);\
      *(u16*)((b) + 4) = ((u16)(b4) << 8) | (u16)(b5);\
    } while (0)

    #define buf_set7(b, b0, b1, b2, b3, b4, b5, b6) do {\
      *(u32*)(b) = ((u32)(b0) << 24) | ((u32)(b1) << 16) | ((u32)(b2) << 8) | (u32)(b3);\
      *(u16*)((b) + 4) = ((u16)(b4) << 8) | (u16)(b5);\
      (b)[6] = (b6);\
    } while (0)

    #if CPU(64BIT) && HAVE(INT64)

      #define buf_set8(b, b0, b1, b2, b3, b4, b5, b6, b7) do {\
        *(u64*)(b) = ((u64)(b0) << 56) | ((u64)(b1) << 48) | ((u64)(b2) << 40) | ((u64)(b3) << 32)\
        | ((u64)(b4) << 24) | ((u64)(b5) << 16) | ((u64)(b6) << 8) | (u64)(b7);\
      } while (0)

    #else // (CPU(64BIT) && HAVE(INT64)) ][

      #define buf_set8(b, b0, b1, b2, b3, b4, b5, b6, b7) do {\
        *(u32*)(b) = ((u32)(b0) << 24) | ((u32)(b1) << 16) | ((u32)(b2) << 8) | (u32)(b3);\
        *(u32*)((b) + 4) = ((u32)(b4) << 24) | ((u32)(b5) << 16) | ((u32)(b6) << 8) | (u32)(b7);\
      } while (0)

    #endif // !(CPU(64BIT) && HAVE(INT64))

  #endif // !CPU(LITTLE_ENDIAN)

#else // (CPU(UNALIGNED_ACCESS) && HAVE(INT32) && HAVE(INT16)) ][

  #define buf_set2(b, b0, b1) do {\
    (b)[0] = (b0), (b)[1] = (b1);\
  } while (0)

  #define buf_set3(b, b0, b1, b2) do {\
    (b)[0] = (b0), (b)[1] = (b1), (b)[2] = (b2);\
  } while (0)

  #define buf_set4(b, b0, b1, b2, b3) do {\
    (b)[0] = (b0), (b)[1] = (b1), (b)[2] = (b2), (b)[3] = (b3);\
  } while (0)

  #define buf_set5(b, b0, b1, b2, b3, b4) do {\
    (b)[0] = (b0), (b)[1] = (b1), (b)[2] = (b2), (b)[3] = (b3),\
    (b)[4] = (b4);\
  } while (0)

  #define buf_set6(b, b0, b1, b2, b3, b4, b5) do {\
    (b)[0] = (b0), (b)[1] = (b1), (b)[2] = (b2), (b)[3] = (b3),\
    (b)[4] = (b4), (b)[5] = (b5);\
  } while (0)

  #define buf_set7(b, b0, b1, b2, b3, b4, b5, b6) do {\
    (b)[0] = (b0), (b)[1] = (b1), (b)[2] = (b2), (b)[3] = (b3),\
    (b)[4] = (b4), (b)[5] = (b5), (b)[6] = (b6);\
  } while (0)

  #define buf_set8(b, b0, b1, b2, b3, b4, b5, b6, b7) do {\
    (b)[0] = (b0), (b)[1] = (b1), (b)[2] = (b2), (b)[3] = (b3),\
    (b)[4] = (b4), (b)[5] = (b5), (b)[6] = (b6), (b)[7] = (b7);\
  } while (0)

#endif // !(CPU(UNALIGNED_ACCESS) && HAVE(INT32) && HAVE(INT16))

// -----------------------------------------------------------------------------
// Memory comparison with a constant
// -----------------------------------------------------------------------------

#if CPU(UNALIGNED_ACCESS) && HAVE(INT32) && HAVE(INT16)

  #if CPU(LITTLE_ENDIAN)

    #define buf_equ2(b, b0, b1)\
    (*(u16*)(b) == (((u16)(b1) << 8) | (u16)(b0)))

    #define buf_equ3(b, b0, b1, b2)\
    ((*(u16*)(b) == (((u16)(b1) << 8) | (u16)(b0))) && ((b)[2] == (b2)))

    #define buf_equ3z(b, b0, b1, b2)\
    (*(u32*)(b) == (((u32)(b2) << 16) | ((u32)(b1) << 8) | (u32)(b0)))

    #define buf_equ3o1(b, b0, b1, b2)\
    ((*(u32*)(b) & 0xFFFFFFu) == (((u32)(b2) << 16) | ((u32)(b1) << 8) | (u32)(b0)))

    #define buf_equ4(b, b0, b1, b2, b3)\
    (*(u32*)(b) == (((u32)(b3) << 24) | ((u32)(b2) << 16) | ((u32)(b1) << 8) | (u32)(b0)))

    #define buf_equ5(b, b0, b1, b2, b3, b4)\
    ((*(u32*)(b) == (((u32)(b3) << 24) | ((u32)(b2) << 16) | ((u32)(b1) << 8) | (u32)(b0)))\
    && ((b)[4] == (b4)))

    #define buf_equ6(b, b0, b1, b2, b3, b4, b5)\
    ((*(u32*)(b) == (((u32)(b3) << 24) | ((u32)(b2) << 16) | ((u32)(b1) << 8) | (u32)(b0)))\
    && (*(u16*)((b) + 4) == (((u16)(b5) << 8) | (u16)(b4))))

    #define buf_equ7(b, b0, b1, b2, b3, b4, b5, b6)\
    ((*(u32*)(b) == (((u32)(b3) << 24) | ((u32)(b2) << 16) | ((u32)(b1) << 8) | (u32)(b0)))\
    && (*(u16*)((b) + 4) == (((u16)(b5) << 8) | (u16)(b4))) && ((b)[6] == (b6)))

    #if CPU(64BIT) && HAVE(INT64)

      #define buf_equ5o3(b, b0, b1, b2, b3, b4)\
      ((*(u64*)(b) & 0xFFFFFFFFFFu) == (((u64)(b4) << 32) | ((u64)(b3) << 24)\
      | ((u64)(b2) << 16) | ((u64)(b1) << 8) | (u64)(b0)))

      #define buf_equ6o2(b, b0, b1, b2, b3, b4, b5)\
      ((*(u64*)(b) & 0xFFFFFFFFFFFFu) == (((u64)(b5) << 40) | ((u64)(b4) << 32)\
      | ((u64)(b3) << 24) | ((u64)(b2) << 16) | ((u64)(b1) << 8) | (u64)(b0)))

      #define buf_equ7z(b, b0, b1, b2, b3, b4, b5, b6)\
      (*(u64*)(b) == (((u64)(b6) << 48) | ((u64)(b5) << 40) | ((u64)(b4) << 32)\
      | ((u64)(b3) << 24) | ((u64)(b2) << 16) | ((u64)(b1) << 8) | (u64)(b0)))

      #define buf_equ7o1(b, b0, b1, b2, b3, b4, b5, b6)\
      ((*(u64*)(b) & 0xFFFFFFFFFFFFFFu) == (((u64)(b6) << 48) | ((u64)(b5) << 40)\
      | ((u64)(b4) << 32) | ((u64)(b3) << 24) | ((u64)(b2) << 16) | ((u64)(b1) << 8)\
      | (u64)(b0)))

      #define buf_equ8(b, b0, b1, b2, b3, b4, b5, b6, b7)\
      (*(u64*)(b) == (((u64)(b7) << 56) | ((u64)(b6) << 48) | ((u64)(b5) << 40)\
      | ((u64)(b4) << 32) | ((u64)(b3) << 24) | ((u64)(b2) << 16) | ((u64)(b1) << 8)\
      | (u64)(b0)))

    #else // (CPU(64BIT) && HAVE(INT64)) ][

      #define buf_equ5o3 buf_equ5
      #define buf_equ6o2 buf_equ6

      #define buf_equ7z(b, b0, b1, b2, b3, b4, b5, b6)\
      ((*(u32*)(b) == (((u32)(b3) << 24) | ((u32)(b2) << 16) | ((u32)(b1) << 8) | (u32)(b0)))\
      && (*(u32*)((b) + 4) == (((u32)(b6) << 16) | ((u32)(b5) << 8) | (u32)(b4))))

      #define buf_equ7o1(b, b0, b1, b2, b3, b4, b5, b6)\
      ((*(u32*)(b) == (((u32)(b3) << 24) | ((u32)(b2) << 16) | ((u32)(b1) << 8) | (u32)(b0)))\
      && ((*(u32*)((b) + 4) & 0xFFFFFFu) == (((u32)(b6) << 16) | ((u32)(b5) << 8) | (u32)(b4))))

      #define buf_equ8(b, b0, b1, b2, b3, b4, b5, b6, b7)\
      ((*(u32*)(b) == (((u32)(b3) << 24) | ((u32)(b2) << 16) | ((u32)(b1) << 8) | (u32)(b0)))\
      && (*(u32*)((b) + 4) == (((u32)(b7) << 24) | ((u32)(b6) << 16) | ((u32)(b5) << 8) | (u32)(b4))))

    #endif // !(CPU(64BIT) && HAVE(INT64))

  #else // CPU(LITTLE_ENDIAN) ][

    #define buf_equ2(b, b0, b1)\
    (*(u16*)(b) == (((u16)(b0) << 8) | (u16)(b1)))

    #define buf_equ3(b, b0, b1, b2)\
    ((*(u16*)(b) == (((u16)(b0) << 8) | (u16)(b1))) && ((b)[2] == (b2)))

    #define buf_equ3z(b, b0, b1, b2)\
    (*(u32*)(b) == (((u32)(b0) << 24) | ((u32)(b1) << 16) | ((u32)(b2) << 8)))

    #define buf_equ3o1(b, b0, b1, b2)\
    ((*(u32*)(b) & 0xFFFFFF00u) == (((u32)(b0) << 24) | ((u32)(b1) << 16) | ((u32)(b2) << 8)))

    #define buf_equ4(b, b0, b1, b2, b3)\
    (*(u32*)(b) == (((u32)(b0) << 24) | ((u32)(b1) << 16) | ((u32)(b2) << 8) | (u32)(b3)))

    #define buf_equ5(b, b0, b1, b2, b3, b4)\
    ((*(u32*)(b) == (((u32)(b0) << 24) | ((u32)(b1) << 16) | ((u32)(b2) << 8) | (u32)(b3)))\
    && ((b)[4] == (b4)))

    #define buf_equ6(b, b0, b1, b2, b3, b4, b5)\
    ((*(u32*)(b) == (((u32)(b0) << 24) | ((u32)(b1) << 16) | ((u32)(b2) << 8) | (u32)(b3)))\
    && (*(u16*)((b) + 4) == (((u16)(b4) << 8) | (u16)(b5))))

    #define buf_equ7(b, b0, b1, b2, b3, b4, b5, b6)\
    ((*(u32*)(b) == (((u32)(b0) << 24) | ((u32)(b1) << 16) | ((u32)(b2) << 8) | (u32)(b3)))\
    && (*(u16*)((b) + 4) == (((u16)(b4) << 8) | (u16)(b5))) && ((b)[6] == (b6)))

    #if CPU(64BIT) && HAVE(INT64)

      #define buf_equ5o3(b, b0, b1, b2, b3, b4)\
      ((*(u64*)(b) & 0xFFFFFFFFFF000000u) == (((u64)(b0) << 56) | ((u64)(b1) << 48)\
      | ((u64)(b2) << 40) | ((u64)(b3) << 32) | ((u64)(b4) << 24)))

      #define buf_equ6o2(b, b0, b1, b2, b3, b4, b5)\
      ((*(u64*)(b) & 0xFFFFFFFFFFFF0000u) == (((u64)(b0) << 56) | ((u64)(b1) << 48)\
      | ((u64)(b2) << 40) | ((u64)(b3) << 32) | ((u64)(b4) << 24) | ((u64)(b5) << 16)))

      #define buf_equ7z(b, b0, b1, b2, b3, b4, b5, b6)\
      (*(u64*)(b) == (((u64)(b0) << 56) | ((u64)(b1) << 48) | ((u64)(b2) << 40)\
      | ((u64)(b3) << 32) | ((u64)(b4) << 24) | ((u64)(b5) << 16) | ((u64)(b6) << 8)))

      #define buf_equ7o1(b, b0, b1, b2, b3, b4, b5, b6)\
      ((*(u64*)(b) & 0xFFFFFFFFFFFFFF00u) == (((u64)(b0) << 56) | ((u64)(b1) << 48)\
      | ((u64)(b2) << 40) | ((u64)(b3) << 32) | ((u64)(b4) << 24) | ((u64)(b5) << 16)\
      | ((u64)(b6) << 8)))

      #define buf_equ8(b, b0, b1, b2, b3, b4, b5, b6, b7)\
      (*(u64*)(b) == (((u64)(b0) << 56) | ((u64)(b1) << 48) | ((u64)(b2) << 40)\
      | ((u64)(b3) << 32) | ((u64)(b4) << 24) | ((u64)(b5) << 16) | ((u64)(b6) << 8)\
      | (u64)(b7)))

    #else // (CPU(64BIT) && HAVE(INT64)) ][

      #define buf_equ5o3 buf_equ5
      #define buf_equ6o2 buf_equ6

      #define buf_equ7z(b, b0, b1, b2, b3, b4, b5, b6)\
      ((*(u32*)(b) == (((u32)(b0) << 24) | ((u32)(b1) << 16) | ((u32)(b2) << 8) | (u32)(b3)))\
      && (*(u32*)((b) + 4) == (((u32)(b4) << 24) | ((u32)(b5) << 16) | ((u32)(b6) << 8))))

      #define buf_equ7o1(b, b0, b1, b2, b3, b4, b5, b6)\
      ((*(u32*)(b) == (((u32)(b0) << 24) | ((u32)(b1) << 16) | ((u32)(b2) << 8) | (u32)(b3)))\
      && ((*(u32*)((b) + 4) & 0xFFFFFF00u) == (((u32)(b4) << 24) | ((u32)(b5) << 16) | ((u32)(b6) << 8))))

      #define buf_equ8(b, b0, b1, b2, b3, b4, b5, b6, b7)\
      ((*(u32*)(b) == (((u32)(b0) << 24) | ((u32)(b1) << 16) | ((u32)(b2) << 8) | (u32)(b3)))\
      && (*(u32*)((b) + 4) == (((u32)(b4) << 24) | ((u32)(b5) << 16) | ((u32)(b6) << 8) | (u32)(b7))))

    #endif // !(CPU(64BIT) && HAVE(INT64))

  #endif // !CPU(LITTLE_ENDIAN)

#else // (CPU(UNALIGNED_ACCESS) && HAVE(INT32) && HAVE(INT16)) ][

  #define buf_equ2(b, b0, b1)\
  (((b)[0] == (b0)) && ((b)[1] == (b1)))

  #define buf_equ3(b, b0, b1, b2)\
  (((b)[0] == (b0)) && ((b)[1] == (b1)) && ((b)[2] == (b2)))

  #define buf_equ3z buf_equ3
  #define buf_equ3o1 buf_equ3

  #define buf_equ4(b, b0, b1, b2, b3)\
  (((b)[0] == (b0)) && ((b)[1] == (b1)) && ((b)[2] == (b2)) && ((b)[3] == (b3)))

  #define buf_equ5(b, b0, b1, b2, b3, b4)\
  (((b)[0] == (b0)) && ((b)[1] == (b1)) && ((b)[2] == (b2)) && ((b)[3] == (b3))\
  && ((b)[4] == (b4)))

  #define buf_equ5o3 buf_equ5

  #define buf_equ6(b, b0, b1, b2, b3, b4, b5)\
  (((b)[0] == (b0)) && ((b)[1] == (b1)) && ((b)[2] == (b2)) && ((b)[3] == (b3))\
  && ((b)[4] == (b4)) && ((b)[5] == (b5)))

  #define buf_equ6o2 buf_equ6

  #define buf_equ7(b, b0, b1, b2, b3, b4, b5, b6)\
  (((b)[0] == (b0)) && ((b)[1] == (b1)) && ((b)[2] == (b2)) && ((b)[3] == (b3))\
  && ((b)[4] == (b4)) && ((b)[5] == (b5)) && ((b)[6] == (b6)))

  #define buf_equ7z buf_equ7
  #define buf_equ7o1 buf_equ7

  #define buf_equ8(b, b0, b1, b2, b3, b4, b5, b6, b7)\
  (((b)[0] == (b0)) && ((b)[1] == (b1)) && ((b)[2] == (b2)) && ((b)[3] == (b3))\
  && ((b)[4] == (b4)) && ((b)[5] == (b5)) && ((b)[6] == (b6)) && ((b)[7] == (b7)))

#endif // !(CPU(UNALIGNED_ACCESS) && HAVE(INT32) && HAVE(INT16))

// -----------------------------------------------------------------------------

#endif
