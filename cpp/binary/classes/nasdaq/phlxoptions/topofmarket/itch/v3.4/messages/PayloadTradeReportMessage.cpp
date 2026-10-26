#include "PayloadTradeReportMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

PayloadTradeReportMessage::PayloadTradeReportMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t option_id, std::uint32_t cross_id, char trade_condition, Decimal price_4, std::uint32_t volume)
  : nanoseconds_(nanoseconds), option_id_(option_id), cross_id_(cross_id), trade_condition_(trade_condition), price_4_(price_4), volume_(volume) {}

std::chrono::nanoseconds PayloadTradeReportMessage::nanoseconds() const { return nanoseconds_; }
void PayloadTradeReportMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t PayloadTradeReportMessage::option_id() const { return option_id_; }
void PayloadTradeReportMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

std::uint32_t PayloadTradeReportMessage::cross_id() const { return cross_id_; }
void PayloadTradeReportMessage::set_cross_id(std::uint32_t value) { cross_id_ = value; }

char PayloadTradeReportMessage::trade_condition() const { return trade_condition_; }
void PayloadTradeReportMessage::set_trade_condition(char value) { trade_condition_ = value; }

Decimal PayloadTradeReportMessage::price_4() const { return price_4_; }
void PayloadTradeReportMessage::set_price_4(Decimal value) { price_4_ = value; }

std::uint32_t PayloadTradeReportMessage::volume() const { return volume_; }
void PayloadTradeReportMessage::set_volume(std::uint32_t value) { volume_ = value; }

PacketMessageCode PayloadTradeReportMessage::type() const { return message_type; }

std::string_view PayloadTradeReportMessage::name() const { return "Trade Report Message"; }

std::size_t PayloadTradeReportMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadTradeReportMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    cross_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    trade_condition_ = wire::read_char(data + offset);
    offset += 1;

    price_4_ = Decimal(static_cast<std::int64_t>(wire::read_i32_be(data + offset)), -4);
    offset += 4;

    volume_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t PayloadTradeReportMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadTradeReportMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(cross_id_));
    offset += 4;

    wire::write_char(data + offset, trade_condition_);
    offset += 1;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(price_4_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(volume_));
    offset += 4;

    return offset;
}

std::size_t PayloadTradeReportMessage::encoded_size() const {
    return wire_size;
}

void PayloadTradeReportMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadTradeReportMessage::clone() const {
    return std::make_unique<PayloadTradeReportMessage>(*this);
}

void PayloadTradeReportMessage::print(std::ostream& out) const {
    out << "PayloadTradeReportMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", option_id=";
    out << option_id_;
    out << ", cross_id=";
    out << cross_id_;
    out << ", trade_condition=";
    print::character(out, trade_condition_);
    out << ", price_4=";
    out << price_4_;
    out << ", volume=";
    out << volume_;
    out << '}';
}

bool PayloadTradeReportMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadTradeReportMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadTradeReportMessage::operator==(const PayloadTradeReportMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && option_id_ == other.option_id_
        && cross_id_ == other.cross_id_
        && trade_condition_ == other.trade_condition_
        && price_4_ == other.price_4_
        && volume_ == other.volume_;
}

bool PayloadTradeReportMessage::operator!=(const PayloadTradeReportMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
