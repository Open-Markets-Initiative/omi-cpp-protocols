// Miax.MiaxOptions.TopOfMarket.Mach.v2.5: messages/UnderlyingTradingStatusNotificationMessage.cpp
#include "UnderlyingTradingStatusNotificationMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

UnderlyingTradingStatusNotificationMessage::UnderlyingTradingStatusNotificationMessage(std::chrono::nanoseconds nanoseconds, const std::string& underlying_symbol, TradingStatus trading_status, EventReason event_reason, std::optional<std::chrono::seconds> expected_event_time_seconds_part, std::chrono::nanoseconds expected_event_time_nano_seconds_part)
  : nanoseconds_(nanoseconds), underlying_symbol_(underlying_symbol), trading_status_(trading_status), event_reason_(event_reason), expected_event_time_seconds_part_(expected_event_time_seconds_part), expected_event_time_nano_seconds_part_(expected_event_time_nano_seconds_part) {}

std::chrono::nanoseconds UnderlyingTradingStatusNotificationMessage::nanoseconds() const { return nanoseconds_; }
void UnderlyingTradingStatusNotificationMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

const std::string& UnderlyingTradingStatusNotificationMessage::underlying_symbol() const { return underlying_symbol_; }
std::string& UnderlyingTradingStatusNotificationMessage::underlying_symbol() { return underlying_symbol_; }
void UnderlyingTradingStatusNotificationMessage::set_underlying_symbol(const std::string& value) { underlying_symbol_ = value; }

TradingStatus UnderlyingTradingStatusNotificationMessage::trading_status() const { return trading_status_; }
void UnderlyingTradingStatusNotificationMessage::set_trading_status(TradingStatus value) { trading_status_ = value; }

EventReason UnderlyingTradingStatusNotificationMessage::event_reason() const { return event_reason_; }
void UnderlyingTradingStatusNotificationMessage::set_event_reason(EventReason value) { event_reason_ = value; }

std::optional<std::chrono::seconds> UnderlyingTradingStatusNotificationMessage::expected_event_time_seconds_part() const { return expected_event_time_seconds_part_; }
void UnderlyingTradingStatusNotificationMessage::set_expected_event_time_seconds_part(std::optional<std::chrono::seconds> value) { expected_event_time_seconds_part_ = value; }

std::chrono::nanoseconds UnderlyingTradingStatusNotificationMessage::expected_event_time_nano_seconds_part() const { return expected_event_time_nano_seconds_part_; }
void UnderlyingTradingStatusNotificationMessage::set_expected_event_time_nano_seconds_part(std::chrono::nanoseconds value) { expected_event_time_nano_seconds_part_ = value; }

DataCode UnderlyingTradingStatusNotificationMessage::type() const { return message_type; }

std::string_view UnderlyingTradingStatusNotificationMessage::name() const { return "Underlying Trading Status Notification Message"; }

std::size_t UnderlyingTradingStatusNotificationMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("UnderlyingTradingStatusNotificationMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    underlying_symbol_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    trading_status_ = static_cast<TradingStatus>(wire::read_char(data + offset));
    offset += 1;

    event_reason_ = static_cast<EventReason>(wire::read_char(data + offset));
    offset += 1;

    expected_event_time_seconds_part_ = wire::nullable_duration<std::chrono::seconds>(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    expected_event_time_nano_seconds_part_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    return offset;
}

std::size_t UnderlyingTradingStatusNotificationMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UnderlyingTradingStatusNotificationMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_text(data + offset, 11, ' ', underlying_symbol_);
    offset += 11;

    wire::write_char(data + offset, static_cast<char>(trading_status_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(event_reason_));
    offset += 1;

    wire::write_u32_le(data + offset, expected_event_time_seconds_part_ ? static_cast<std::uint32_t>(expected_event_time_seconds_part_->count()) : static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(expected_event_time_nano_seconds_part_.count()));
    offset += 4;

    return offset;
}

std::size_t UnderlyingTradingStatusNotificationMessage::encoded_size() const {
    return wire_size;
}

void UnderlyingTradingStatusNotificationMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> UnderlyingTradingStatusNotificationMessage::clone() const {
    return std::make_unique<UnderlyingTradingStatusNotificationMessage>(*this);
}

void UnderlyingTradingStatusNotificationMessage::print(std::ostream& out) const {
    out << "UnderlyingTradingStatusNotificationMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", underlying_symbol=";
    print::text(out, underlying_symbol_);
    out << ", trading_status=";
    out << trading_status_;
    out << ", event_reason=";
    out << event_reason_;
    out << ", expected_event_time_seconds_part=";
    print::optional_duration(out, expected_event_time_seconds_part_);
    out << ", expected_event_time_nano_seconds_part=";
    out << expected_event_time_nano_seconds_part_.count();
    out << '}';
}

bool UnderlyingTradingStatusNotificationMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const UnderlyingTradingStatusNotificationMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UnderlyingTradingStatusNotificationMessage::operator==(const UnderlyingTradingStatusNotificationMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && underlying_symbol_ == other.underlying_symbol_
        && trading_status_ == other.trading_status_
        && event_reason_ == other.event_reason_
        && expected_event_time_seconds_part_ == other.expected_event_time_seconds_part_
        && expected_event_time_nano_seconds_part_ == other.expected_event_time_nano_seconds_part_;
}

bool UnderlyingTradingStatusNotificationMessage::operator!=(const UnderlyingTradingStatusNotificationMessage& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
