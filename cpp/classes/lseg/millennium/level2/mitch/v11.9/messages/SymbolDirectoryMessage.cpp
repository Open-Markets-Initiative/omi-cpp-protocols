#include "SymbolDirectoryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

SymbolDirectoryMessage::SymbolDirectoryMessage(std::uint32_t nanosecond, std::uint32_t instrument_id, const std::array<std::byte, 1>& reserved_a, const std::array<std::byte, 1>& reserved_b, SymbolStatus symbol_status, const std::string& isin, const std::string& sedol, const std::string& segment, const std::string& underlying, const std::string& currency, const std::array<std::byte, 1>& reserved_byte, const std::array<std::byte, 4>& reserved_4, std::int64_t previous_close_price)
  : nanosecond_(nanosecond), instrument_id_(instrument_id), reserved_a_(reserved_a), reserved_b_(reserved_b), symbol_status_(symbol_status), isin_(isin), sedol_(sedol), segment_(segment), underlying_(underlying), currency_(currency), reserved_byte_(reserved_byte), reserved_4_(reserved_4), previous_close_price_(previous_close_price) {}

std::uint32_t SymbolDirectoryMessage::nanosecond() const { return nanosecond_; }
void SymbolDirectoryMessage::set_nanosecond(std::uint32_t value) { nanosecond_ = value; }

std::uint32_t SymbolDirectoryMessage::instrument_id() const { return instrument_id_; }
void SymbolDirectoryMessage::set_instrument_id(std::uint32_t value) { instrument_id_ = value; }

const std::array<std::byte, 1>& SymbolDirectoryMessage::reserved_a() const { return reserved_a_; }
std::array<std::byte, 1>& SymbolDirectoryMessage::reserved_a() { return reserved_a_; }
void SymbolDirectoryMessage::set_reserved_a(const std::array<std::byte, 1>& value) { reserved_a_ = value; }

const std::array<std::byte, 1>& SymbolDirectoryMessage::reserved_b() const { return reserved_b_; }
std::array<std::byte, 1>& SymbolDirectoryMessage::reserved_b() { return reserved_b_; }
void SymbolDirectoryMessage::set_reserved_b(const std::array<std::byte, 1>& value) { reserved_b_ = value; }

SymbolStatus SymbolDirectoryMessage::symbol_status() const { return symbol_status_; }
void SymbolDirectoryMessage::set_symbol_status(SymbolStatus value) { symbol_status_ = value; }

const std::string& SymbolDirectoryMessage::isin() const { return isin_; }
std::string& SymbolDirectoryMessage::isin() { return isin_; }
void SymbolDirectoryMessage::set_isin(const std::string& value) { isin_ = value; }

const std::string& SymbolDirectoryMessage::sedol() const { return sedol_; }
std::string& SymbolDirectoryMessage::sedol() { return sedol_; }
void SymbolDirectoryMessage::set_sedol(const std::string& value) { sedol_ = value; }

const std::string& SymbolDirectoryMessage::segment() const { return segment_; }
std::string& SymbolDirectoryMessage::segment() { return segment_; }
void SymbolDirectoryMessage::set_segment(const std::string& value) { segment_ = value; }

const std::string& SymbolDirectoryMessage::underlying() const { return underlying_; }
std::string& SymbolDirectoryMessage::underlying() { return underlying_; }
void SymbolDirectoryMessage::set_underlying(const std::string& value) { underlying_ = value; }

const std::string& SymbolDirectoryMessage::currency() const { return currency_; }
std::string& SymbolDirectoryMessage::currency() { return currency_; }
void SymbolDirectoryMessage::set_currency(const std::string& value) { currency_ = value; }

const std::array<std::byte, 1>& SymbolDirectoryMessage::reserved_byte() const { return reserved_byte_; }
std::array<std::byte, 1>& SymbolDirectoryMessage::reserved_byte() { return reserved_byte_; }
void SymbolDirectoryMessage::set_reserved_byte(const std::array<std::byte, 1>& value) { reserved_byte_ = value; }

const std::array<std::byte, 4>& SymbolDirectoryMessage::reserved_4() const { return reserved_4_; }
std::array<std::byte, 4>& SymbolDirectoryMessage::reserved_4() { return reserved_4_; }
void SymbolDirectoryMessage::set_reserved_4(const std::array<std::byte, 4>& value) { reserved_4_ = value; }

