#include "TradeReportMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

TradeReportMessage::TradeReportMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t option_id, std::uint32_t cross_id, char trade_condition, Decimal price_4, std::uint32_t volume)
  : nanoseconds_(nanoseconds), option_id_(option_id), cross_id_(cross_id), trade_condition_(trade_condition), price_4_(price_4), volume_(volume) {}

std::chrono::nanoseconds TradeReportMessage::nanoseconds() const { return nanoseconds_; }
void TradeReportMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t TradeReportMessage::option_id() const { return option_id_; }
void TradeReportMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

std::uint32_t TradeReportMessage::cross_id() const { return cross_id_; }
void TradeReportMessage::set_cross_id(std::uint32_t value) { cross_id_ = value; }

char TradeReportMessage::trade_condition() const { return trade_condition_; }
void TradeReportMessage::set_trade_condition(char value) { trade_condition_ = value; }

Decimal TradeReportMessage::price_4() const { return price_4_; }
void TradeReportMessage::set_price_4(Decimal value) { price_4_ = value; }

std::uint32_t TradeReportMessage::volume() const { return volume_; }
void TradeReportMessage::set_volume(std::uint32_t value) { volume_ = value; }

SequencedMessageCode TradeReportMessage::type() const { return message_type; }

std::string_view TradeReportMessage::name() const { return "Trade Report Message"; }

std::size_t TradeReportMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeReportMessage", wire_size, length);

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

std::size_t TradeReportMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeReportMessage", wire_size, capacity);

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

std::size_t TradeReportMessage::encoded_size() const {
    return wire_size;
}

void TradeReportMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> TradeReportMessage::clone() const {
    return std::make_unique<TradeReportMessage>(*this);
}

void TradeReportMessage::print(std::ostream& out) const {
    out << "TradeReportMessage{";
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

bool TradeReportMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const TradeReportMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeReportMessage::operator==(const TradeReportMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && option_id_ == other.option_id_
        && cross_id_ == other.cross_id_
        && trade_condition_ == other.trade_condition_
        && price_4_ == other.price_4_
        && volume_ == other.volume_;
}

bool TradeReportMessage::operator!=(const TradeReportMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
