#include "MwcbStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

MwcbStatusMessage::MwcbStatusMessage(BreachedLevel breached_level)
  : breached_level_(breached_level) {}

BreachedLevel MwcbStatusMessage::breached_level() const { return breached_level_; }
void MwcbStatusMessage::set_breached_level(BreachedLevel value) { breached_level_ = value; }

MessageCode MwcbStatusMessage::type() const { return message_type; }

std::string_view MwcbStatusMessage::name() const { return "Mwcb Status Message"; }

std::size_t MwcbStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MwcbStatusMessage", wire_size, length);

    breached_level_ = static_cast<BreachedLevel>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t MwcbStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MwcbStatusMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(breached_level_));
    offset += 1;

    return offset;
}

std::size_t MwcbStatusMessage::encoded_size() const {
    return wire_size;
}

void MwcbStatusMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MwcbStatusMessage::clone() const {
    return std::make_unique<MwcbStatusMessage>(*this);
}

void MwcbStatusMessage::print(std::ostream& out) const {
    out << "MwcbStatusMessage{";
    out << "breached_level=";
    out << breached_level_;
    out << '}';
}

bool MwcbStatusMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MwcbStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MwcbStatusMessage::operator==(const MwcbStatusMessage& other) const {
    return breached_level_ == other.breached_level_;
}

bool MwcbStatusMessage::operator!=(const MwcbStatusMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
