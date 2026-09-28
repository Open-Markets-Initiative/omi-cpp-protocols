#include "PayloadBrokenTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

PayloadBrokenTradeMessage::PayloadBrokenTradeMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t match_number)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), match_number_(match_number) {}

std::uint16_t PayloadBrokenTradeMessage::stock_locate() const { return stock_locate_; }
void PayloadBrokenTradeMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t PayloadBrokenTradeMessage::tracking_number() const { return tracking_number_; }
void PayloadBrokenTradeMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds PayloadBrokenTradeMessage::timestamp() const { return timestamp_; }
void PayloadBrokenTradeMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t PayloadBrokenTradeMessage::match_number() const { return match_number_; }
void PayloadBrokenTradeMessage::set_match_number(std::uint64_t value) { match_number_ = value; }

PacketMessageCode PayloadBrokenTradeMessage::type() const { return message_type; }

std::string_view PayloadBrokenTradeMessage::name() const { return "Broken Trade Message"; }

std::size_t PayloadBrokenTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadBrokenTradeMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    match_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t PayloadBrokenTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadBrokenTradeMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(match_number_));
    offset += 8;

    return offset;
}

std::size_t PayloadBrokenTradeMessage::encoded_size() const {
    return wire_size;
}

void PayloadBrokenTradeMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadBrokenTradeMessage::clone() const {
    return std::make_unique<PayloadBrokenTradeMessage>(*this);
}

void PayloadBrokenTradeMessage::print(std::ostream& out) const {
    out << "PayloadBrokenTradeMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", match_number=";
    out << match_number_;
    out << '}';
}

bool PayloadBrokenTradeMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadBrokenTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadBrokenTradeMessage::operator==(const PayloadBrokenTradeMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && match_number_ == other.match_number_;
}

bool PayloadBrokenTradeMessage::operator!=(const PayloadBrokenTradeMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
