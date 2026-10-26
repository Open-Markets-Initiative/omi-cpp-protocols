#include "InstrumentDirectoryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

InstrumentDirectoryMessage::InstrumentDirectoryMessage(std::chrono::nanoseconds timestamp, std::uint16_t security_id, const std::string& symbol, const std::string& symbol_sfx, std::uint32_t round_lot, std::uint8_t reserved, IsTestSymbol is_test_symbol, Decimal mpv)
  : timestamp_(timestamp), security_id_(security_id), symbol_(symbol), symbol_sfx_(symbol_sfx), round_lot_(round_lot), reserved_(reserved), is_test_symbol_(is_test_symbol), mpv_(mpv) {}

std::chrono::nanoseconds InstrumentDirectoryMessage::timestamp() const { return timestamp_; }
void InstrumentDirectoryMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t InstrumentDirectoryMessage::security_id() const { return security_id_; }
void InstrumentDirectoryMessage::set_security_id(std::uint16_t value) { security_id_ = value; }

const std::string& InstrumentDirectoryMessage::symbol() const { return symbol_; }
std::string& InstrumentDirectoryMessage::symbol() { return symbol_; }
void InstrumentDirectoryMessage::set_symbol(const std::string& value) { symbol_ = value; }

const std::string& InstrumentDirectoryMessage::symbol_sfx() const { return symbol_sfx_; }
std::string& InstrumentDirectoryMessage::symbol_sfx() { return symbol_sfx_; }
void InstrumentDirectoryMessage::set_symbol_sfx(const std::string& value) { symbol_sfx_ = value; }

std::uint32_t InstrumentDirectoryMessage::round_lot() const { return round_lot_; }
void InstrumentDirectoryMessage::set_round_lot(std::uint32_t value) { round_lot_ = value; }

std::uint8_t InstrumentDirectoryMessage::reserved() const { return reserved_; }
void InstrumentDirectoryMessage::set_reserved(std::uint8_t value) { reserved_ = value; }

IsTestSymbol InstrumentDirectoryMessage::is_test_symbol() const { return is_test_symbol_; }
void InstrumentDirectoryMessage::set_is_test_symbol(IsTestSymbol value) { is_test_symbol_ = value; }

Decimal InstrumentDirectoryMessage::mpv() const { return mpv_; }
void InstrumentDirectoryMessage::set_mpv(Decimal value) { mpv_ = value; }

PayloadCode InstrumentDirectoryMessage::type() const { return message_type; }

std::string_view InstrumentDirectoryMessage::name() const { return "Instrument Directory Message"; }

std::size_t InstrumentDirectoryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("InstrumentDirectoryMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    security_id_ = wire::read_u16_be(data + offset);
    offset += 2;

    symbol_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    symbol_sfx_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    round_lot_ = wire::read_u32_be(data + offset);
    offset += 4;

    reserved_ = wire::read_u8(data + offset);
    offset += 1;

    is_test_symbol_ = static_cast<IsTestSymbol>(wire::read_u8(data + offset));
    offset += 1;

    mpv_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -6);
    offset += 8;

    return offset;
}

std::size_t InstrumentDirectoryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InstrumentDirectoryMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(security_id_));
    offset += 2;

    wire::write_text(data + offset, 6, '\0', symbol_);
    offset += 6;

    wire::write_text(data + offset, 6, '\0', symbol_sfx_);
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(round_lot_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(reserved_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(is_test_symbol_));
    offset += 1;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(mpv_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t InstrumentDirectoryMessage::encoded_size() const {
    return wire_size;
}

void InstrumentDirectoryMessage::accept(PayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Payload> InstrumentDirectoryMessage::clone() const {
    return std::make_unique<InstrumentDirectoryMessage>(*this);
}

void InstrumentDirectoryMessage::print(std::ostream& out) const {
    out << "InstrumentDirectoryMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", security_id=";
    out << security_id_;
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", symbol_sfx=";
    print::text(out, symbol_sfx_);
    out << ", round_lot=";
    out << round_lot_;
    out << ", reserved=";
    out << static_cast<int>(reserved_);
    out << ", is_test_symbol=";
    out << is_test_symbol_;
    out << ", mpv=";
    out << mpv_;
    out << '}';
}

bool InstrumentDirectoryMessage::equals(const Payload& other) const {
    const auto* that = dynamic_cast<const InstrumentDirectoryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool InstrumentDirectoryMessage::operator==(const InstrumentDirectoryMessage& other) const {
    return timestamp_ == other.timestamp_
        && security_id_ == other.security_id_
        && symbol_ == other.symbol_
        && symbol_sfx_ == other.symbol_sfx_
        && round_lot_ == other.round_lot_
        && reserved_ == other.reserved_
        && is_test_symbol_ == other.is_test_symbol_
        && mpv_ == other.mpv_;
}

bool InstrumentDirectoryMessage::operator!=(const InstrumentDirectoryMessage& other) const {
    return !(*this == other);
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
