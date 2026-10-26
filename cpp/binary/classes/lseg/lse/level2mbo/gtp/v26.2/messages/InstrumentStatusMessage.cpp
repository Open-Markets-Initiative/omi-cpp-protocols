#include "InstrumentStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

InstrumentStatusMessage::InstrumentStatusMessage(std::chrono::nanoseconds timestamp, std::uint64_t instrument, SourceVenue source_venue, TradingStatus trading_status, SessionChangeReason session_change_reason, const std::string& new_end_time, OrderBookType order_book_type)
  : timestamp_(timestamp), instrument_(instrument), source_venue_(source_venue), trading_status_(trading_status), session_change_reason_(session_change_reason), new_end_time_(new_end_time), order_book_type_(order_book_type) {}

std::chrono::nanoseconds InstrumentStatusMessage::timestamp() const { return timestamp_; }
void InstrumentStatusMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t InstrumentStatusMessage::instrument() const { return instrument_; }
void InstrumentStatusMessage::set_instrument(std::uint64_t value) { instrument_ = value; }

SourceVenue InstrumentStatusMessage::source_venue() const { return source_venue_; }
void InstrumentStatusMessage::set_source_venue(SourceVenue value) { source_venue_ = value; }

TradingStatus InstrumentStatusMessage::trading_status() const { return trading_status_; }
void InstrumentStatusMessage::set_trading_status(TradingStatus value) { trading_status_ = value; }

SessionChangeReason InstrumentStatusMessage::session_change_reason() const { return session_change_reason_; }
void InstrumentStatusMessage::set_session_change_reason(SessionChangeReason value) { session_change_reason_ = value; }

const std::string& InstrumentStatusMessage::new_end_time() const { return new_end_time_; }
std::string& InstrumentStatusMessage::new_end_time() { return new_end_time_; }
void InstrumentStatusMessage::set_new_end_time(const std::string& value) { new_end_time_ = value; }

OrderBookType InstrumentStatusMessage::order_book_type() const { return order_book_type_; }
void InstrumentStatusMessage::set_order_book_type(OrderBookType value) { order_book_type_ = value; }

MessageCode InstrumentStatusMessage::type() const { return message_type; }

std::string_view InstrumentStatusMessage::name() const { return "Instrument Status Message"; }

std::size_t InstrumentStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("InstrumentStatusMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    instrument_ = wire::read_u64_le(data + offset);
    offset += 8;

    source_venue_ = static_cast<SourceVenue>(wire::read_u16_le(data + offset));
    offset += 2;

    trading_status_ = static_cast<TradingStatus>(wire::read_char(data + offset));
    offset += 1;

    session_change_reason_ = static_cast<SessionChangeReason>(wire::read_u8(data + offset));
    offset += 1;

    new_end_time_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    order_book_type_ = static_cast<OrderBookType>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t InstrumentStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InstrumentStatusMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(instrument_));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(source_venue_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(trading_status_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(session_change_reason_));
    offset += 1;

    wire::write_text(data + offset, 6, ' ', new_end_time_);
    offset += 6;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(order_book_type_));
    offset += 1;

    return offset;
}

std::size_t InstrumentStatusMessage::encoded_size() const {
    return wire_size;
}

void InstrumentStatusMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> InstrumentStatusMessage::clone() const {
    return std::make_unique<InstrumentStatusMessage>(*this);
}

void InstrumentStatusMessage::print(std::ostream& out) const {
    out << "InstrumentStatusMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", instrument=";
    out << instrument_;
    out << ", source_venue=";
    out << source_venue_;
    out << ", trading_status=";
    out << trading_status_;
    out << ", session_change_reason=";
    out << session_change_reason_;
    out << ", new_end_time=";
    print::text(out, new_end_time_);
    out << ", order_book_type=";
    out << order_book_type_;
    out << '}';
}

bool InstrumentStatusMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const InstrumentStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool InstrumentStatusMessage::operator==(const InstrumentStatusMessage& other) const {
    return timestamp_ == other.timestamp_
        && instrument_ == other.instrument_
        && source_venue_ == other.source_venue_
        && trading_status_ == other.trading_status_
        && session_change_reason_ == other.session_change_reason_
        && new_end_time_ == other.new_end_time_
        && order_book_type_ == other.order_book_type_;
}

bool InstrumentStatusMessage::operator!=(const InstrumentStatusMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
