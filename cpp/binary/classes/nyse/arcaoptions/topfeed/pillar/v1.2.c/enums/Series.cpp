#include "Series.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

std::string_view to_string(Series value) {
    switch (value) {
        case Series::Cube: return "Cube";
        case Series::Occ: return "Occ";
        case Series::FloorTrade: return "Floor Trade";
        case Series::OtherOutrightSeries: return "Other Outright Series";
        case Series::IsoSweep: return "Iso Sweep";
        case Series::After90Seconds: return "After 90 Seconds";
        case Series::OtherComplexOrders: return "Other Complex Orders";
        case Series::ComplexCube: return "Complex Cube";
        case Series::ComplexQccOrder: return "Complex Qcc Order";
        case Series::ComplexFloorOrder: return "Complex Floor Order";
        case Series::ComplexOrderTradingWithTheOutrightSeries: return "Complex Order Trading With The Outright Series";
        case Series::ComplexOrderToOutrightSeriesOrderfloorTrade: return "Complex Order To Outright Series Orderfloor Trade";
        case Series::ComplexOrderWithStockToComplexOrderWithStockFloorTrade: return "Complex Order With Stock To Complex Order With Stock Floor Trade";
        case Series::ComplexOrderWithStockToOutrightSeriesOrderFloorTrade: return "Complex Order With Stock To Outright Series Order Floor Trade";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Series value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
