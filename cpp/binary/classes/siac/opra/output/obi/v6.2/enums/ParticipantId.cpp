#include "ParticipantId.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(ParticipantId value) {
    switch (value) {
        case ParticipantId::Amex: return "Amex";
        case ParticipantId::Box: return "Box";
        case ParticipantId::Cboe: return "Cboe";
        case ParticipantId::Emerald: return "Emerald";
        case ParticipantId::Edgx: return "Edgx";
        case ParticipantId::Gemx: return "Gemx";
        case ParticipantId::Ise: return "Ise";
        case ParticipantId::Mrx: return "Mrx";
        case ParticipantId::Miax: return "Miax";
        case ParticipantId::Nyse: return "Nyse";
        case ParticipantId::Opra: return "Opra";
        case ParticipantId::Pearl: return "Pearl";
        case ParticipantId::Nasd: return "Nasd";
        case ParticipantId::Sphr: return "Sphr";
        case ParticipantId::Bx: return "Bx";
        case ParticipantId::Memx: return "Memx";
        case ParticipantId::C2: return "C 2";
        case ParticipantId::Phlx: return "Phlx";
        case ParticipantId::Bats: return "Bats";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ParticipantId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
