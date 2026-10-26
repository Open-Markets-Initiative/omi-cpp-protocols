#pragma once

#include <cstddef>
#include "../types/Year.hpp"
#include "../types/Month.hpp"
#include "../types/Day.hpp"
#include "../types/Week.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_3;

#pragma pack(push, 1)

struct maturity_month_year {

    sbe_binaryumdf::year year;
    sbe_binaryumdf::month month;
    sbe_binaryumdf::day day;
    sbe_binaryumdf::week week;

    // parse method
    static maturity_month_year* parse(std::byte* buffer) {
        return reinterpret_cast<maturity_month_year*>(buffer);
    }

    // parse method const
    static const maturity_month_year* parse(const std::byte* buffer) {
        return reinterpret_cast<const maturity_month_year*>(buffer);
    }
};

// layout verification
static_assert(offsetof(maturity_month_year, year) == 0, "unexpected offset of maturity_month_year::year");
static_assert(offsetof(maturity_month_year, month) == 2, "unexpected offset of maturity_month_year::month");
static_assert(offsetof(maturity_month_year, day) == 3, "unexpected offset of maturity_month_year::day");
static_assert(offsetof(maturity_month_year, week) == 4, "unexpected offset of maturity_month_year::week");
static_assert(sizeof(maturity_month_year) == 5, "unexpected sizeof maturity_month_year");

#pragma pack(pop)
}
