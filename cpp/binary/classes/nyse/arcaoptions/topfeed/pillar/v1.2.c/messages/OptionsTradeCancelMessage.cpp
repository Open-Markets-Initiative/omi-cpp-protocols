#include "OptionsTradeCancelMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

OptionsTradeCancelMessage::OptionsTradeCancelMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, std::uint32_t original_trade_id)
  : source_time_(source_time), source_time_ns_(source_time_ns), series_index_(series_index), series_seq_num_(series_seq_num), original_trade_id_(original_trade_id) {}

std::uint32_t OptionsTradeCancelMessage::source_time() const { return source_time_; }
void OptionsTradeCancelMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t OptionsTradeCancelMessage::source_time_ns() const { return source_time_ns_; }
void OptionsTradeCancelMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t OptionsTradeCancelMessage::series_index() const { return series_index_; }
void OptionsTradeCancelMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

std::uint32_t OptionsTradeCancelMessage::series_seq_num() const { return series_seq_num_; }
void OptionsTradeCancelMessage::set_series_seq_num(std::uint32_t value) { series_seq_num_ = value; }

std::uint32_t OptionsTradeCancelMessage::original_trade_id() const { return original_trade_id_; }
void OptionsTradeCancelMessage::set_original_trade_id(std::uint32_t value) { original_trade_id_ = value; }

MessageCode OptionsTradeCancelMessage::type() const { return message_type; }

std::string_view OptionsTradeCancelMessage::name() const { return "Options Trade Cancel Message"; }

std::size_t OptionsTradeCancelMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OptionsTradeCancelMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    original_trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t OptionsTradeCancelMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionsTradeCancelMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_seq_num_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(original_trade_id_));
    offset += 4;

    return offset;
}

std::size_t OptionsTradeCancelMessage::encoded_size() const {
    return wire_size;
}

void OptionsTradeCancelMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OptionsTradeCancelMessage::clone() const {
    return std::make_unique<OptionsTradeCancelMessage>(*this);
}

void OptionsTradeCancelMessage::print(std::ostream& out) const {
    out << "OptionsTradeCancelMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
    out << ", series_index=";
    out << series_index_;
    out << ", series_seq_num=";
    out << series_seq_num_;
    out << ", original_trade_id=";
    out << original_trade_id_;
    out << '}';
}

bool OptionsTradeCancelMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OptionsTradeCancelMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OptionsTradeCancelMessage::operator==(const OptionsTradeCancelMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && series_index_ == other.series_index_
        && series_seq_num_ == other.series_seq_num_
        && original_trade_id_ == other.original_trade_id_;
}

bool OptionsTradeCancelMessage::operator!=(const OptionsTradeCancelMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
