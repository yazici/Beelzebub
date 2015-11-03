#pragma once

#include <metaprogramming.h>

#include <utils/bitfields.arc.inc>

/*  Bit properties!!1!  */

#ifndef BITFIELD_FLAG_RO
//  Creates a getter for bit-based flags.
#define BITFIELD_FLAG_RO(bitInd, name, varT, var, decB, decG, decV)            \
decV varT const MCATS(name, Bit) = ((varT)1) << bitInd;                        \
decB inline bool MCATS(Get, name)() decG                                       \
{                                                                              \
    return 0 != (var & MCATS(name, Bit));                                      \
}
#endif

#ifndef BITFIELD_FLAG_RW
//  Creates a getter and setter for bit-based flags.
#define BITFIELD_FLAG_RW(bitInd, name, varT, var, decB, decG, decV)            \
decV varT const MCATS(name, Bit) = ((varT)1) << bitInd;                        \
decB inline bool MCATS(Get, name)() decG                                       \
{                                                                              \
    return 0 != (var & MCATS(name, Bit));                                      \
}                                                                              \
decB inline void MCATS(Set, name)(bool const val)                              \
{                                                                              \
    if (val)                                                                   \
        var |=  MCATS(name, Bit);                                              \
    else                                                                       \
        var &= ~MCATS(name, Bit);                                              \
}                                                                              \
decB inline bool MCATS(FetchSet, name)()                                       \
{                                                                              \
    bool res = 0 != (var & MCATS(name, Bit));                                  \
                                                                               \
    var |=  MCATS(name, Bit);                                                  \
                                                                               \
    return res;                                                                \
}                                                                              \
decB inline bool MCATS(FetchClear, name)()                                     \
{                                                                              \
    bool res = 0 != (var & MCATS(name, Bit));                                  \
                                                                               \
    var &= ~MCATS(name, Bit);                                                  \
                                                                               \
    return res;                                                                \
}                                                                              \
decB inline bool MCATS(FetchFlip, name)()                                      \
{                                                                              \
    bool res = 0 != (var & MCATS(name, Bit));                                  \
                                                                               \
    var ^=  MCATS(name, Bit);                                                  \
                                                                               \
    return res;                                                                \
}
#endif

#ifndef BITFIELD_STRM_RO
//  Creates a getter for bit-based masked strings.
#define BITFIELD_STRM_RO(bitInd, bitLen, valT, name, varT, var, decB, decG, decV) \
decV varT const MCATS(name, Offset) = bitInd;                                  \
decV varT const MCATS(name, Bits) = ((((varT)1) << (bitLen)) - 1) << bitInd;   \
decB inline valT MCATS(Get, name)() decG                                       \
{                                                                              \
    return (valT)(var & MCATS(name, Bits));                                    \
}
#endif

#ifndef BITFIELD_STRM_RW
//  Creates a getter and setter for bit-based masked strings.
#define BITFIELD_STRM_RW(bitInd, bitLen, valT, name, varT, var, decB, decG, decV) \
decV varT const MCATS(name, Offset) = bitInd;                                  \
decV varT const MCATS(name, Bits) = ((((varT)1) << (bitLen)) - 1) << bitInd;   \
decB inline valT MCATS(Get, name)() decG                                       \
{                                                                              \
    return (valT)(var & MCATS(name, Bits));                                    \
}                                                                              \
decB inline void MCATS(Set, name)(valT const val)                              \
{                                                                              \
    var = ((varT)val &  MCATS(name, Bits))                                     \
        | (      var & ~MCATS(name, Bits));                                    \
}
#endif

#ifndef BITFIELD_STRO_RO
//  Creates a getter for bit-based masked & offset strings.
#define BITFIELD_STRO_RO(bitInd, bitLen, valT, name, varT, var, decB, decG, decV) \
decV varT const MCATS(name, Offset) = bitInd;                                  \
decV varT const MCATS(name, Bits) = ((((varT)1) << (bitLen)) - 1) << bitInd;   \
decB inline valT MCATS(Get, name)() decG                                       \
{                                                                              \
    return (valT)((var & MCATS(name, Bits)) >> bitInd);                        \
}
#endif

#ifndef BITFIELD_STRO_RW
//  Creates a getter and setter for bit-based masked & offset strings.
#define BITFIELD_STRO_RW(bitInd, bitLen, valT, name, varT, var, decB, decG, decV) \
decV varT const MCATS(name, Offset) = bitInd;                                  \
decV varT const MCATS(name, Bits) = ((((varT)1) << (bitLen)) - 1) << bitInd;   \
decB inline valT MCATS(Get, name)() decG                                       \
{                                                                              \
    return (valT)((var & MCATS(name, Bits)) >> bitInd);                        \
}                                                                              \
decB inline void MCATS(Set, name)(valT const val)                              \
{                                                                              \
    var = (((varT)val << bitInd) &  MCATS(name, Bits))                         \
        | (       var            & ~MCATS(name, Bits));                        \
}
#endif

