#include "OrderBookStateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

OrderBookStateMessage::OrderBookStateMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, SessionState session_state)
  : nanoseconds_(nanoseconds), trade_date_(trade_date), tradeable_instrument_id_(tradeable_instrument_id), session_state_(session_state) {}

std::chrono::nanoseconds OrderBookStateMessage::nanoseconds() const { return nanoseconds_; }
void OrderBookStateMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint16_t OrderBookStateMessage::trade_date() const { return trade_date_; }
void OrderBookStateMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::uint32_t OrderBookStateMessage::tradeable_instrument_id() const { return tradeable_instrument_id_; }
void OrderBookStateMessage::set_tradeable_instrument_id(std::uint32_t value) { tradeable_instrument_id_ = value; }

SessionState OrderBookStateMessage::session_state() const { return session_state_; }
void OrderBookStateMessage::set_session_state(SessionState value) { session_state_ = value; }

MessageCode OrderBookStateMessage::type() const { return message_type; }

std::string_view OrderBookStateMessage::name() const { return "Order Book State Message"; }

std::size_t OrderBookStateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderBookStateMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    trade_date_ = wire::read_u16_be(data + offset);
    offset += 2;

    tradeable_instrument_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    session_state_ = static_cast<SessionState>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t OrderBookStateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderBookStateMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(tradeable_instrument_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(session_state_));
    offset += 1;

    return offset;
}

std::size_t OrderBookStateMessage::encoded_size() const {
    return wire_size;
}

void OrderBookStateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderBookStateMessage::clone() const {
    return std::make_unique<OrderBookStateMessage>(*this);
}

void OrderBookStateMessage::print(std::ostream& out) const {
    out << "OrderBookStateMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", trade_date=";
    out << trade_date_;
    out << ", tradeable_instrument_id=";
    out << tradeable_instrument_id_;
    out << ", session_state=";
    out << session_state_;
    out << '}';
}

bool OrderBookStateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderBookStateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderBookStateMessage::operator==(const OrderBookStateMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && trade_date_ == other.trade_date_
        && tradeable_instrument_id_ == other.tradeable_instrument_id_
        && session_state_ == other.session_state_;
}

bool OrderBookStateMessage::operator!=(const OrderBookStateMessage& other) const {
    return !(*this == other);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
