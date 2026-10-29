#include "SymbolIndexMappingRequestMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f {

SymbolIndexMappingRequestMessage::SymbolIndexMappingRequestMessage(std::uint32_t symbol_index, const std::string& source_id, std::uint8_t product_id, std::uint8_t channel_id, std::uint8_t retransmit_method)
  : symbol_index_(symbol_index), source_id_(source_id), product_id_(product_id), channel_id_(channel_id), retransmit_method_(retransmit_method) {}

std::uint32_t SymbolIndexMappingRequestMessage::symbol_index() const { return symbol_index_; }
void SymbolIndexMappingRequestMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

const std::string& SymbolIndexMappingRequestMessage::source_id() const { return source_id_; }
std::string& SymbolIndexMappingRequestMessage::source_id() { return source_id_; }
void SymbolIndexMappingRequestMessage::set_source_id(const std::string& value) { source_id_ = value; }

std::uint8_t SymbolIndexMappingRequestMessage::product_id() const { return product_id_; }
void SymbolIndexMappingRequestMessage::set_product_id(std::uint8_t value) { product_id_ = value; }

std::uint8_t SymbolIndexMappingRequestMessage::channel_id() const { return channel_id_; }
void SymbolIndexMappingRequestMessage::set_channel_id(std::uint8_t value) { channel_id_ = value; }

std::uint8_t SymbolIndexMappingRequestMessage::retransmit_method() const { return retransmit_method_; }
void SymbolIndexMappingRequestMessage::set_retransmit_method(std::uint8_t value) { retransmit_method_ = value; }

MessageCode SymbolIndexMappingRequestMessage::type() const { return message_type; }

std::string_view SymbolIndexMappingRequestMessage::name() const { return "Symbol Index Mapping Request Message"; }

std::size_t SymbolIndexMappingRequestMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SymbolIndexMappingRequestMessage", wire_size, length);

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_id_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    product_id_ = wire::read_u8(data + offset);
    offset += 1;

    channel_id_ = wire::read_u8(data + offset);
    offset += 1;

    retransmit_method_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t SymbolIndexMappingRequestMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SymbolIndexMappingRequestMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_text(data + offset, 10, '\0', source_id_);
    offset += 10;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(product_id_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(channel_id_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(retransmit_method_));
    offset += 1;

    return offset;
}

std::size_t SymbolIndexMappingRequestMessage::encoded_size() const {
    return wire_size;
}

void SymbolIndexMappingRequestMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SymbolIndexMappingRequestMessage::clone() const {
    return std::make_unique<SymbolIndexMappingRequestMessage>(*this);
}

void SymbolIndexMappingRequestMessage::print(std::ostream& out) const {
    out << "SymbolIndexMappingRequestMessage{";
    out << "symbol_index=";
    out << symbol_index_;
    out << ", source_id=";
    print::text(out, source_id_);
    out << ", product_id=";
    out << static_cast<int>(product_id_);
    out << ", channel_id=";
    out << static_cast<int>(channel_id_);
    out << ", retransmit_method=";
    out << static_cast<int>(retransmit_method_);
    out << '}';
}

bool SymbolIndexMappingRequestMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SymbolIndexMappingRequestMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SymbolIndexMappingRequestMessage::operator==(const SymbolIndexMappingRequestMessage& other) const {
    return symbol_index_ == other.symbol_index_
        && source_id_ == other.source_id_
        && product_id_ == other.product_id_
        && channel_id_ == other.channel_id_
        && retransmit_method_ == other.retransmit_method_;
}

bool SymbolIndexMappingRequestMessage::operator!=(const SymbolIndexMappingRequestMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f
