// Databento.MarketData.Normalized.Dbn.v2: messages/SymbolMappingMsg.cpp
#include "SymbolMappingMsg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

SymbolMappingMsg::SymbolMappingMsg(std::optional<StypeIn> stype_in, const std::string& stype_in_symbol, StypeOut stype_out, const std::string& stype_out_symbol, std::optional<std::chrono::nanoseconds> start_ts, std::optional<std::chrono::nanoseconds> end_ts)
  : stype_in_(stype_in), stype_in_symbol_(stype_in_symbol), stype_out_(stype_out), stype_out_symbol_(stype_out_symbol), start_ts_(start_ts), end_ts_(end_ts) {}

std::optional<StypeIn> SymbolMappingMsg::stype_in() const { return stype_in_; }
void SymbolMappingMsg::set_stype_in(std::optional<StypeIn> value) { stype_in_ = value; }

const std::string& SymbolMappingMsg::stype_in_symbol() const { return stype_in_symbol_; }
std::string& SymbolMappingMsg::stype_in_symbol() { return stype_in_symbol_; }
void SymbolMappingMsg::set_stype_in_symbol(const std::string& value) { stype_in_symbol_ = value; }

StypeOut SymbolMappingMsg::stype_out() const { return stype_out_; }
void SymbolMappingMsg::set_stype_out(StypeOut value) { stype_out_ = value; }

const std::string& SymbolMappingMsg::stype_out_symbol() const { return stype_out_symbol_; }
std::string& SymbolMappingMsg::stype_out_symbol() { return stype_out_symbol_; }
void SymbolMappingMsg::set_stype_out_symbol(const std::string& value) { stype_out_symbol_ = value; }

std::optional<std::chrono::nanoseconds> SymbolMappingMsg::start_ts() const { return start_ts_; }
void SymbolMappingMsg::set_start_ts(std::optional<std::chrono::nanoseconds> value) { start_ts_ = value; }

std::optional<std::chrono::nanoseconds> SymbolMappingMsg::end_ts() const { return end_ts_; }
void SymbolMappingMsg::set_end_ts(std::optional<std::chrono::nanoseconds> value) { end_ts_ = value; }

MessageCode SymbolMappingMsg::type() const { return message_type; }

std::string_view SymbolMappingMsg::name() const { return "Symbol Mapping Msg"; }

std::size_t SymbolMappingMsg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SymbolMappingMsg", wire_size, length);

    stype_in_ = wire::nullable_enum<StypeIn>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    stype_in_symbol_ = wire::read_text(data + offset, 71, '\0');
    offset += 71;

    stype_out_ = static_cast<StypeOut>(wire::read_u8(data + offset));
    offset += 1;

    stype_out_symbol_ = wire::read_text(data + offset, 71, '\0');
    offset += 71;

    start_ts_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    end_ts_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    return offset;
}

std::size_t SymbolMappingMsg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SymbolMappingMsg", wire_size, capacity);

    wire::write_u8(data + offset, stype_in_ ? static_cast<std::uint8_t>(*stype_in_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_text(data + offset, 71, '\0', stype_in_symbol_);
    offset += 71;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(stype_out_));
    offset += 1;

    wire::write_text(data + offset, 71, '\0', stype_out_symbol_);
    offset += 71;

    wire::write_u64_le(data + offset, start_ts_ ? static_cast<std::uint64_t>(start_ts_->count()) : static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    wire::write_u64_le(data + offset, end_ts_ ? static_cast<std::uint64_t>(end_ts_->count()) : static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    return offset;
}

std::size_t SymbolMappingMsg::encoded_size() const {
    return wire_size;
}

void SymbolMappingMsg::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SymbolMappingMsg::clone() const {
    return std::make_unique<SymbolMappingMsg>(*this);
}

void SymbolMappingMsg::print(std::ostream& out) const {
    out << "SymbolMappingMsg{";
    out << "stype_in=";
    print::optional(out, stype_in_);
    out << ", stype_in_symbol=";
    print::text(out, stype_in_symbol_);
    out << ", stype_out=";
    out << stype_out_;
    out << ", stype_out_symbol=";
    print::text(out, stype_out_symbol_);
    out << ", start_ts=";
    print::optional_duration(out, start_ts_);
    out << ", end_ts=";
    print::optional_duration(out, end_ts_);
    out << '}';
}

bool SymbolMappingMsg::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SymbolMappingMsg*>(&other);
    return that != nullptr && *this == *that;
}

bool SymbolMappingMsg::operator==(const SymbolMappingMsg& other) const {
    return stype_in_ == other.stype_in_
        && stype_in_symbol_ == other.stype_in_symbol_
        && stype_out_ == other.stype_out_
        && stype_out_symbol_ == other.stype_out_symbol_
        && start_ts_ == other.start_ts_
        && end_ts_ == other.end_ts_;
}

bool SymbolMappingMsg::operator!=(const SymbolMappingMsg& other) const {
    return !(*this == other);
}

} // namespace databento::marketdata::normalized::dbn::v2
