#include "OptionsSeriesRfqMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

OptionsSeriesRfqMessage::OptionsSeriesRfqMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, RfqSide rfq_side, Type type_field, Capacity capacity, std::uint32_t total_quantity, std::int32_t working_price, std::uint32_t participant, std::uint64_t auction_id, RfqStatus rfq_status)
  : source_time_(source_time), source_time_ns_(source_time_ns), series_index_(series_index), series_seq_num_(series_seq_num), rfq_side_(rfq_side), type_field_(type_field), capacity_(capacity), total_quantity_(total_quantity), working_price_(working_price), participant_(participant), auction_id_(auction_id), rfq_status_(rfq_status) {}

std::uint32_t OptionsSeriesRfqMessage::source_time() const { return source_time_; }
void OptionsSeriesRfqMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t OptionsSeriesRfqMessage::source_time_ns() const { return source_time_ns_; }
void OptionsSeriesRfqMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t OptionsSeriesRfqMessage::series_index() const { return series_index_; }
void OptionsSeriesRfqMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

std::uint32_t OptionsSeriesRfqMessage::series_seq_num() const { return series_seq_num_; }
void OptionsSeriesRfqMessage::set_series_seq_num(std::uint32_t value) { series_seq_num_ = value; }

RfqSide OptionsSeriesRfqMessage::rfq_side() const { return rfq_side_; }
void OptionsSeriesRfqMessage::set_rfq_side(RfqSide value) { rfq_side_ = value; }

Type OptionsSeriesRfqMessage::type_field() const { return type_field_; }
void OptionsSeriesRfqMessage::set_type_field(Type value) { type_field_ = value; }

Capacity OptionsSeriesRfqMessage::capacity() const { return capacity_; }
void OptionsSeriesRfqMessage::set_capacity(Capacity value) { capacity_ = value; }

std::uint32_t OptionsSeriesRfqMessage::total_quantity() const { return total_quantity_; }
void OptionsSeriesRfqMessage::set_total_quantity(std::uint32_t value) { total_quantity_ = value; }

std::int32_t OptionsSeriesRfqMessage::working_price() const { return working_price_; }
void OptionsSeriesRfqMessage::set_working_price(std::int32_t value) { working_price_ = value; }

std::uint32_t OptionsSeriesRfqMessage::participant() const { return participant_; }
void OptionsSeriesRfqMessage::set_participant(std::uint32_t value) { participant_ = value; }

std::uint64_t OptionsSeriesRfqMessage::auction_id() const { return auction_id_; }
void OptionsSeriesRfqMessage::set_auction_id(std::uint64_t value) { auction_id_ = value; }

RfqStatus OptionsSeriesRfqMessage::rfq_status() const { return rfq_status_; }
void OptionsSeriesRfqMessage::set_rfq_status(RfqStatus value) { rfq_status_ = value; }

MessageCode OptionsSeriesRfqMessage::type() const { return message_type; }

std::string_view OptionsSeriesRfqMessage::name() const { return "Options Series Rfq Message"; }

std::size_t OptionsSeriesRfqMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OptionsSeriesRfqMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    rfq_side_ = static_cast<RfqSide>(wire::read_char(data + offset));
    offset += 1;

    type_field_ = static_cast<Type>(wire::read_char(data + offset));
    offset += 1;

    capacity_ = static_cast<Capacity>(wire::read_char(data + offset));
    offset += 1;

    total_quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    working_price_ = wire::read_i32_le(data + offset);
    offset += 4;

    participant_ = wire::read_u32_le(data + offset);
    offset += 4;

    auction_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    rfq_status_ = static_cast<RfqStatus>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t OptionsSeriesRfqMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionsSeriesRfqMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_seq_num_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(rfq_side_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(type_field_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(capacity_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(total_quantity_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(working_price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(participant_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(auction_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(rfq_status_));
    offset += 1;

    return offset;
}

std::size_t OptionsSeriesRfqMessage::encoded_size() const {
    return wire_size;
}

void OptionsSeriesRfqMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OptionsSeriesRfqMessage::clone() const {
    return std::make_unique<OptionsSeriesRfqMessage>(*this);
}

void OptionsSeriesRfqMessage::print(std::ostream& out) const {
    out << "OptionsSeriesRfqMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
    out << ", series_index=";
    out << series_index_;
    out << ", series_seq_num=";
    out << series_seq_num_;
    out << ", rfq_side=";
    out << rfq_side_;
    out << ", type_field=";
    out << type_field_;
    out << ", capacity=";
    out << capacity_;
    out << ", total_quantity=";
    out << total_quantity_;
    out << ", working_price=";
    out << working_price_;
    out << ", participant=";
    out << participant_;
    out << ", auction_id=";
    out << auction_id_;
    out << ", rfq_status=";
    out << rfq_status_;
    out << '}';
}

bool OptionsSeriesRfqMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OptionsSeriesRfqMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OptionsSeriesRfqMessage::operator==(const OptionsSeriesRfqMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && series_index_ == other.series_index_
        && series_seq_num_ == other.series_seq_num_
        && rfq_side_ == other.rfq_side_
        && type_field_ == other.type_field_
        && capacity_ == other.capacity_
        && total_quantity_ == other.total_quantity_
        && working_price_ == other.working_price_
        && participant_ == other.participant_
        && auction_id_ == other.auction_id_
        && rfq_status_ == other.rfq_status_;
}

bool OptionsSeriesRfqMessage::operator!=(const OptionsSeriesRfqMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
