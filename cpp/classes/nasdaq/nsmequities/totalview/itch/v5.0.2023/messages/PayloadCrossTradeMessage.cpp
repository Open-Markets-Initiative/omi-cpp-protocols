#include "PayloadCrossTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

PayloadCrossTradeMessage::PayloadCrossTradeMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t cross_shares, const std::string& stock, Decimal cross_price, std::uint64_t match_number, CrossType cross_type)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), cross_shares_(cross_shares), stock_(stock), cross_price_(cross_price), match_number_(match_number), cross_type_(cross_type) {}

std::uint16_t PayloadCrossTradeMessage::stock_locate() const { return stock_locate_; }
void PayloadCrossTradeMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t PayloadCrossTradeMessage::tracking_number() const { return tracking_number_; }
void PayloadCrossTradeMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds PayloadCrossTradeMessage::timestamp() const { return timestamp_; }
void PayloadCrossTradeMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t PayloadCrossTradeMessage::cross_shares() const { return cross_shares_; }
void PayloadCrossTradeMessage::set_cross_shares(std::uint64_t value) { cross_shares_ = value; }

const std::string& PayloadCrossTradeMessage::stock() const { return stock_; }
std::string& PayloadCrossTradeMessage::stock() { return stock_; }
void PayloadCrossTradeMessage::set_stock(const std::string& value) { stock_ = value; }

Decimal PayloadCrossTradeMessage::cross_price() const { return cross_price_; }
void PayloadCrossTradeMessage::set_cross_price(Decimal value) { cross_price_ = value; }

std::uint64_t PayloadCrossTradeMessage::match_number() const { return match_number_; }
void PayloadCrossTradeMessage::set_match_number(std::uint64_t value) { match_number_ = value; }

CrossType PayloadCrossTradeMessage::cross_type() const { return cross_type_; }
void PayloadCrossTradeMessage::set_cross_type(CrossType value) { cross_type_ = value; }

PacketMessageCode PayloadCrossTradeMessage::type() const { return message_type; }

std::string_view PayloadCrossTradeMessage::name() const { return "Cross Trade Message"; }

std::size_t PayloadCrossTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadCrossTradeMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    cross_shares_ = wire::read_u64_be(data + offset);
    offset += 8;

    stock_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    cross_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    match_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    cross_type_ = static_cast<CrossType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t PayloadCrossTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadCrossTradeMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(cross_shares_));
    offset += 8;

    wire::write_text(data + offset, 8, ' ', stock_);
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(cross_price_.mantissa()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(match_number_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(cross_type_));
    offset += 1;

    return offset;
}

std::size_t PayloadCrossTradeMessage::encoded_size() const {
    return wire_size;
}

void PayloadCrossTradeMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadCrossTradeMessage::clone() const {
    return std::make_unique<PayloadCrossTradeMessage>(*this);
}

void PayloadCrossTradeMessage::print(std::ostream& out) const {
    out << "PayloadCrossTradeMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", cross_shares=";
    out << cross_shares_;
    out << ", stock=";
    print::text(out, stock_);
    out << ", cross_price=";
    out << cross_price_;
    out << ", match_number=";
    out << match_number_;
    out << ", cross_type=";
    out << cross_type_;
    out << '}';
}

bool PayloadCrossTradeMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadCrossTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadCrossTradeMessage::operator==(const PayloadCrossTradeMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && cross_shares_ == other.cross_shares_
        && stock_ == other.stock_
        && cross_price_ == other.cross_price_
        && match_number_ == other.match_number_
        && cross_type_ == other.cross_type_;
}

bool PayloadCrossTradeMessage::operator!=(const PayloadCrossTradeMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
