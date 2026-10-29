#include "MarketDataControlMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

MarketDataControlMessage::MarketDataControlMessage(MdControlType md_control_type)
  : md_control_type_(md_control_type) {}

MdControlType MarketDataControlMessage::md_control_type() const { return md_control_type_; }
void MarketDataControlMessage::set_md_control_type(MdControlType value) { md_control_type_ = value; }

MessageCode MarketDataControlMessage::type() const { return message_type; }

std::string_view MarketDataControlMessage::name() const { return "Market Data Control Message"; }

std::size_t MarketDataControlMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MarketDataControlMessage", wire_size, length);

    md_control_type_ = static_cast<MdControlType>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t MarketDataControlMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MarketDataControlMessage", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_control_type_));
    offset += 1;

    return offset;
}

std::size_t MarketDataControlMessage::encoded_size() const {
    return wire_size;
}

void MarketDataControlMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> MarketDataControlMessage::clone() const {
    return std::make_unique<MarketDataControlMessage>(*this);
}

void MarketDataControlMessage::print(std::ostream& out) const {
    out << "MarketDataControlMessage{";
    out << "md_control_type=";
    out << md_control_type_;
    out << '}';
}

bool MarketDataControlMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const MarketDataControlMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MarketDataControlMessage::operator==(const MarketDataControlMessage& other) const {
    return md_control_type_ == other.md_control_type_;
}

bool MarketDataControlMessage::operator!=(const MarketDataControlMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
