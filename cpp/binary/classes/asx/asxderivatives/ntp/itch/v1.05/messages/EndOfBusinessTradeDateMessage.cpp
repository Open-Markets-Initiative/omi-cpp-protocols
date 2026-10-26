#include "EndOfBusinessTradeDateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

EndOfBusinessTradeDateMessage::EndOfBusinessTradeDateMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, EventCode event_code)
  : nanoseconds_(nanoseconds), trade_date_(trade_date), event_code_(event_code) {}

std::chrono::nanoseconds EndOfBusinessTradeDateMessage::nanoseconds() const { return nanoseconds_; }
void EndOfBusinessTradeDateMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint16_t EndOfBusinessTradeDateMessage::trade_date() const { return trade_date_; }
void EndOfBusinessTradeDateMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

EventCode EndOfBusinessTradeDateMessage::event_code() const { return event_code_; }
void EndOfBusinessTradeDateMessage::set_event_code(EventCode value) { event_code_ = value; }

MessageCode EndOfBusinessTradeDateMessage::type() const { return message_type; }

std::string_view EndOfBusinessTradeDateMessage::name() const { return "End Of Business Trade Date Message"; }

std::size_t EndOfBusinessTradeDateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EndOfBusinessTradeDateMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    trade_date_ = wire::read_u16_be(data + offset);
    offset += 2;

    event_code_ = static_cast<EventCode>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t EndOfBusinessTradeDateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EndOfBusinessTradeDateMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(event_code_));
    offset += 1;

    return offset;
}

std::size_t EndOfBusinessTradeDateMessage::encoded_size() const {
    return wire_size;
}

void EndOfBusinessTradeDateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> EndOfBusinessTradeDateMessage::clone() const {
    return std::make_unique<EndOfBusinessTradeDateMessage>(*this);
}

void EndOfBusinessTradeDateMessage::print(std::ostream& out) const {
    out << "EndOfBusinessTradeDateMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", trade_date=";
    out << trade_date_;
    out << ", event_code=";
    out << event_code_;
    out << '}';
}

bool EndOfBusinessTradeDateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const EndOfBusinessTradeDateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool EndOfBusinessTradeDateMessage::operator==(const EndOfBusinessTradeDateMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && trade_date_ == other.trade_date_
        && event_code_ == other.event_code_;
}

bool EndOfBusinessTradeDateMessage::operator!=(const EndOfBusinessTradeDateMessage& other) const {
    return !(*this == other);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