std::int64_t SymbolDirectoryMessage::previous_close_price() const { return previous_close_price_; }
void SymbolDirectoryMessage::set_previous_close_price(std::int64_t value) { previous_close_price_ = value; }

MessageCode SymbolDirectoryMessage::type() const { return message_type; }

std::string_view SymbolDirectoryMessage::name() const { return "Symbol Directory Message"; }

std::size_t SymbolDirectoryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SymbolDirectoryMessage", wire_size, length);

    nanosecond_ = wire::read_u32_le(data + offset);
    offset += 4;

    instrument_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, reserved_a_.data(), 1);
    offset += 1;

    wire::read_bytes(data + offset, reserved_b_.data(), 1);
    offset += 1;

    symbol_status_ = static_cast<SymbolStatus>(wire::read_char(data + offset));
    offset += 1;

    isin_ = wire::read_text(data + offset, 12, ' ');
    offset += 12;

    sedol_ = wire::read_text(data + offset, 12, ' ');
    offset += 12;

    segment_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    underlying_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    currency_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    wire::read_bytes(data + offset, reserved_byte_.data(), 1);
    offset += 1;

    wire::read_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    previous_close_price_ = wire::read_i64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t SymbolDirectoryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SymbolDirectoryMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanosecond_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(instrument_id_));
    offset += 4;

    wire::write_bytes(data + offset, reserved_a_.data(), 1);
    offset += 1;

    wire::write_bytes(data + offset, reserved_b_.data(), 1);
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(symbol_status_));
    offset += 1;

    wire::write_text(data + offset, 12, ' ', isin_);
    offset += 12;

    wire::write_text(data + offset, 12, ' ', sedol_);
    offset += 12;

    wire::write_text(data + offset, 6, ' ', segment_);
    offset += 6;

    wire::write_text(data + offset, 6, ' ', underlying_);
    offset += 6;

    wire::write_text(data + offset, 3, ' ', currency_);
    offset += 3;

    wire::write_bytes(data + offset, reserved_byte_.data(), 1);
    offset += 1;

    wire::write_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(previous_close_price_));
    offset += 8;

    return offset;
}

std::size_t SymbolDirectoryMessage::encoded_size() const {
    return wire_size;
}

void SymbolDirectoryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SymbolDirectoryMessage::clone() const {
    return std::make_unique<SymbolDirectoryMessage>(*this);
}

void SymbolDirectoryMessage::print(std::ostream& out) const {
    out << "SymbolDirectoryMessage{";
    out << "nanosecond=";
    out << nanosecond_;
    out << ", instrument_id=";
    out << instrument_id_;
    out << ", reserved_a=";
    print::hex(out, reserved_a_.data(), reserved_a_.size());
    out << ", reserved_b=";
    print::hex(out, reserved_b_.data(), reserved_b_.size());
    out << ", symbol_status=";
    out << symbol_status_;
    out << ", isin=";
    print::text(out, isin_);
    out << ", sedol=";
    print::text(out, sedol_);
    out << ", segment=";
    print::text(out, segment_);
    out << ", underlying=";
    print::text(out, underlying_);
    out << ", currency=";
    print::text(out, currency_);
    out << ", reserved_byte=";
    print::hex(out, reserved_byte_.data(), reserved_byte_.size());
    out << ", reserved_4=";
    print::hex(out, reserved_4_.data(), reserved_4_.size());
    out << ", previous_close_price=";
    out << previous_close_price_;
    out << '}';
}

bool SymbolDirectoryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SymbolDirectoryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SymbolDirectoryMessage::operator==(const SymbolDirectoryMessage& other) const {
    return nanosecond_ == other.nanosecond_
        && instrument_id_ == other.instrument_id_
        && reserved_a_ == other.reserved_a_
        && reserved_b_ == other.reserved_b_
        && symbol_status_ == other.symbol_status_
        && isin_ == other.isin_
        && sedol_ == other.sedol_
        && segment_ == other.segment_
        && underlying_ == other.underlying_
        && currency_ == other.currency_
        && reserved_byte_ == other.reserved_byte_
        && reserved_4_ == other.reserved_4_
        && previous_close_price_ == other.previous_close_price_;
}

bool SymbolDirectoryMessage::operator!=(const SymbolDirectoryMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::millennium::level2::mitch::v11_9
