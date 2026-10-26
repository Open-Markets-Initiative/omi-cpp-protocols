#include "MdReqIdStatus.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

std::string_view to_string(MdReqIdStatus value) {
    switch (value) {
        case MdReqIdStatus::FullAck: return "Full Ack";
        case MdReqIdStatus::PartialAck: return "Partial Ack";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MdReqIdStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_13
