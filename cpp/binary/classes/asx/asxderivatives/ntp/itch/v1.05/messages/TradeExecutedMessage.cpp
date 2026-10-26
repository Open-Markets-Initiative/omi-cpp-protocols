#include "TradeExecutedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

TradeExecutedMessage::TradeExecutedMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, TradeType trade_type, std::uint64_t trade_id, std::uint32_t executed_quantity, Decimal trade_price, std::uint64_t combination_trade_id, const std::string& participant_id_buyer, const std::string& participant_id_seller)
  : nanoseconds_(nanoseconds), trade_date_(trade_date), tradeable_instrument_id_(tradeable_instrument_id), trade_type_(trade_type), trade_id_(trade_id), executed_quantity_(executed_quantity), trade_price_(trade_price), combination_trade_id_(combination_trade_id), participant_id_buyer_(participant_id_buyer), participant_id_seller_(participant_id_seller) {}

std::chrono::nanoseconds TradeExecutedMessage::nanoseconds() const { return nanoseconds_; }
void TradeExecutedMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint16_t TradeExecutedMessage::trade_date() const { return trade_date_; }
void TradeExecutedMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::uint32_t TradeExecutedMessage::tradeable_instrument_id() const { return tradeable_instrument_id_; }
void TradeExecutedMessage::set_tradeable_instrument_id(std::uint32_t value) { tradeable_instrument_id_ = value; }

TradeType TradeExecutedMessage::trade_type() const { return trade_type_; }
void TradeExecutedMessage::set_trade_type(TradeType value) { trade_type_ = value; }

std::uint64_t TradeExecutedMessage::trade_id() const { return trade_id_; }
void TradeExecutedMessage::set_trade_id(std::uint64_t value) { trade_id_ = value; }

std::uint32_t TradeExecutedMessage::executed_quantity() const { return executed_quantity_; }
void TradeExecutedMessage::set_executed_quantity(std::uint32_t value) { executed_quantity_ = value; }

Decimal TradeExecutedMessage::trade_price() const { return trade_price_; }
void TradeExecutedMessage::set_trade_price(Decimal value) { trade_price_ = value; }

std::uint64_t TradeExecutedMessage::combination_trade_id() const { return combination_trade_id_; }
void TradeExecutedMessage::set_combination_trade_id(std::uint64_t value) { combination_trade_id_ = value; }

const std::string& TradeExecutedMessage::participant_id_buyer() const { return participant_id_buyer_; }
std::string& TradeExecutedMessage::participant_id_buyer() { return participant_id_buyer_; }
void TradeExecutedMessage::set_participant_id_buyer(const std::string& value) { participant_id_buyer_ = value; }

const std::string& TradeExecutedMessage::participant_id_seller() const { return participant_id_seller_; }
std::string& TradeExecutedMessage::participant_id_seller() { return participant_id_seller_; }
void TradeExecutedMessage::set_participant_id_seller(const std::string& value) { participant_id_seller_ = value; }

MessageCode TradeExecutedMessage::type() const { return message_type; }

std::string_view TradeExecutedMessage::name() const { return "Trade Executed Message"; }

std::size_t TradeExecutedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeExecutedMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    trade_date_ = wire::read_u16_be(data + offset);
    offset += 2;

    tradeable_instrument_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    trade_type_ = static_cast<TradeType>(wire::read_char(data + offset));
    offset += 1;

    trade_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    executed_quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
    offset += 8;

    combination_trade_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    participant_id_buyer_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    participant_id_seller_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    return offset;
}

std::size_t TradeExecutedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeExecutedMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(tradeable_instrument_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(trade_type_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(trade_id_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(executed_quantity_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(trade_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(combination_trade_id_));
    offset += 8;

    wire::write_text(data + offset, 3, ' ', participant_id_buyer_);
    offset += 3;

    wire::write_text(data + offset, 3, ' ', participant_id_seller_);
    offset += 3;

    return offset;
}

std::size_t TradeExecutedMessage::encoded_size() const {
    return wire_size;
}

void TradeExecutedMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeExecutedMessage::clone() const {
    return std::make_unique<TradeExecutedMessage>(*this);
}

void TradeExecutedMessage::print(std::ostream& out) const {
    out << "TradeExecutedMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", trade_date=";
    out << trade_date_;
    out << ", tradeable_instrument_id=";
    out << tradeable_instrument_id_;
    out << ", trade_type=";
    out << trade_type_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", executed_quantity=";
    out << executed_quantity_;
    out << ", trade_price=";
    out << trade_price_;
    out << ", combination_trade_id=";
    out << combination_trade_id_;
    out << ", participant_id_buyer=";
    print::text(out, participant_id_buyer_);
    out << ", participant_id_seller=";
    print::text(out, participant_id_seller_);
    out << '}';
}

bool TradeExecutedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeExecutedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeExecutedMessage::operator==(const TradeExecutedMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && trade_date_ == other.trade_date_
        && tradeable_instrument_id_ == other.tradeable_instrument_id_
        && trade_type_ == other.trade_type_
        && trade_id_ == other.trade_id_
        && executed_quantity_ == other.executed_quantity_
        && trade_price_ == other.trade_price_
        && combination_trade_id_ == other.combination_trade_id_
        && participant_id_buyer_ == other.participant_id_buyer_
        && participant_id_seller_ == other.participant_id_seller_;
}

bool TradeExecutedMessage::operator!=(const TradeExecutedMessage& other) const {
    return !(*this == other);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
