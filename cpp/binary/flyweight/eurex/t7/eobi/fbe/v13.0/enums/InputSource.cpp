#include "InputSource.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

std::string_view to_string(InputSource value) {
    switch (value) {
        case InputSource::ClipClientBroker: return "Clip Client Broker";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, InputSource value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v13_0
