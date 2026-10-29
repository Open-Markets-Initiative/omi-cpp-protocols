#include "SymbolClearMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

SymbolClearMessage::SymbolClearMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t next_source_seq_num)
  : source_time_(source_time), source_time_ns_(source_time_ns), symbol_index_(symbol_index), next_source_seq_num_(next_source_seq_num) {}

std::uint32_t SymbolClearMessage::source_time() const { return source_time_; }
void SymbolClearMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t SymbolClearMessage::source_time_ns() const { return source_time_ns_; }
void SymbolClearMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t SymbolClearMessage::symbol_index() const { return symbol_index_; }
void SymbolClearMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t SymbolClearMessage::next_source_seq_num() const { return next_source_seq_num_; }
void SymbolClearMessage::set_next_source_seq_num(std::uint32_t value) { next_source_seq_num_ = value; }

MessageCode SymbolClearMessage::type() const { return message_type; }

std::string_view SymbolClearMessage::name() const { return "Symbol Clear Message"; }

std::size_t SymbolClearMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SymbolClearMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    next_source_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t SymbolClearMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SymbolClearMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(next_source_seq_num_));
    offset += 4;

    return offset;
}

std::size_t SymbolClearMessage::encoded_size() const {
    return wire_size;
}

void SymbolClearMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SymbolClearMessage::clone() const {
    return std::make_unique<SymbolClearMessage>(*this);
}

void SymbolClearMessage::print(std::ostream& out) const {
    out << "SymbolClearMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
    out << ", symbol_index=";
    out << symbol_index_;
    out << ", next_source_seq_num=";
    out << next_source_seq_num_;
    out << '}';
}

bool SymbolClearMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SymbolClearMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SymbolClearMessage::operator==(const SymbolClearMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && next_source_seq_num_ == other.next_source_seq_num_;
}

bool SymbolClearMessage::operator!=(const SymbolClearMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nyseequities::bbo::xdp::v2_4_g
