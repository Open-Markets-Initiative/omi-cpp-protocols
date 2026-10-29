#include "CrossCorrectionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

CrossCorrectionMessage::CrossCorrectionMessage(std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint32_t cross_id, std::uint32_t volume)
  : source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), cross_id_(cross_id), volume_(volume) {}

std::uint32_t CrossCorrectionMessage::source_time_ns() const { return source_time_ns_; }
void CrossCorrectionMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t CrossCorrectionMessage::symbol_index() const { return symbol_index_; }
void CrossCorrectionMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t CrossCorrectionMessage::symbol_seq_num() const { return symbol_seq_num_; }
void CrossCorrectionMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint32_t CrossCorrectionMessage::cross_id() const { return cross_id_; }
void CrossCorrectionMessage::set_cross_id(std::uint32_t value) { cross_id_ = value; }

std::uint32_t CrossCorrectionMessage::volume() const { return volume_; }
void CrossCorrectionMessage::set_volume(std::uint32_t value) { volume_ = value; }

MessageCode CrossCorrectionMessage::type() const { return message_type; }

std::string_view CrossCorrectionMessage::name() const { return "Cross Correction Message"; }

std::size_t CrossCorrectionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CrossCorrectionMessage", wire_size, length);

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    cross_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t CrossCorrectionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CrossCorrectionMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(cross_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(volume_));
    offset += 4;

    return offset;
}

std::size_t CrossCorrectionMessage::encoded_size() const {
    return wire_size;
}

void CrossCorrectionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> CrossCorrectionMessage::clone() const {
    return std::make_unique<CrossCorrectionMessage>(*this);
}

void CrossCorrectionMessage::print(std::ostream& out) const {
    out << "CrossCorrectionMessage{";
    out << "source_time_ns=";
    out << source_time_ns_;
    out << ", symbol_index=";
    out << symbol_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", cross_id=";
    out << cross_id_;
    out << ", volume=";
    out << volume_;
    out << '}';
}

bool CrossCorrectionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const CrossCorrectionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool CrossCorrectionMessage::operator==(const CrossCorrectionMessage& other) const {
    return source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && cross_id_ == other.cross_id_
        && volume_ == other.volume_;
}

bool CrossCorrectionMessage::operator!=(const CrossCorrectionMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
