#include "SymbolClearMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

SymbolClearMessage::SymbolClearMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t symbol_id)
  : nanoseconds_(nanoseconds), symbol_id_(symbol_id) {}

std::chrono::nanoseconds SymbolClearMessage::nanoseconds() const { return nanoseconds_; }
void SymbolClearMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t SymbolClearMessage::symbol_id() const { return symbol_id_; }
void SymbolClearMessage::set_symbol_id(std::uint32_t value) { symbol_id_ = value; }

DataCode SymbolClearMessage::type() const { return message_type; }

std::string_view SymbolClearMessage::name() const { return "Symbol Clear Message"; }

std::size_t SymbolClearMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SymbolClearMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t SymbolClearMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SymbolClearMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_id_));
    offset += 4;

    return offset;
}

std::size_t SymbolClearMessage::encoded_size() const {
    return wire_size;
}

void SymbolClearMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> SymbolClearMessage::clone() const {
    return std::make_unique<SymbolClearMessage>(*this);
}

void SymbolClearMessage::print(std::ostream& out) const {
    out << "SymbolClearMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", symbol_id=";
    out << symbol_id_;
    out << '}';
}

bool SymbolClearMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const SymbolClearMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SymbolClearMessage::operator==(const SymbolClearMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && symbol_id_ == other.symbol_id_;
}

bool SymbolClearMessage::operator!=(const SymbolClearMessage& other) const {
    return !(*this == other);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
