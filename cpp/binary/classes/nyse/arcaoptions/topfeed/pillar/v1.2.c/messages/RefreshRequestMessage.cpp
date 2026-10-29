#include "RefreshRequestMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

RefreshRequestMessage::RefreshRequestMessage(std::uint32_t symbol_index, const std::string& source_id, std::uint8_t product_id, std::uint8_t channel_id)
  : symbol_index_(symbol_index), source_id_(source_id), product_id_(product_id), channel_id_(channel_id) {}

std::uint32_t RefreshRequestMessage::symbol_index() const { return symbol_index_; }
void RefreshRequestMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

const std::string& RefreshRequestMessage::source_id() const { return source_id_; }
std::string& RefreshRequestMessage::source_id() { return source_id_; }
void RefreshRequestMessage::set_source_id(const std::string& value) { source_id_ = value; }

std::uint8_t RefreshRequestMessage::product_id() const { return product_id_; }
void RefreshRequestMessage::set_product_id(std::uint8_t value) { product_id_ = value; }

std::uint8_t RefreshRequestMessage::channel_id() const { return channel_id_; }
void RefreshRequestMessage::set_channel_id(std::uint8_t value) { channel_id_ = value; }

MessageCode RefreshRequestMessage::type() const { return message_type; }

std::string_view RefreshRequestMessage::name() const { return "Refresh Request Message"; }

std::size_t RefreshRequestMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RefreshRequestMessage", wire_size, length);

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_id_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    product_id_ = wire::read_u8(data + offset);
    offset += 1;

    channel_id_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t RefreshRequestMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RefreshRequestMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_text(data + offset, 10, '\0', source_id_);
    offset += 10;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(product_id_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(channel_id_));
    offset += 1;

    return offset;
}

std::size_t RefreshRequestMessage::encoded_size() const {
    return wire_size;
}

void RefreshRequestMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> RefreshRequestMessage::clone() const {
    return std::make_unique<RefreshRequestMessage>(*this);
}

void RefreshRequestMessage::print(std::ostream& out) const {
    out << "RefreshRequestMessage{";
    out << "symbol_index=";
    out << symbol_index_;
    out << ", source_id=";
    print::text(out, source_id_);
    out << ", product_id=";
    out << static_cast<int>(product_id_);
    out << ", channel_id=";
    out << static_cast<int>(channel_id_);
    out << '}';
}

bool RefreshRequestMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const RefreshRequestMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RefreshRequestMessage::operator==(const RefreshRequestMessage& other) const {
    return symbol_index_ == other.symbol_index_
        && source_id_ == other.source_id_
        && product_id_ == other.product_id_
        && channel_id_ == other.channel_id_;
}

bool RefreshRequestMessage::operator!=(const RefreshRequestMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
