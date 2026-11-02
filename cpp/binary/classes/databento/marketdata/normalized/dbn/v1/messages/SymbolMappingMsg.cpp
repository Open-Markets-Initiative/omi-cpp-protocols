#include "SymbolMappingMsg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

SymbolMappingMsg::SymbolMappingMsg(const std::string& stype_in_symbol, const std::string& stype_out_symbol, const std::array<std::byte, 4>& dummy_4, std::optional<std::chrono::nanoseconds> start_ts, std::optional<std::chrono::nanoseconds> end_ts)
  : stype_in_symbol_(stype_in_symbol), stype_out_symbol_(stype_out_symbol), dummy_4_(dummy_4), start_ts_(start_ts), end_ts_(end_ts) {}

const std::string& SymbolMappingMsg::stype_in_symbol() const { return stype_in_symbol_; }
std::string& SymbolMappingMsg::stype_in_symbol() { return stype_in_symbol_; }
void SymbolMappingMsg::set_stype_in_symbol(const std::string& value) { stype_in_symbol_ = value; }

const std::string& SymbolMappingMsg::stype_out_symbol() const { return stype_out_symbol_; }
std::string& SymbolMappingMsg::stype_out_symbol() { return stype_out_symbol_; }
void SymbolMappingMsg::set_stype_out_symbol(const std::string& value) { stype_out_symbol_ = value; }

const std::array<std::byte, 4>& SymbolMappingMsg::dummy_4() const { return dummy_4_; }
std::array<std::byte, 4>& SymbolMappingMsg::dummy_4() { return dummy_4_; }
void SymbolMappingMsg::set_dummy_4(const std::array<std::byte, 4>& value) { dummy_4_ = value; }

std::optional<std::chrono::nanoseconds> SymbolMappingMsg::start_ts() const { return start_ts_; }
void SymbolMappingMsg::set_start_ts(std::optional<std::chrono::nanoseconds> value) { start_ts_ = value; }

std::optional<std::chrono::nanoseconds> SymbolMappingMsg::end_ts() const { return end_ts_; }
void SymbolMappingMsg::set_end_ts(std::optional<std::chrono::nanoseconds> value) { end_ts_ = value; }

MessageCode SymbolMappingMsg::type() const { return message_type; }

std::string_view SymbolMappingMsg::name() const { return "Symbol Mapping Msg"; }

std::size_t SymbolMappingMsg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SymbolMappingMsg", wire_size, length);

    stype_in_symbol_ = wire::read_text(data + offset, 22, '\0');
    offset += 22;

    stype_out_symbol_ = wire::read_text(data + offset, 22, '\0');
    offset += 22;

    wire::read_bytes(data + offset, dummy_4_.data(), 4);
    offset += 4;

    start_ts_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    end_ts_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    return offset;
}

std::size_t SymbolMappingMsg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SymbolMappingMsg", wire_size, capacity);

    wire::write_text(data + offset, 22, '\0', stype_in_symbol_);
    offset += 22;

    wire::write_text(data + offset, 22, '\0', stype_out_symbol_);
    offset += 22;

    wire::write_bytes(data + offset, dummy_4_.data(), 4);
    offset += 4;

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
    out << "stype_in_symbol=";
    print::text(out, stype_in_symbol_);
    out << ", stype_out_symbol=";
    print::text(out, stype_out_symbol_);
    out << ", dummy_4=";
    print::hex(out, dummy_4_.data(), dummy_4_.size());
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
    return stype_in_symbol_ == other.stype_in_symbol_
        && stype_out_symbol_ == other.stype_out_symbol_
        && dummy_4_ == other.dummy_4_
        && start_ts_ == other.start_ts_
        && end_ts_ == other.end_ts_;
}

bool SymbolMappingMsg::operator!=(const SymbolMappingMsg& other) const {
    return !(*this == other);
}

} // namespace databento::marketdata::normalized::dbn::v1
