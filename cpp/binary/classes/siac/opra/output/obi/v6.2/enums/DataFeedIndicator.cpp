#include "DataFeedIndicator.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(DataFeedIndicator value) {
    switch (value) {
        case DataFeedIndicator::Opra: return "Opra";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, DataFeedIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
