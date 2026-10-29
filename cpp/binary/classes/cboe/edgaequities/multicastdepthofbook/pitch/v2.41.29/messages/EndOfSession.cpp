#include "EndOfSession.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

EndOfSession::EndOfSession(std::uint32_t last_timestamp)
  : last_timestamp_(last_timestamp) {}

std::uint32_t EndOfSession::last_timestamp() const { return last_timestamp_; }
void EndOfSession::set_last_timestamp(std::uint32_t value) { last_timestamp_ = value; }

MessageCode EndOfSession::type() const { return message_type; }

std::string_view EndOfSession::name() const { return "End Of Session"; }

std::size_t EndOfSession::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EndOfSession", wire_size, length);

    last_timestamp_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t EndOfSession::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EndOfSession", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(last_timestamp_));
    offset += 4;

    return offset;
}

std::size_t EndOfSession::encoded_size() const {
    return wire_size;
}

void EndOfSession::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> EndOfSession::clone() const {
    return std::make_unique<EndOfSession>(*this);
}

void EndOfSession::print(std::ostream& out) const {
    out << "EndOfSession{";
    out << "last_timestamp=";
    out << last_timestamp_;
    out << '}';
}

bool EndOfSession::equals(const Message& other) const {
    const auto* that = dynamic_cast<const EndOfSession*>(&other);
    return that != nullptr && *this == *that;
}

bool EndOfSession::operator==(const EndOfSession& other) const {
    return last_timestamp_ == other.last_timestamp_;
}

bool EndOfSession::operator!=(const EndOfSession& other) const {
    return !(*this == other);
}

} // namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29
