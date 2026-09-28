#pragma once

#include "../types/Year.hpp"
#include "../types/Month.hpp"
#include "../types/Day.hpp"
#include "../types/Week.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

#pragma pack(push, 1)

struct ContractSettlMonth {

    Year year;
    Month month;
    Day day;
    Week week;

    // parse method
    static ContractSettlMonth* parse(std::byte* buffer) {
        return reinterpret_cast<ContractSettlMonth*>(buffer);
    }

    // parse method const
    static const ContractSettlMonth* parse(const std::byte* buffer) {
        return reinterpret_cast<const ContractSettlMonth*>(buffer);
    }
};

#pragma pack(pop)
}
