//
// TypeInfo.h
//
// Library: Foundation
// Package: Core
// Module:  TypeInfo
//


#ifndef Foundation_TypeInfo_INCLUDED
#define Foundation_TypeInfo_INCLUDED

#include <typeinfo>
#include <string.h>

namespace Poco {


// for this compiler at least, cross-shared-library type_info
// comparisons don't work, so use typeid(x).name() instead. It's not
// yet clear what the best default strategy is.
#if (defined(__GNUC__) && __GNUC__ >= 3) \
 || defined(_AIX) \
 || (   defined(__sgi) && defined(__host_mips)) \
 || (defined(__hpux) && defined(__HP_aCC)) \
 || (defined(linux) && defined(__INTEL_COMPILER) && defined(__ICC))

#define TYPE_INFO_CMP_NAMES

#endif


class TypeInfo
{

public:
    TypeInfo(const std::type_info& type)
        : _typeInfo(type) {}

    inline bool operator==(const std::type_info& rhs) const
    {
#if defined(TYPE_INFO_CMP_NAMES)
        return !strcmp(_typeInfo.name(), rhs.name());
#else
        return _typeInfo == rhs;
#endif
    }

    inline bool operator!=(const std::type_info& rhs) const
    {
        return !operator==(rhs);
    }

    inline bool operator==(const TypeInfo& rhs) const
    {
        return operator==(rhs._typeInfo);
    }

    inline bool operator!=(const TypeInfo& rhs) const
    {
        return !operator==(rhs);
    }

    inline const char* name() const
    {
        return _typeInfo.name();
    }
private:
    const std::type_info& _typeInfo;
};


} // namespace Poco

#endif
