#include "PacketType.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

std::string_view to_string(PacketType value) {
    switch (value) {
        case PacketType::LoginRequestMessage: return "Login Request Message";
        case PacketType::LoginResultMessage: return "Login Result Message";
        case PacketType::MessageResponseMessage: return "Message Response Message";
        case PacketType::EndOfMessageMessage: return "End Of Message Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PacketType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
