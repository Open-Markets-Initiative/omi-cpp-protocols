#include "UnderlyingTradingStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

UnderlyingTradingStatusMessage::UnderlyingTradingStatusMessage(std::chrono::nanoseconds nanoseconds, const std::string& underlying_symbol, TradingStatus trading_status, EventReason event_reason, std::uint32_t seconds_part, std::uint32_t expected_event_time_nano_seconds_part)
  : nanoseconds_(nanoseconds), underlying_symbol_(underlying_symbol), trading_status_(trading_status), event_reason_(event_reason), seconds_part_(seconds_part), expected_event_time_nano_seconds_part_(expected_event_time_nano_seconds_part) {}

std::chrono::nanoseconds UnderlyingTradingStatusMessage::nanoseconds() const { return nanoseconds_; }
void UnderlyingTradingStatusMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

const std::string& UnderlyingTradingStatusMessage::underlying_symbol() const { return underlying_symbol_; }
std::string& UnderlyingTradingStatusMessage::underlying_symbol() { return underlying_symbol_; }
void UnderlyingTradingStatusMessage::set_underlying_symbol(const std::string& value) { underlying_symbol_ = value; }

TradingStatus UnderlyingTradingStatusMessage::trading_status() const { return trading_status_; }
void UnderlyingTradingStatusMessage::set_trading_status(TradingStatus value) { trading_status_ = value; }

EventReason UnderlyingTradingStatusMessage::event_reason() const { return event_reason_; }
void UnderlyingTradingStatusMessage::set_event_reason(EventReason value) { event_reason_ = value; }

std::uint32_t UnderlyingTradingStatusMessage::seconds_part() const { return seconds_part_; }
void UnderlyingTradingStatusMessage::set_seconds_part(std::uint32_t value) { seconds_part_ = value; }

std::uint32_t UnderlyingTradingStatusMessage::expected_event_time_nano_seconds_part() const { return expected_event_time_nano_seconds_part_; }
void UnderlyingTradingStatusMessage::set_expected_event_time_nano_seconds_part(std::uint32_t value) { expected_event_time_nano_seconds_part_ = value; }

DataCode UnderlyingTradingStatusMessage::type() const { return message_type; }

std::string_view UnderlyingTradingStatusMessage::name() const { return "Underlying Trading Status Message"; }

std::size_t UnderlyingTradingStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UnderlyingTradingStatusMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    underlying_symbol_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    trading_status_ = static_cast<TradingStatus>(wire::read_char(data + offset));
    offset += 1;

    event_reason_ = static_cast<EventReason>(wire::read_char(data + offset));
    offset += 1;

    seconds_part_ = wire::read_u32_le(data + offset);
    offset += 4;

    expected_event_time_nano_seconds_part_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t UnderlyingTradingStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UnderlyingTradingStatusMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_text(data + offset, 11, ' ', underlying_symbol_);
    offset += 11;

    wire::write_char(data + offset, static_cast<char>(trading_status_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(event_reason_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(seconds_part_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(expected_event_time_nano_seconds_part_));
    offset += 4;

    return offset;
}

std::size_t UnderlyingTradingStatusMessage::encoded_size() const {
    return wire_size;
}

void UnderlyingTradingStatusMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> UnderlyingTradingStatusMessage::clone() const {
    return std::make_unique<UnderlyingTradingStatusMessage>(*this);
}

void UnderlyingTradingStatusMessage::print(std::ostream& out) const {
    out << "UnderlyingTradingStatusMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", underlying_symbol=";
    print::text(out, underlying_symbol_);
    out << ", trading_status=";
    out << trading_status_;
    out << ", event_reason=";
    out << event_reason_;
    out << ", seconds_part=";
    out << seconds_part_;
    out << ", expected_event_time_nano_seconds_part=";
    out << expected_event_time_nano_seconds_part_;
    out << '}';
}

bool UnderlyingTradingStatusMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const UnderlyingTradingStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UnderlyingTradingStatusMessage::operator==(const UnderlyingTradingStatusMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && underlying_symbol_ == other.underlying_symbol_
        && trading_status_ == other.trading_status_
        && event_reason_ == other.event_reason_
        && seconds_part_ == other.seconds_part_
        && expected_event_time_nano_seconds_part_ == other.expected_event_time_nano_seconds_part_;
}

bool UnderlyingTradingStatusMessage::operator!=(const UnderlyingTradingStatusMessage& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
