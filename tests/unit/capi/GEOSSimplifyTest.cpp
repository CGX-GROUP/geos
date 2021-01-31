//
// Test Suite for C-API GEOSSimplify

#include <tut/tut.hpp>
// geos
#include <geos_c.h>
// std
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <memory>

#include "capi_test_utils.h"

namespace tut {
//
// Test Group
//

// Common data used in test cases.
struct test_capigeossimplify_data : public capitest::utility {
    GEOSGeometry* geom1_;
    GEOSGeometry* geom2_;

    test_capigeossimplify_data()
        : geom1_(nullptr), geom2_(nullptr)
    {}

    ~test_capigeossimplify_data()
    {
        GEOSGeom_destroy(geom1_);
        GEOSGeom_destroy(geom2_);
        geom1_ = nullptr;
        geom2_ = nullptr;
    }

};

typedef test_group<test_capigeossimplify_data> group;
typedef group::object object;

group test_capigeossimplify_group("capi::GEOSSimplify");

//
// Test Cases
//

// Test GEOSSimplify
template<>
template<>
void object::test<1>
()
{
    geom1_ = GEOSGeomFromWKT("POLYGON EMPTY");

    ensure(0 != GEOSisEmpty(geom1_));

    geom2_ = GEOSSimplify(geom1_, 43.2);

    ensure(0 != GEOSisEmpty(geom2_));
}

} // namespace tut

