#pragma once

#include <cstddef>
#include "../types/Year.hpp"
#include "../types/Month.hpp"
#include "../types/Day.hpp"
#include "../types/Week.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_8;

#pragma pack(push, 1)

struct contract_settl_month {

    sbe_binaryumdf::year year;
    sbe_binaryumdf::month month;
    sbe_binaryumdf::day day;
    sbe_binaryumdf::week week;

    // parse method
    static contract_settl_month* parse(std::byte* buffer) {
        return reinterpret_cast<contract_settl_month*>(buffer);
    }

    // parse method const
    static const contract_settl_month* parse(const std::byte* buffer) {
        return reinterpret_cast<const contract_settl_month*>(buffer);
    }
};

// layout verification
static_assert(offsetof(contract_settl_month, year) == 0, "unexpected offset of contract_settl_month::year");
static_assert(offsetof(contract_settl_month, month) == 2, "unexpected offset of contract_settl_month::month");
static_assert(offsetof(contract_settl_month, day) == 3, "unexpected offset of contract_settl_month::day");
static_assert(offsetof(contract_settl_month, week) == 4, "unexpected offset of contract_settl_month::week");
static_assert(sizeof(contract_settl_month) == 5, "unexpected sizeof contract_settl_month");

#pragma pack(pop)
}
