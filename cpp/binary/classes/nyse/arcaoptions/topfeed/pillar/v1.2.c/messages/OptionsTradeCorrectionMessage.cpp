#include "OptionsTradeCorrectionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

OptionsTradeCorrectionMessage::OptionsTradeCorrectionMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, std::uint32_t original_trade_id, std::uint32_t trade_id, std::int32_t price, std::uint32_t volume, const CorrectionCondition& correction_condition)
  : source_time_(source_time), source_time_ns_(source_time_ns), series_index_(series_index), series_seq_num_(series_seq_num), original_trade_id_(original_trade_id), trade_id_(trade_id), price_(price), volume_(volume), correction_condition_(correction_condition) {}

std::uint32_t OptionsTradeCorrectionMessage::source_time() const { return source_time_; }
void OptionsTradeCorrectionMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t OptionsTradeCorrectionMessage::source_time_ns() const { return source_time_ns_; }
void OptionsTradeCorrectionMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t OptionsTradeCorrectionMessage::series_index() const { return series_index_; }
void OptionsTradeCorrectionMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

std::uint32_t OptionsTradeCorrectionMessage::series_seq_num() const { return series_seq_num_; }
void OptionsTradeCorrectionMessage::set_series_seq_num(std::uint32_t value) { series_seq_num_ = value; }

std::uint32_t OptionsTradeCorrectionMessage::original_trade_id() const { return original_trade_id_; }
void OptionsTradeCorrectionMessage::set_original_trade_id(std::uint32_t value) { original_trade_id_ = value; }

std::uint32_t OptionsTradeCorrectionMessage::trade_id() const { return trade_id_; }
void OptionsTradeCorrectionMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::int32_t OptionsTradeCorrectionMessage::price() const { return price_; }
void OptionsTradeCorrectionMessage::set_price(std::int32_t value) { price_ = value; }

std::uint32_t OptionsTradeCorrectionMessage::volume() const { return volume_; }
void OptionsTradeCorrectionMessage::set_volume(std::uint32_t value) { volume_ = value; }

const CorrectionCondition& OptionsTradeCorrectionMessage::correction_condition() const { return correction_condition_; }
CorrectionCondition& OptionsTradeCorrectionMessage::correction_condition() { return correction_condition_; }
void OptionsTradeCorrectionMessage::set_correction_condition(const CorrectionCondition& value) { correction_condition_ = value; }

MessageCode OptionsTradeCorrectionMessage::type() const { return message_type; }

std::string_view OptionsTradeCorrectionMessage::name() const { return "Options Trade Correction Message"; }

std::size_t OptionsTradeCorrectionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OptionsTradeCorrectionMessage", wire_size, length);

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

    trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_ = wire::read_i32_le(data + offset);
    offset += 4;

    volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    offset += correction_condition_.decode(data + offset, length - offset);

    return offset;
}

std::size_t OptionsTradeCorrectionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionsTradeCorrectionMessage", wire_size, capacity);

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

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_id_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(volume_));
    offset += 4;

    offset += correction_condition_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t OptionsTradeCorrectionMessage::encoded_size() const {
    return wire_size;
}

void OptionsTradeCorrectionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OptionsTradeCorrectionMessage::clone() const {
    return std::make_unique<OptionsTradeCorrectionMessage>(*this);
}

void OptionsTradeCorrectionMessage::print(std::ostream& out) const {
    out << "OptionsTradeCorrectionMessage{";
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
    out << ", trade_id=";
    out << trade_id_;
    out << ", price=";
    out << price_;
    out << ", volume=";
    out << volume_;
    out << ", correction_condition=";
    correction_condition_.print(out);
    out << '}';
}

bool OptionsTradeCorrectionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OptionsTradeCorrectionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OptionsTradeCorrectionMessage::operator==(const OptionsTradeCorrectionMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && series_index_ == other.series_index_
        && series_seq_num_ == other.series_seq_num_
        && original_trade_id_ == other.original_trade_id_
        && trade_id_ == other.trade_id_
        && price_ == other.price_
        && volume_ == other.volume_
        && correction_condition_ == other.correction_condition_;
}

bool OptionsTradeCorrectionMessage::operator!=(const OptionsTradeCorrectionMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
