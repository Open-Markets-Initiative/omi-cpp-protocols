#include "PayloadBrokenTradeReportMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

PayloadBrokenTradeReportMessage::PayloadBrokenTradeReportMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t option_id, std::uint32_t original_cross_id, Decimal original_price, std::uint32_t original_volume)
  : nanoseconds_(nanoseconds), option_id_(option_id), original_cross_id_(original_cross_id), original_price_(original_price), original_volume_(original_volume) {}

std::chrono::nanoseconds PayloadBrokenTradeReportMessage::nanoseconds() const { return nanoseconds_; }
void PayloadBrokenTradeReportMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t PayloadBrokenTradeReportMessage::option_id() const { return option_id_; }
void PayloadBrokenTradeReportMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

std::uint32_t PayloadBrokenTradeReportMessage::original_cross_id() const { return original_cross_id_; }
void PayloadBrokenTradeReportMessage::set_original_cross_id(std::uint32_t value) { original_cross_id_ = value; }

Decimal PayloadBrokenTradeReportMessage::original_price() const { return original_price_; }
void PayloadBrokenTradeReportMessage::set_original_price(Decimal value) { original_price_ = value; }

std::uint32_t PayloadBrokenTradeReportMessage::original_volume() const { return original_volume_; }
void PayloadBrokenTradeReportMessage::set_original_volume(std::uint32_t value) { original_volume_ = value; }

PacketMessageCode PayloadBrokenTradeReportMessage::type() const { return message_type; }

std::string_view PayloadBrokenTradeReportMessage::name() const { return "Broken Trade Report Message"; }

std::size_t PayloadBrokenTradeReportMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadBrokenTradeReportMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    original_cross_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    original_price_ = Decimal(static_cast<std::int64_t>(wire::read_i32_be(data + offset)), -4);
    offset += 4;

    original_volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t PayloadBrokenTradeReportMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadBrokenTradeReportMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(original_cross_id_));
    offset += 4;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(original_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(original_volume_));
    offset += 4;

    return offset;
}

std::size_t PayloadBrokenTradeReportMessage::encoded_size() const {
    return wire_size;
}

void PayloadBrokenTradeReportMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadBrokenTradeReportMessage::clone() const {
    return std::make_unique<PayloadBrokenTradeReportMessage>(*this);
}

void PayloadBrokenTradeReportMessage::print(std::ostream& out) const {
    out << "PayloadBrokenTradeReportMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", option_id=";
    out << option_id_;
    out << ", original_cross_id=";
    out << original_cross_id_;
    out << ", original_price=";
    out << original_price_;
    out << ", original_volume=";
    out << original_volume_;
    out << '}';
}

bool PayloadBrokenTradeReportMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadBrokenTradeReportMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadBrokenTradeReportMessage::operator==(const PayloadBrokenTradeReportMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && option_id_ == other.option_id_
        && original_cross_id_ == other.original_cross_id_
        && original_price_ == other.original_price_
        && original_volume_ == other.original_volume_;
}

bool PayloadBrokenTradeReportMessage::operator!=(const PayloadBrokenTradeReportMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