#ifndef BITFIELD_STRC_RO
//  Creates a getter and setter for bit-based concatenated strings.
#define BITFIELD_STRC_RO(offL, lenL, offH, lenH, valT, name, varT, var, decB, decG, decV) \
decV varT const MCATS(name,  LowOffset) = offL;                                \
decV varT const MCATS(name,  LowBits  ) = ((((varT)1) << (lenL)) - 1) << offL; \
decV varT const MCATS(name, HighOffset) = offH;                                \
decV varT const MCATS(name, HighBits  ) = ((((varT)1) << (lenH)) - 1) << offH; \
decV varT const MCATS(name,Bits) = MCATS(name,LowBits) | MCATS(name,HighBits); \
decB inline valT MCATS(Get, name)() decG                                       \
{                                                                              \
    return (valT)(((var & MCATS(name,  LowBits)) >>         offL)              \
                | ((var & MCATS(name, HighBits)) >> (offH - offL)));           \
}
#endif

#ifndef BITFIELD_STRC_RW
//  Creates a getter and setter for bit-based concatenated strings.
#define BITFIELD_STRC_RW(offL, lenL, offH, lenH, valT, name, varT, var, decB, decG, decV) \
decV varT const MCATS(name,  LowOffset) = offL;                                \
decV varT const MCATS(name,  LowBits  ) = ((((varT)1) << (lenL)) - 1) << offL; \
decV varT const MCATS(name, HighOffset) = offH;                                \
decV varT const MCATS(name, HighBits  ) = ((((varT)1) << (lenH)) - 1) << offH; \
decV varT const MCATS(name,Bits) = MCATS(name,LowBits) | MCATS(name,HighBits); \
decB inline valT MCATS(Get, name)() decG                                       \
{                                                                              \
    return (valT)(((var & MCATS(name,  LowBits)) >>         offL)              \
                | ((var & MCATS(name, HighBits)) >> (offH - offL)));           \
}                                                                              \
decB inline void MCATS(Set, name)(valT const val)                              \
{                                                                              \
    var = (((varT)val <<  offL        ) &  MCATS(name,  LowBits))              \
        | (((varT)val << (offH - lenL)) &  MCATS(name, HighBits))              \
        | (       var                   & ~MCATS(name, Bits));                 \
}
#endif

/*  Some defaults  */

#define BITFIELD_DEFAULT_1W(bitInd, name) \
BITFIELD_FLAG_RW(bitInd, name, uint64_t, this->Value, __bland, const, static)

#define BITFIELD_DEFAULT_1O(bitInd, name) \
BITFIELD_FLAG_RO(bitInd, name, uint64_t, this->Value, __bland, const, static)

#define BITFIELD_DEFAULT_2W(bitInd, bitLen, valT, name) \
BITFIELD_STRM_RW(bitInd, bitLen, valT, name, uint64_t, this->Value, __bland, const, static)

#define BITFIELD_DEFAULT_2O(bitInd, bitLen, valT, name) \
BITFIELD_STRM_RO(bitInd, bitLen, valT, name, uint64_t, this->Value, __bland, const, static)

#define BITFIELD_DEFAULT_3W(offL, lenL, offH, lenH, valT, name) \
BITFIELD_STRC_RW(offL, lenL, offH, lenH, valT, name, uint64_t, this->Value, __bland, const, static)

#define BITFIELD_DEFAULT_3O(offL, lenL, offH, lenH, valT, name) \
BITFIELD_STRC_RO(offL, lenL, offH, lenH, valT, name, uint64_t, this->Value, __bland, const, static)

#define BITFIELD_DEFAULT_4W(bitInd, bitLen, valT, name) \
BITFIELD_STRO_RW(bitInd, bitLen, valT, name, uint64_t, this->Value, __bland, const, static)

#define BITFIELD_DEFAULT_4O(bitInd, bitLen, valT, name) \
BITFIELD_STRO_RO(bitInd, bitLen, valT, name, uint64_t, this->Value, __bland, const, static)

#define BITFIELD_DEFAULT_1W32(bitInd, name) \
BITFIELD_FLAG_RW(bitInd, name, uint32_t, this->Value, __bland, const, static)

#define BITFIELD_DEFAULT_1O32(bitInd, name) \
BITFIELD_FLAG_RO(bitInd, name, uint32_t, this->Value, __bland, const, static)

#define BITFIELD_DEFAULT_2W32(bitInd, bitLen, valT, name) \
BITFIELD_STRM_RW(bitInd, bitLen, valT, name, uint32_t, this->Value, __bland, const, static)

#define BITFIELD_DEFAULT_2O32(bitInd, bitLen, valT, name) \
BITFIELD_STRM_RO(bitInd, bitLen, valT, name, uint32_t, this->Value, __bland, const, static)

#define BITFIELD_DEFAULT_3W32(offL, lenL, offH, lenH, valT, name) \
BITFIELD_STRC_RW(offL, lenL, offH, lenH, valT, name, uint32_t, this->Value, __bland, const, static)

#define BITFIELD_DEFAULT_3O32(offL, lenL, offH, lenH, valT, name) \
BITFIELD_STRC_RO(offL, lenL, offH, lenH, valT, name, uint32_t, this->Value, __bland, const, static)

#define BITFIELD_DEFAULT_4W32(bitInd, bitLen, valT, name) \
BITFIELD_STRO_RW(bitInd, bitLen, valT, name, uint32_t, this->Value, __bland, const, static)

#define BITFIELD_DEFAULT_4O32(bitInd, bitLen, valT, name) \
BITFIELD_STRO_RO(bitInd, bitLen, valT, name, uint32_t, this->Value, __bland, const, static)
