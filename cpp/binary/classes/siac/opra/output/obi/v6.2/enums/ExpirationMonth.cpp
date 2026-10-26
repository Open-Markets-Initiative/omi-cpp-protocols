#include "ExpirationMonth.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(ExpirationMonth value) {
    switch (value) {
        case ExpirationMonth::JanuaryCall: return "January Call";
        case ExpirationMonth::JanuaryPut: return "January Put";
        case ExpirationMonth::FebruaryCall: return "February Call";
        case ExpirationMonth::FebruaryPut: return "February Put";
        case ExpirationMonth::MarchCall: return "March Call";
        case ExpirationMonth::MarchPut: return "March Put";
        case ExpirationMonth::AprilCall: return "April Call";
        case ExpirationMonth::AprilPut: return "April Put";
        case ExpirationMonth::MayCall: return "May Call";
        case ExpirationMonth::MayPut: return "May Put";
        case ExpirationMonth::JuneCall: return "June Call";
        case ExpirationMonth::JunePut: return "June Put";
        case ExpirationMonth::JulyCall: return "July Call";
        case ExpirationMonth::JulyPut: return "July Put";
        case ExpirationMonth::AugustCall: return "August Call";
        case ExpirationMonth::AugustPut: return "August Put";
        case ExpirationMonth::SeptemberCall: return "September Call";
        case ExpirationMonth::SeptemberPut: return "September Put";
        case ExpirationMonth::OctoberCall: return "October Call";
        case ExpirationMonth::OctoberPut: return "October Put";
        case ExpirationMonth::NovemberCall: return "November Call";
        case ExpirationMonth::NovemberPut: return "November Put";
        case ExpirationMonth::DecemberCall: return "December Call";
        case ExpirationMonth::DecemberPut: return "December Put";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ExpirationMonth value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
