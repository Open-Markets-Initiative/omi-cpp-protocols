#include "OptionsStatusMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

OptionsStatusMessage::OptionsStatusMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, SeriesStatus series_status, MarketState market_state, HaltCondition halt_condition)
  : source_time_(source_time), source_time_ns_(source_time_ns), series_index_(series_index), series_seq_num_(series_seq_num), series_status_(series_status), market_state_(market_state), halt_condition_(halt_condition) {}

std::uint32_t OptionsStatusMessage::source_time() const { return source_time_; }
void OptionsStatusMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t OptionsStatusMessage::source_time_ns() const { return source_time_ns_; }
void OptionsStatusMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t OptionsStatusMessage::series_index() const { return series_index_; }
void OptionsStatusMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

std::uint32_t OptionsStatusMessage::series_seq_num() const { return series_seq_num_; }
void OptionsStatusMessage::set_series_seq_num(std::uint32_t value) { series_seq_num_ = value; }

SeriesStatus OptionsStatusMessage::series_status() const { return series_status_; }
void OptionsStatusMessage::set_series_status(SeriesStatus value) { series_status_ = value; }

MarketState OptionsStatusMessage::market_state() const { return market_state_; }
void OptionsStatusMessage::set_market_state(MarketState value) { market_state_ = value; }

HaltCondition OptionsStatusMessage::halt_condition() const { return halt_condition_; }
void OptionsStatusMessage::set_halt_condition(HaltCondition value) { halt_condition_ = value; }

MessageCode OptionsStatusMessage::type() const { return message_type; }

std::string_view OptionsStatusMessage::name() const { return "Options Status Message"; }

std::size_t OptionsStatusMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OptionsStatusMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_status_ = static_cast<SeriesStatus>(wire::read_char(data + offset));
    offset += 1;

    market_state_ = static_cast<MarketState>(wire::read_char(data + offset));
    offset += 1;

    halt_condition_ = static_cast<HaltCondition>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t OptionsStatusMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionsStatusMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_seq_num_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(series_status_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(market_state_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(halt_condition_));
    offset += 1;

    return offset;
}

std::size_t OptionsStatusMessage::encoded_size() const {
    return wire_size;
}

void OptionsStatusMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OptionsStatusMessage::clone() const {
    return std::make_unique<OptionsStatusMessage>(*this);
}

void OptionsStatusMessage::print(std::ostream& out) const {
    out << "OptionsStatusMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
    out << ", series_index=";
    out << series_index_;
    out << ", series_seq_num=";
    out << series_seq_num_;
    out << ", series_status=";
    out << series_status_;
    out << ", market_state=";
    out << market_state_;
    out << ", halt_condition=";
    out << halt_condition_;
    out << '}';
}

bool OptionsStatusMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OptionsStatusMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OptionsStatusMessage::operator==(const OptionsStatusMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && series_index_ == other.series_index_
        && series_seq_num_ == other.series_seq_num_
        && series_status_ == other.series_status_
        && market_state_ == other.market_state_
        && halt_condition_ == other.halt_condition_;
}

bool OptionsStatusMessage::operator!=(const OptionsStatusMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
