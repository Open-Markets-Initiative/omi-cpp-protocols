#include "SymbolStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

SymbolStatusMessage::SymbolStatusMessage(std::uint32_t nanosecond, std::uint32_t instrument_id, const std::array<std::byte, 1>& reserved_a, const std::array<std::byte, 1>& reserved_b, TradingStatus trading_status, const SymbolStatusFlags& symbol_status_flags, const std::string& reason, SessionChangeReason session_change_reason, const std::string& new_end_time, BookType book_type)
  : nanosecond_(nanosecond), instrument_id_(instrument_id), reserved_a_(reserved_a), reserved_b_(reserved_b), trading_status_(trading_status), symbol_status_flags_(symbol_status_flags), reason_(reason), session_change_reason_(session_change_reason), new_end_time_(new_end_time), book_type_(book_type) {}

std::uint32_t SymbolStatusMessage::nanosecond() const { return nanosecond_; }
void SymbolStatusMessage::set_nanosecond(std::uint32_t value) { nanosecond_ = value; }

std::uint32_t SymbolStatusMessage::instrument_id() const { return instrument_id_; }
void SymbolStatusMessage::set_instrument_id(std::uint32_t value) { instrument_id_ = value; }

const std::array<std::byte, 1>& SymbolStatusMessage::reserved_a() const { return reserved_a_; }
std::array<std::byte, 1>& SymbolStatusMessage::reserved_a() { return reserved_a_; }
void SymbolStatusMessage::set_reserved_a(const std::array<std::byte, 1>& value) { reserved_a_ = value; }

const std::array<std::byte, 1>& SymbolStatusMessage::reserved_b() const { return reserved_b_; }
std::array<std::byte, 1>& SymbolStatusMessage::reserved_b() { return reserved_b_; }
void SymbolStatusMessage::set_reserved_b(const std::array<std::byte, 1>& value) { reserved_b_ = value; }

TradingStatus SymbolStatusMessage::trading_status() const { return trading_status_; }
void SymbolStatusMessage::set_trading_status(TradingStatus value) { trading_status_ = value; }

const SymbolStatusFlags& SymbolStatusMessage::symbol_status_flags() const { return symbol_status_flags_; }
SymbolStatusFlags& SymbolStatusMessage::symbol_status_flags() { return symbol_status_flags_; }
void SymbolStatusMessage::set_symbol_status_flags(const SymbolStatusFlags& value) { symbol_status_flags_ = value; }

const std::string& SymbolStatusMessage::reason() const { return reason_; }
std::string& SymbolStatusMessage::reason() { return reason_; }
void SymbolStatusMessage::set_reason(const std::string& value) { reason_ = value; }

SessionChangeReason SymbolStatusMessage::session_change_reason() const { return session_change_reason_; }
void SymbolStatusMessage::set_session_change_reason(SessionChangeReason value) { session_change_reason_ = value; }

const std::string& SymbolStatusMessage::new_end_time() const { return new_end_time_; }
std::string& SymbolStatusMessage::new_end_time() { return new_end_time_; }
void SymbolStatusMessage::set_new_end_time(const std::string& value) { new_end_time_ = value; }

BookType SymbolStatusMessage::book_type() const { return book_type_; }
void SymbolStatusMessage::set_book_type(BookType value) { book_type_ = value; }

MessageCode SymbolStatusMessage::type() const { return message_type; }

std::string_view SymbolStatusMessage::name() const { return "Symbol Status Message"; }

std::size_t SymbolStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SymbolStatusMessage", wire_size, length);

    nanosecond_ = wire::read_u32_le(data + offset);
    offset += 4;

    instrument_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, reserved_a_.data(), 1);
    offset += 1;

    wire::read_bytes(data + offset, reserved_b_.data(), 1);
    offset += 1;

    trading_status_ = static_cast<TradingStatus>(wire::read_char(data + offset));
    offset += 1;

    offset += symbol_status_flags_.decode(data + offset, length - offset);

    reason_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    session_change_reason_ = static_cast<SessionChangeReason>(wire::read_u8(data + offset));
    offset += 1;

    new_end_time_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    book_type_ = static_cast<BookType>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t SymbolStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SymbolStatusMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanosecond_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(instrument_id_));
    offset += 4;

    wire::write_bytes(data + offset, reserved_a_.data(), 1);
    offset += 1;

    wire::write_bytes(data + offset, reserved_b_.data(), 1);
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trading_status_));
    offset += 1;

    offset += symbol_status_flags_.encode(data + offset, capacity - offset);

    wire::write_text(data + offset, 4, ' ', reason_);
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(session_change_reason_));
    offset += 1;

    wire::write_text(data + offset, 8, ' ', new_end_time_);
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(book_type_));
    offset += 1;

    return offset;
}

std::size_t SymbolStatusMessage::encoded_size() const {
    return wire_size;
}

void SymbolStatusMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SymbolStatusMessage::clone() const {
    return std::make_unique<SymbolStatusMessage>(*this);
}

void SymbolStatusMessage::print(std::ostream& out) const {
    out << "SymbolStatusMessage{";
    out << "nanosecond=";
    out << nanosecond_;
    out << ", instrument_id=";
    out << instrument_id_;
    out << ", reserved_a=";
    print::hex(out, reserved_a_.data(), reserved_a_.size());
    out << ", reserved_b=";
    print::hex(out, reserved_b_.data(), reserved_b_.size());
    out << ", trading_status=";
    out << trading_status_;
    out << ", symbol_status_flags=";
    symbol_status_flags_.print(out);
    out << ", reason=";
    print::text(out, reason_);
    out << ", session_change_reason=";
    out << session_change_reason_;
    out << ", new_end_time=";
    print::text(out, new_end_time_);
    out << ", book_type=";
    out << book_type_;
    out << '}';
}

bool SymbolStatusMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SymbolStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SymbolStatusMessage::operator==(const SymbolStatusMessage& other) const {
    return nanosecond_ == other.nanosecond_
        && instrument_id_ == other.instrument_id_
        && reserved_a_ == other.reserved_a_
        && reserved_b_ == other.reserved_b_
        && trading_status_ == other.trading_status_
        && symbol_status_flags_ == other.symbol_status_flags_
        && reason_ == other.reason_
        && session_change_reason_ == other.session_change_reason_
        && new_end_time_ == other.new_end_time_
        && book_type_ == other.book_type_;
}

bool SymbolStatusMessage::operator!=(const SymbolStatusMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::millennium::level2::mitch::v11_9
