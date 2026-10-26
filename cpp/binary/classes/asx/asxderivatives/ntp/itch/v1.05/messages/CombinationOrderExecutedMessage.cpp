#include "CombinationOrderExecutedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

CombinationOrderExecutedMessage::CombinationOrderExecutedMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, Side side, std::uint64_t order_id, std::uint32_t quantity_remaining, TradeType trade_type, std::uint64_t trade_id, std::uint32_t executed_quantity, Decimal trade_price, std::uint32_t opposite_tradeable_instrument_id, OppositeSide opposite_side, std::uint64_t opposite_order_id, std::uint64_t combination_trade_id)
  : nanoseconds_(nanoseconds), trade_date_(trade_date), tradeable_instrument_id_(tradeable_instrument_id), side_(side), order_id_(order_id), quantity_remaining_(quantity_remaining), trade_type_(trade_type), trade_id_(trade_id), executed_quantity_(executed_quantity), trade_price_(trade_price), opposite_tradeable_instrument_id_(opposite_tradeable_instrument_id), opposite_side_(opposite_side), opposite_order_id_(opposite_order_id), combination_trade_id_(combination_trade_id) {}

std::chrono::nanoseconds CombinationOrderExecutedMessage::nanoseconds() const { return nanoseconds_; }
void CombinationOrderExecutedMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint16_t CombinationOrderExecutedMessage::trade_date() const { return trade_date_; }
void CombinationOrderExecutedMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::uint32_t CombinationOrderExecutedMessage::tradeable_instrument_id() const { return tradeable_instrument_id_; }
void CombinationOrderExecutedMessage::set_tradeable_instrument_id(std::uint32_t value) { tradeable_instrument_id_ = value; }

Side CombinationOrderExecutedMessage::side() const { return side_; }
void CombinationOrderExecutedMessage::set_side(Side value) { side_ = value; }

std::uint64_t CombinationOrderExecutedMessage::order_id() const { return order_id_; }
void CombinationOrderExecutedMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t CombinationOrderExecutedMessage::quantity_remaining() const { return quantity_remaining_; }
void CombinationOrderExecutedMessage::set_quantity_remaining(std::uint32_t value) { quantity_remaining_ = value; }

TradeType CombinationOrderExecutedMessage::trade_type() const { return trade_type_; }
void CombinationOrderExecutedMessage::set_trade_type(TradeType value) { trade_type_ = value; }

std::uint64_t CombinationOrderExecutedMessage::trade_id() const { return trade_id_; }
void CombinationOrderExecutedMessage::set_trade_id(std::uint64_t value) { trade_id_ = value; }

std::uint32_t CombinationOrderExecutedMessage::executed_quantity() const { return executed_quantity_; }
void CombinationOrderExecutedMessage::set_executed_quantity(std::uint32_t value) { executed_quantity_ = value; }

Decimal CombinationOrderExecutedMessage::trade_price() const { return trade_price_; }
void CombinationOrderExecutedMessage::set_trade_price(Decimal value) { trade_price_ = value; }

std::uint32_t CombinationOrderExecutedMessage::opposite_tradeable_instrument_id() const { return opposite_tradeable_instrument_id_; }
void CombinationOrderExecutedMessage::set_opposite_tradeable_instrument_id(std::uint32_t value) { opposite_tradeable_instrument_id_ = value; }

OppositeSide CombinationOrderExecutedMessage::opposite_side() const { return opposite_side_; }
void CombinationOrderExecutedMessage::set_opposite_side(OppositeSide value) { opposite_side_ = value; }

std::uint64_t CombinationOrderExecutedMessage::opposite_order_id() const { return opposite_order_id_; }
void CombinationOrderExecutedMessage::set_opposite_order_id(std::uint64_t value) { opposite_order_id_ = value; }

std::uint64_t CombinationOrderExecutedMessage::combination_trade_id() const { return combination_trade_id_; }
void CombinationOrderExecutedMessage::set_combination_trade_id(std::uint64_t value) { combination_trade_id_ = value; }

MessageCode CombinationOrderExecutedMessage::type() const { return message_type; }

std::string_view CombinationOrderExecutedMessage::name() const { return "Combination Order Executed Message"; }

std::size_t CombinationOrderExecutedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CombinationOrderExecutedMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    trade_date_ = wire::read_u16_be(data + offset);
    offset += 2;

    tradeable_instrument_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    order_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    quantity_remaining_ = wire::read_u32_be(data + offset);
    offset += 4;

    trade_type_ = static_cast<TradeType>(wire::read_char(data + offset));
    offset += 1;

    trade_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    executed_quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
    offset += 8;

    opposite_tradeable_instrument_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    opposite_side_ = static_cast<OppositeSide>(wire::read_char(data + offset));
    offset += 1;

    opposite_order_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    combination_trade_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t CombinationOrderExecutedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CombinationOrderExecutedMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(tradeable_instrument_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quantity_remaining_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(trade_type_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(trade_id_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(executed_quantity_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(trade_price_.mantissa()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(opposite_tradeable_instrument_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(opposite_side_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(opposite_order_id_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(combination_trade_id_));
    offset += 8;

    return offset;
}

std::size_t CombinationOrderExecutedMessage::encoded_size() const {
    return wire_size;
}

void CombinationOrderExecutedMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> CombinationOrderExecutedMessage::clone() const {
    return std::make_unique<CombinationOrderExecutedMessage>(*this);
}

void CombinationOrderExecutedMessage::print(std::ostream& out) const {
    out << "CombinationOrderExecutedMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", trade_date=";
    out << trade_date_;
    out << ", tradeable_instrument_id=";
    out << tradeable_instrument_id_;
    out << ", side=";
    out << side_;
    out << ", order_id=";
    out << order_id_;
    out << ", quantity_remaining=";
    out << quantity_remaining_;
    out << ", trade_type=";
    out << trade_type_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", executed_quantity=";
    out << executed_quantity_;
    out << ", trade_price=";
    out << trade_price_;
    out << ", opposite_tradeable_instrument_id=";
    out << opposite_tradeable_instrument_id_;
    out << ", opposite_side=";
    out << opposite_side_;
    out << ", opposite_order_id=";
    out << opposite_order_id_;
    out << ", combination_trade_id=";
    out << combination_trade_id_;
    out << '}';
}

bool CombinationOrderExecutedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const CombinationOrderExecutedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool CombinationOrderExecutedMessage::operator==(const CombinationOrderExecutedMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && trade_date_ == other.trade_date_
        && tradeable_instrument_id_ == other.tradeable_instrument_id_
        && side_ == other.side_
        && order_id_ == other.order_id_
        && quantity_remaining_ == other.quantity_remaining_
        && trade_type_ == other.trade_type_
        && trade_id_ == other.trade_id_
        && executed_quantity_ == other.executed_quantity_
        && trade_price_ == other.trade_price_
        && opposite_tradeable_instrument_id_ == other.opposite_tradeable_instrument_id_
        && opposite_side_ == other.opposite_side_
        && opposite_order_id_ == other.opposite_order_id_
        && combination_trade_id_ == other.combination_trade_id_;
}

bool CombinationOrderExecutedMessage::operator!=(const CombinationOrderExecutedMessage& other) const {
    return !(*this == other);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
