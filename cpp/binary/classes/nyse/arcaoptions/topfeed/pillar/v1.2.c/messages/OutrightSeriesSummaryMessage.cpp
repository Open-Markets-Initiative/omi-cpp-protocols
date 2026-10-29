#include "OutrightSeriesSummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

OutrightSeriesSummaryMessage::OutrightSeriesSummaryMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t series_index, std::int32_t high_price, std::int32_t low_price, std::int32_t open, std::int32_t close, std::uint32_t total_volume)
  : source_time_(source_time), source_time_ns_(source_time_ns), series_index_(series_index), high_price_(high_price), low_price_(low_price), open_(open), close_(close), total_volume_(total_volume) {}

std::uint32_t OutrightSeriesSummaryMessage::source_time() const { return source_time_; }
void OutrightSeriesSummaryMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t OutrightSeriesSummaryMessage::source_time_ns() const { return source_time_ns_; }
void OutrightSeriesSummaryMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t OutrightSeriesSummaryMessage::series_index() const { return series_index_; }
void OutrightSeriesSummaryMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

std::int32_t OutrightSeriesSummaryMessage::high_price() const { return high_price_; }
void OutrightSeriesSummaryMessage::set_high_price(std::int32_t value) { high_price_ = value; }

std::int32_t OutrightSeriesSummaryMessage::low_price() const { return low_price_; }
void OutrightSeriesSummaryMessage::set_low_price(std::int32_t value) { low_price_ = value; }

std::int32_t OutrightSeriesSummaryMessage::open() const { return open_; }
void OutrightSeriesSummaryMessage::set_open(std::int32_t value) { open_ = value; }

std::int32_t OutrightSeriesSummaryMessage::close() const { return close_; }
void OutrightSeriesSummaryMessage::set_close(std::int32_t value) { close_ = value; }

std::uint32_t OutrightSeriesSummaryMessage::total_volume() const { return total_volume_; }
void OutrightSeriesSummaryMessage::set_total_volume(std::uint32_t value) { total_volume_ = value; }

MessageCode OutrightSeriesSummaryMessage::type() const { return message_type; }

std::string_view OutrightSeriesSummaryMessage::name() const { return "Outright Series Summary Message"; }

std::size_t OutrightSeriesSummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OutrightSeriesSummaryMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    high_price_ = wire::read_i32_le(data + offset);
    offset += 4;

    low_price_ = wire::read_i32_le(data + offset);
    offset += 4;

    open_ = wire::read_i32_le(data + offset);
    offset += 4;

    close_ = wire::read_i32_le(data + offset);
    offset += 4;

    total_volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t OutrightSeriesSummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OutrightSeriesSummaryMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_index_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(high_price_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(low_price_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(open_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(close_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(total_volume_));
    offset += 4;

    return offset;
}

std::size_t OutrightSeriesSummaryMessage::encoded_size() const {
    return wire_size;
}

void OutrightSeriesSummaryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OutrightSeriesSummaryMessage::clone() const {
    return std::make_unique<OutrightSeriesSummaryMessage>(*this);
}

void OutrightSeriesSummaryMessage::print(std::ostream& out) const {
    out << "OutrightSeriesSummaryMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
    out << ", series_index=";
    out << series_index_;
    out << ", high_price=";
    out << high_price_;
    out << ", low_price=";
    out << low_price_;
    out << ", open=";
    out << open_;
    out << ", close=";
    out << close_;
    out << ", total_volume=";
    out << total_volume_;
    out << '}';
}

bool OutrightSeriesSummaryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OutrightSeriesSummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OutrightSeriesSummaryMessage::operator==(const OutrightSeriesSummaryMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && series_index_ == other.series_index_
        && high_price_ == other.high_price_
        && low_price_ == other.low_price_
        && open_ == other.open_
        && close_ == other.close_
        && total_volume_ == other.total_volume_;
}

bool OutrightSeriesSummaryMessage::operator!=(const OutrightSeriesSummaryMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
