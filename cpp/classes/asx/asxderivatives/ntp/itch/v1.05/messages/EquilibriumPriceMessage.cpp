#include "EquilibriumPriceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

EquilibriumPriceMessage::EquilibriumPriceMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, Decimal equilibrium_price, std::uint64_t matched_quantity, std::uint64_t bid_quantity, std::uint64_t ask_quantity)
  : nanoseconds_(nanoseconds), trade_date_(trade_date), tradeable_instrument_id_(tradeable_instrument_id), equilibrium_price_(equilibrium_price), matched_quantity_(matched_quantity), bid_quantity_(bid_quantity), ask_quantity_(ask_quantity) {}

std::chrono::nanoseconds EquilibriumPriceMessage::nanoseconds() const { return nanoseconds_; }
void EquilibriumPriceMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint16_t EquilibriumPriceMessage::trade_date() const { return trade_date_; }
void EquilibriumPriceMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::uint32_t EquilibriumPriceMessage::tradeable_instrument_id() const { return tradeable_instrument_id_; }
void EquilibriumPriceMessage::set_tradeable_instrument_id(std::uint32_t value) { tradeable_instrument_id_ = value; }

Decimal EquilibriumPriceMessage::equilibrium_price() const { return equilibrium_price_; }
void EquilibriumPriceMessage::set_equilibrium_price(Decimal value) { equilibrium_price_ = value; }

std::uint64_t EquilibriumPriceMessage::matched_quantity() const { return matched_quantity_; }
void EquilibriumPriceMessage::set_matched_quantity(std::uint64_t value) { matched_quantity_ = value; }

std::uint64_t EquilibriumPriceMessage::bid_quantity() const { return bid_quantity_; }
void EquilibriumPriceMessage::set_bid_quantity(std::uint64_t value) { bid_quantity_ = value; }

std::uint64_t EquilibriumPriceMessage::ask_quantity() const { return ask_quantity_; }
void EquilibriumPriceMessage::set_ask_quantity(std::uint64_t value) { ask_quantity_ = value; }

MessageCode EquilibriumPriceMessage::type() const { return message_type; }

std::string_view EquilibriumPriceMessage::name() const { return "Equilibrium Price Message"; }

std::size_t EquilibriumPriceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EquilibriumPriceMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    trade_date_ = wire::read_u16_be(data + offset);
    offset += 2;

    tradeable_instrument_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    equilibrium_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
    offset += 8;

    matched_quantity_ = wire::read_u64_be(data + offset);
    offset += 8;

    bid_quantity_ = wire::read_u64_be(data + offset);
    offset += 8;

    ask_quantity_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t EquilibriumPriceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EquilibriumPriceMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(tradeable_instrument_id_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(equilibrium_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(matched_quantity_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(bid_quantity_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(ask_quantity_));
    offset += 8;

    return offset;
}

std::size_t EquilibriumPriceMessage::encoded_size() const {
    return wire_size;
}

void EquilibriumPriceMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> EquilibriumPriceMessage::clone() const {
    return std::make_unique<EquilibriumPriceMessage>(*this);
}

void EquilibriumPriceMessage::print(std::ostream& out) const {
    out << "EquilibriumPriceMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", trade_date=";
    out << trade_date_;
    out << ", tradeable_instrument_id=";
    out << tradeable_instrument_id_;
    out << ", equilibrium_price=";
    out << equilibrium_price_;
    out << ", matched_quantity=";
    out << matched_quantity_;
    out << ", bid_quantity=";
    out << bid_quantity_;
    out << ", ask_quantity=";
    out << ask_quantity_;
    out << '}';
}

bool EquilibriumPriceMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const EquilibriumPriceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool EquilibriumPriceMessage::operator==(const EquilibriumPriceMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && trade_date_ == other.trade_date_
        && tradeable_instrument_id_ == other.tradeable_instrument_id_
        && equilibrium_price_ == other.equilibrium_price_
        && matched_quantity_ == other.matched_quantity_
        && bid_quantity_ == other.bid_quantity_
        && ask_quantity_ == other.ask_quantity_;
}

bool EquilibriumPriceMessage::operator!=(const EquilibriumPriceMessage& other) const {
    return !(*this == other);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
