#include "OptionsDeleteOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

OptionsDeleteOrderMessage::OptionsDeleteOrderMessage(std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, std::uint64_t order_id, const std::array<std::byte, 1>& reserved_1)
  : source_time_ns_(source_time_ns), series_index_(series_index), series_seq_num_(series_seq_num), order_id_(order_id), reserved_1_(reserved_1) {}

std::uint32_t OptionsDeleteOrderMessage::source_time_ns() const { return source_time_ns_; }
void OptionsDeleteOrderMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t OptionsDeleteOrderMessage::series_index() const { return series_index_; }
void OptionsDeleteOrderMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

std::uint32_t OptionsDeleteOrderMessage::series_seq_num() const { return series_seq_num_; }
void OptionsDeleteOrderMessage::set_series_seq_num(std::uint32_t value) { series_seq_num_ = value; }

std::uint64_t OptionsDeleteOrderMessage::order_id() const { return order_id_; }
void OptionsDeleteOrderMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

const std::array<std::byte, 1>& OptionsDeleteOrderMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& OptionsDeleteOrderMessage::reserved_1() { return reserved_1_; }
void OptionsDeleteOrderMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

MessageCode OptionsDeleteOrderMessage::type() const { return message_type; }

std::string_view OptionsDeleteOrderMessage::name() const { return "Options Delete Order Message"; }

std::size_t OptionsDeleteOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OptionsDeleteOrderMessage", wire_size, length);

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t OptionsDeleteOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionsDeleteOrderMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_seq_num_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t OptionsDeleteOrderMessage::encoded_size() const {
    return wire_size;
}

void OptionsDeleteOrderMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OptionsDeleteOrderMessage::clone() const {
    return std::make_unique<OptionsDeleteOrderMessage>(*this);
}

void OptionsDeleteOrderMessage::print(std::ostream& out) const {
    out << "OptionsDeleteOrderMessage{";
    out << "source_time_ns=";
    out << source_time_ns_;
    out << ", series_index=";
    out << series_index_;
    out << ", series_seq_num=";
    out << series_seq_num_;
    out << ", order_id=";
    out << order_id_;
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << '}';
}

bool OptionsDeleteOrderMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OptionsDeleteOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OptionsDeleteOrderMessage::operator==(const OptionsDeleteOrderMessage& other) const {
    return source_time_ns_ == other.source_time_ns_
        && series_index_ == other.series_index_
        && series_seq_num_ == other.series_seq_num_
        && order_id_ == other.order_id_
        && reserved_1_ == other.reserved_1_;
}

bool OptionsDeleteOrderMessage::operator!=(const OptionsDeleteOrderMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
