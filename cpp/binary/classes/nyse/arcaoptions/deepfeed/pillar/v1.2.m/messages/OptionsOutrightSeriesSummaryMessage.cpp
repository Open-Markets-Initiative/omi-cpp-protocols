#include "OptionsOutrightSeriesSummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

OptionsOutrightSeriesSummaryMessage::OptionsOutrightSeriesSummaryMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t series_index, std::int32_t high_price, std::int32_t low_price, std::int32_t open, std::int32_t close, std::uint32_t total_volume)
  : source_time_(source_time), source_time_ns_(source_time_ns), series_index_(series_index), high_price_(high_price), low_price_(low_price), open_(open), close_(close), total_volume_(total_volume) {}

std::uint32_t OptionsOutrightSeriesSummaryMessage::source_time() const { return source_time_; }
void OptionsOutrightSeriesSummaryMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t OptionsOutrightSeriesSummaryMessage::source_time_ns() const { return source_time_ns_; }
void OptionsOutrightSeriesSummaryMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t OptionsOutrightSeriesSummaryMessage::series_index() const { return series_index_; }
void OptionsOutrightSeriesSummaryMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

std::int32_t OptionsOutrightSeriesSummaryMessage::high_price() const { return high_price_; }
void OptionsOutrightSeriesSummaryMessage::set_high_price(std::int32_t value) { high_price_ = value; }

std::int32_t OptionsOutrightSeriesSummaryMessage::low_price() const { return low_price_; }
void OptionsOutrightSeriesSummaryMessage::set_low_price(std::int32_t value) { low_price_ = value; }

std::int32_t OptionsOutrightSeriesSummaryMessage::open() const { return open_; }
void OptionsOutrightSeriesSummaryMessage::set_open(std::int32_t value) { open_ = value; }

std::int32_t OptionsOutrightSeriesSummaryMessage::close() const { return close_; }
void OptionsOutrightSeriesSummaryMessage::set_close(std::int32_t value) { close_ = value; }

std::uint32_t OptionsOutrightSeriesSummaryMessage::total_volume() const { return total_volume_; }
void OptionsOutrightSeriesSummaryMessage::set_total_volume(std::uint32_t value) { total_volume_ = value; }

MessageCode OptionsOutrightSeriesSummaryMessage::type() const { return message_type; }

std::string_view OptionsOutrightSeriesSummaryMessage::name() const { return "Options Outright Series Summary Message"; }

std::size_t OptionsOutrightSeriesSummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OptionsOutrightSeriesSummaryMessage", wire_size, length);

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

std::size_t OptionsOutrightSeriesSummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionsOutrightSeriesSummaryMessage", wire_size, capacity);

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

std::size_t OptionsOutrightSeriesSummaryMessage::encoded_size() const {
    return wire_size;
}

void OptionsOutrightSeriesSummaryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OptionsOutrightSeriesSummaryMessage::clone() const {
    return std::make_unique<OptionsOutrightSeriesSummaryMessage>(*this);
}

void OptionsOutrightSeriesSummaryMessage::print(std::ostream& out) const {
    out << "OptionsOutrightSeriesSummaryMessage{";
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

bool OptionsOutrightSeriesSummaryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OptionsOutrightSeriesSummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OptionsOutrightSeriesSummaryMessage::operator==(const OptionsOutrightSeriesSummaryMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && series_index_ == other.series_index_
        && high_price_ == other.high_price_
        && low_price_ == other.low_price_
        && open_ == other.open_
        && close_ == other.close_
        && total_volume_ == other.total_volume_;
}

bool OptionsOutrightSeriesSummaryMessage::operator!=(const OptionsOutrightSeriesSummaryMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
