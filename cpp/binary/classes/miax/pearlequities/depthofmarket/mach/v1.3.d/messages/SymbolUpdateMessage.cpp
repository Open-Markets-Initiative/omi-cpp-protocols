#include "SymbolUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

SymbolUpdateMessage::SymbolUpdateMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t symbol_id, const std::string& ticker_symbol, const std::array<std::byte, 1>& reserved_1, TestSecurityIndicator test_security_indicator, const std::array<std::byte, 1>& second_reserved_1, std::uint16_t lot_size, const std::string& opening_time, const std::string& closing_time, PrimaryMarketCode primary_market_code)
  : nanoseconds_(nanoseconds), symbol_id_(symbol_id), ticker_symbol_(ticker_symbol), reserved_1_(reserved_1), test_security_indicator_(test_security_indicator), second_reserved_1_(second_reserved_1), lot_size_(lot_size), opening_time_(opening_time), closing_time_(closing_time), primary_market_code_(primary_market_code) {}

std::chrono::nanoseconds SymbolUpdateMessage::nanoseconds() const { return nanoseconds_; }
void SymbolUpdateMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t SymbolUpdateMessage::symbol_id() const { return symbol_id_; }
void SymbolUpdateMessage::set_symbol_id(std::uint32_t value) { symbol_id_ = value; }

const std::string& SymbolUpdateMessage::ticker_symbol() const { return ticker_symbol_; }
std::string& SymbolUpdateMessage::ticker_symbol() { return ticker_symbol_; }
void SymbolUpdateMessage::set_ticker_symbol(const std::string& value) { ticker_symbol_ = value; }

const std::array<std::byte, 1>& SymbolUpdateMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& SymbolUpdateMessage::reserved_1() { return reserved_1_; }
void SymbolUpdateMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

TestSecurityIndicator SymbolUpdateMessage::test_security_indicator() const { return test_security_indicator_; }
void SymbolUpdateMessage::set_test_security_indicator(TestSecurityIndicator value) { test_security_indicator_ = value; }

const std::array<std::byte, 1>& SymbolUpdateMessage::second_reserved_1() const { return second_reserved_1_; }
std::array<std::byte, 1>& SymbolUpdateMessage::second_reserved_1() { return second_reserved_1_; }
void SymbolUpdateMessage::set_second_reserved_1(const std::array<std::byte, 1>& value) { second_reserved_1_ = value; }

std::uint16_t SymbolUpdateMessage::lot_size() const { return lot_size_; }
void SymbolUpdateMessage::set_lot_size(std::uint16_t value) { lot_size_ = value; }

const std::string& SymbolUpdateMessage::opening_time() const { return opening_time_; }
std::string& SymbolUpdateMessage::opening_time() { return opening_time_; }
void SymbolUpdateMessage::set_opening_time(const std::string& value) { opening_time_ = value; }

const std::string& SymbolUpdateMessage::closing_time() const { return closing_time_; }
std::string& SymbolUpdateMessage::closing_time() { return closing_time_; }
void SymbolUpdateMessage::set_closing_time(const std::string& value) { closing_time_ = value; }

PrimaryMarketCode SymbolUpdateMessage::primary_market_code() const { return primary_market_code_; }
void SymbolUpdateMessage::set_primary_market_code(PrimaryMarketCode value) { primary_market_code_ = value; }

DataCode SymbolUpdateMessage::type() const { return message_type; }

std::string_view SymbolUpdateMessage::name() const { return "Symbol Update Message"; }

std::size_t SymbolUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SymbolUpdateMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    ticker_symbol_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    test_security_indicator_ = static_cast<TestSecurityIndicator>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, second_reserved_1_.data(), 1);
    offset += 1;

    lot_size_ = wire::read_u16_le(data + offset);
    offset += 2;

    opening_time_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    closing_time_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    primary_market_code_ = static_cast<PrimaryMarketCode>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SymbolUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SymbolUpdateMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_id_));
    offset += 4;

    wire::write_text(data + offset, 11, ' ', ticker_symbol_);
    offset += 11;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(test_security_indicator_));
    offset += 1;

    wire::write_bytes(data + offset, second_reserved_1_.data(), 1);
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(lot_size_));
    offset += 2;

    wire::write_text(data + offset, 8, ' ', opening_time_);
    offset += 8;

    wire::write_text(data + offset, 8, ' ', closing_time_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(primary_market_code_));
    offset += 1;

    return offset;
}

std::size_t SymbolUpdateMessage::encoded_size() const {
    return wire_size;
}

void SymbolUpdateMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> SymbolUpdateMessage::clone() const {
    return std::make_unique<SymbolUpdateMessage>(*this);
}

void SymbolUpdateMessage::print(std::ostream& out) const {
    out << "SymbolUpdateMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", symbol_id=";
    out << symbol_id_;
    out << ", ticker_symbol=";
    print::text(out, ticker_symbol_);
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", test_security_indicator=";
    out << test_security_indicator_;
    out << ", second_reserved_1=";
    print::hex(out, second_reserved_1_.data(), second_reserved_1_.size());
    out << ", lot_size=";
    out << lot_size_;
    out << ", opening_time=";
    print::text(out, opening_time_);
    out << ", closing_time=";
    print::text(out, closing_time_);
    out << ", primary_market_code=";
    out << primary_market_code_;
    out << '}';
}

bool SymbolUpdateMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const SymbolUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SymbolUpdateMessage::operator==(const SymbolUpdateMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && symbol_id_ == other.symbol_id_
        && ticker_symbol_ == other.ticker_symbol_
        && reserved_1_ == other.reserved_1_
        && test_security_indicator_ == other.test_security_indicator_
        && second_reserved_1_ == other.second_reserved_1_
        && lot_size_ == other.lot_size_
        && opening_time_ == other.opening_time_
        && closing_time_ == other.closing_time_
        && primary_market_code_ == other.primary_market_code_;
}

bool SymbolUpdateMessage::operator!=(const SymbolUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
