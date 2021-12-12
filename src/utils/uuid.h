/**
 * @file uuid.h
 * @author Sihan Li (lshh1015813038@gmail.com)
 * @version 0.1
 * @date 2021-12-09
 */

#ifndef __AGE_UUID__
#define __AGE_UUID__

#include <bitset>

namespace AGE
{

/**
 * @brief Stands for `(U)niversally (U)nique (I)dentifier`.
 * 
 * Essentially, `UUID` is a 64-bit unsigned integer wrapper but with 
 * randomly value.
 */
class UUID
{
public:
    /** @brief default ctor: will create a UUID */
    UUID();

    /** @brief ctor with a given specific UUID value */
    UUID(uint64_t uuid);
    
    /** @brief make UUID hashable */
    operator uint64_t() const;
private:
    /* tranditionally, should use 128-bit label. But, 64-bits works total fine 
    for this tiny AGE engine :) */
    uint64_t _UUID;
};

} // AGE

namespace std
{

/** @brief template specialization - make UUID hashable so that it can be placed 
 * into `std::map`  */
template<>
struct hash<AGE::UUID>
{
    std::size_t operator()(const AGE::UUID &uuid) const
    {
        return hash<uint64_t>()( static_cast<uint64_t>(uuid) );
    }
};

} // std


#endif
