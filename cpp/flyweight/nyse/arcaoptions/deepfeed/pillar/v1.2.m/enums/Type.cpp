#include "Type.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

std::string_view to_string(Type value) {
    switch (value) {
        case Type::BoldOutrightOnly: return "Bold Outright Only";
        case Type::CoaComplexOnly: return "Coa Complex Only";
        case Type::FlexPriceImprovementCube: return "Flex Price Improvement Cube";
        case Type::FlexAonSolicitationCube: return "Flex Aon Solicitation Cube";
        case Type::PriceImprovementCube: return "Price Improvement Cube";
        case Type::AonSolicitationCube: return "Aon Solicitation Cube";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Type value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
