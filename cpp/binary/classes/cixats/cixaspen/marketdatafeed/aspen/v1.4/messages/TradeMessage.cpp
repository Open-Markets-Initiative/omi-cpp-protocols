#include "TradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

TradeMessage::TradeMessage(std::uint16_t symbol_id, std::chrono::nanoseconds timestamp, std::uint64_t reserved_8, Side side, Decimal shares, const std::string& symbol, Decimal price, std::uint64_t execution_id, const std::string& broker, const std::string& contra_broker)
  : symbol_id_(symbol_id), timestamp_(timestamp), reserved_8_(reserved_8), side_(side), shares_(shares), symbol_(symbol), price_(price), execution_id_(execution_id), broker_(broker), contra_broker_(contra_broker) {}

std::uint16_t TradeMessage::symbol_id() const { return symbol_id_; }
void TradeMessage::set_symbol_id(std::uint16_t value) { symbol_id_ = value; }

std::chrono::nanoseconds TradeMessage::timestamp() const { return timestamp_; }
void TradeMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t TradeMessage::reserved_8() const { return reserved_8_; }
void TradeMessage::set_reserved_8(std::uint64_t value) { reserved_8_ = value; }

Side TradeMessage::side() const { return side_; }
void TradeMessage::set_side(Side value) { side_ = value; }

Decimal TradeMessage::shares() const { return shares_; }
void TradeMessage::set_shares(Decimal value) { shares_ = value; }

const std::string& TradeMessage::symbol() const { return symbol_; }
std::string& TradeMessage::symbol() { return symbol_; }
void TradeMessage::set_symbol(const std::string& value) { symbol_ = value; }

Decimal TradeMessage::price() const { return price_; }
void TradeMessage::set_price(Decimal value) { price_ = value; }

std::uint64_t TradeMessage::execution_id() const { return execution_id_; }
void TradeMessage::set_execution_id(std::uint64_t value) { execution_id_ = value; }

const std::string& TradeMessage::broker() const { return broker_; }
std::string& TradeMessage::broker() { return broker_; }
void TradeMessage::set_broker(const std::string& value) { broker_ = value; }

const std::string& TradeMessage::contra_broker() const { return contra_broker_; }
std::string& TradeMessage::contra_broker() { return contra_broker_; }
void TradeMessage::set_contra_broker(const std::string& value) { contra_broker_ = value; }

MessageCode TradeMessage::type() const { return message_type; }

std::string_view TradeMessage::name() const { return "Trade Message"; }

std::size_t TradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeMessage", wire_size, length);

    symbol_id_ = wire::read_u16_le(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    reserved_8_ = wire::read_u64_le(data + offset);
    offset += 8;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    shares_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -6);
    offset += 8;

    symbol_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -6);
    offset += 8;

    execution_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    broker_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    contra_broker_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    return offset;
}

std::size_t TradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeMessage", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(symbol_id_));
    offset += 2;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(reserved_8_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(shares_.mantissa()));
    offset += 8;

    wire::write_text(data + offset, 11, ' ', symbol_);
    offset += 11;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(execution_id_));
    offset += 8;

    wire::write_text(data + offset, 3, ' ', broker_);
    offset += 3;

    wire::write_text(data + offset, 3, ' ', contra_broker_);
    offset += 3;

    return offset;
}

std::size_t TradeMessage::encoded_size() const {
    return wire_size;
}

void TradeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeMessage::clone() const {
    return std::make_unique<TradeMessage>(*this);
}

void TradeMessage::print(std::ostream& out) const {
    out << "TradeMessage{";
    out << "symbol_id=";
    out << symbol_id_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", reserved_8=";
    out << reserved_8_;
    out << ", side=";
    out << side_;
    out << ", shares=";
    out << shares_;
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", price=";
    out << price_;
    out << ", execution_id=";
    out << execution_id_;
    out << ", broker=";
    print::text(out, broker_);
    out << ", contra_broker=";
    print::text(out, contra_broker_);
    out << '}';
}

bool TradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeMessage::operator==(const TradeMessage& other) const {
    return symbol_id_ == other.symbol_id_
        && timestamp_ == other.timestamp_
        && reserved_8_ == other.reserved_8_
        && side_ == other.side_
        && shares_ == other.shares_
        && symbol_ == other.symbol_
        && price_ == other.price_
        && execution_id_ == other.execution_id_
        && broker_ == other.broker_
        && contra_broker_ == other.contra_broker_;
}

bool TradeMessage::operator!=(const TradeMessage& other) const {
    return !(*this == other);
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
