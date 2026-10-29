#include "TradeCorrectMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

TradeCorrectMessage::TradeCorrectMessage(std::uint16_t symbol_id, std::chrono::nanoseconds timestamp, std::uint64_t reserved_8, char reserved_1, const std::string& symbol, std::uint64_t execution_id, const std::string& broker, const std::string& contra_broker, std::uint64_t original_execution_id, Decimal original_trade_price, Decimal original_trade_quantity, Decimal corrected_trade_price, Decimal corrected_trade_quantity)
  : symbol_id_(symbol_id), timestamp_(timestamp), reserved_8_(reserved_8), reserved_1_(reserved_1), symbol_(symbol), execution_id_(execution_id), broker_(broker), contra_broker_(contra_broker), original_execution_id_(original_execution_id), original_trade_price_(original_trade_price), original_trade_quantity_(original_trade_quantity), corrected_trade_price_(corrected_trade_price), corrected_trade_quantity_(corrected_trade_quantity) {}

std::uint16_t TradeCorrectMessage::symbol_id() const { return symbol_id_; }
void TradeCorrectMessage::set_symbol_id(std::uint16_t value) { symbol_id_ = value; }

std::chrono::nanoseconds TradeCorrectMessage::timestamp() const { return timestamp_; }
void TradeCorrectMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t TradeCorrectMessage::reserved_8() const { return reserved_8_; }
void TradeCorrectMessage::set_reserved_8(std::uint64_t value) { reserved_8_ = value; }

char TradeCorrectMessage::reserved_1() const { return reserved_1_; }
void TradeCorrectMessage::set_reserved_1(char value) { reserved_1_ = value; }

const std::string& TradeCorrectMessage::symbol() const { return symbol_; }
std::string& TradeCorrectMessage::symbol() { return symbol_; }
void TradeCorrectMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::uint64_t TradeCorrectMessage::execution_id() const { return execution_id_; }
void TradeCorrectMessage::set_execution_id(std::uint64_t value) { execution_id_ = value; }

const std::string& TradeCorrectMessage::broker() const { return broker_; }
std::string& TradeCorrectMessage::broker() { return broker_; }
void TradeCorrectMessage::set_broker(const std::string& value) { broker_ = value; }

const std::string& TradeCorrectMessage::contra_broker() const { return contra_broker_; }
std::string& TradeCorrectMessage::contra_broker() { return contra_broker_; }
void TradeCorrectMessage::set_contra_broker(const std::string& value) { contra_broker_ = value; }

std::uint64_t TradeCorrectMessage::original_execution_id() const { return original_execution_id_; }
void TradeCorrectMessage::set_original_execution_id(std::uint64_t value) { original_execution_id_ = value; }

Decimal TradeCorrectMessage::original_trade_price() const { return original_trade_price_; }
void TradeCorrectMessage::set_original_trade_price(Decimal value) { original_trade_price_ = value; }

Decimal TradeCorrectMessage::original_trade_quantity() const { return original_trade_quantity_; }
void TradeCorrectMessage::set_original_trade_quantity(Decimal value) { original_trade_quantity_ = value; }

Decimal TradeCorrectMessage::corrected_trade_price() const { return corrected_trade_price_; }
void TradeCorrectMessage::set_corrected_trade_price(Decimal value) { corrected_trade_price_ = value; }

Decimal TradeCorrectMessage::corrected_trade_quantity() const { return corrected_trade_quantity_; }
void TradeCorrectMessage::set_corrected_trade_quantity(Decimal value) { corrected_trade_quantity_ = value; }

MessageCode TradeCorrectMessage::type() const { return message_type; }

std::string_view TradeCorrectMessage::name() const { return "Trade Correct Message"; }

std::size_t TradeCorrectMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeCorrectMessage", wire_size, length);

    symbol_id_ = wire::read_u16_le(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    reserved_8_ = wire::read_u64_le(data + offset);
    offset += 8;

    reserved_1_ = wire::read_char(data + offset);
    offset += 1;

    symbol_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    execution_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    broker_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    contra_broker_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    original_execution_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    original_trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -6);
    offset += 8;

    original_trade_quantity_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -6);
    offset += 8;

    corrected_trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -6);
    offset += 8;

    corrected_trade_quantity_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -6);
    offset += 8;

    return offset;
}

std::size_t TradeCorrectMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeCorrectMessage", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(symbol_id_));
    offset += 2;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(reserved_8_));
    offset += 8;

    wire::write_char(data + offset, reserved_1_);
    offset += 1;

    wire::write_text(data + offset, 11, ' ', symbol_);
    offset += 11;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(execution_id_));
    offset += 8;

    wire::write_text(data + offset, 3, ' ', broker_);
    offset += 3;

    wire::write_text(data + offset, 3, ' ', contra_broker_);
    offset += 3;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(original_execution_id_));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(original_trade_price_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(original_trade_quantity_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(corrected_trade_price_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(corrected_trade_quantity_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t TradeCorrectMessage::encoded_size() const {
    return wire_size;
}

void TradeCorrectMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeCorrectMessage::clone() const {
    return std::make_unique<TradeCorrectMessage>(*this);
}

void TradeCorrectMessage::print(std::ostream& out) const {
    out << "TradeCorrectMessage{";
    out << "symbol_id=";
    out << symbol_id_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", reserved_8=";
    out << reserved_8_;
    out << ", reserved_1=";
    print::character(out, reserved_1_);
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", execution_id=";
    out << execution_id_;
    out << ", broker=";
    print::text(out, broker_);
    out << ", contra_broker=";
    print::text(out, contra_broker_);
    out << ", original_execution_id=";
    out << original_execution_id_;
    out << ", original_trade_price=";
    out << original_trade_price_;
    out << ", original_trade_quantity=";
    out << original_trade_quantity_;
    out << ", corrected_trade_price=";
    out << corrected_trade_price_;
    out << ", corrected_trade_quantity=";
    out << corrected_trade_quantity_;
    out << '}';
}

bool TradeCorrectMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeCorrectMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeCorrectMessage::operator==(const TradeCorrectMessage& other) const {
    return symbol_id_ == other.symbol_id_
        && timestamp_ == other.timestamp_
        && reserved_8_ == other.reserved_8_
        && reserved_1_ == other.reserved_1_
        && symbol_ == other.symbol_
        && execution_id_ == other.execution_id_
        && broker_ == other.broker_
        && contra_broker_ == other.contra_broker_
        && original_execution_id_ == other.original_execution_id_
        && original_trade_price_ == other.original_trade_price_
        && original_trade_quantity_ == other.original_trade_quantity_
        && corrected_trade_price_ == other.corrected_trade_price_
        && corrected_trade_quantity_ == other.corrected_trade_quantity_;
}

bool TradeCorrectMessage::operator!=(const TradeCorrectMessage& other) const {
    return !(*this == other);
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
