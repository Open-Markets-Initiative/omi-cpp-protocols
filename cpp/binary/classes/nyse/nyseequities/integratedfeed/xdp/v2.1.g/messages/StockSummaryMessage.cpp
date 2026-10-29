#include "StockSummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

StockSummaryMessage::StockSummaryMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t high_price, std::uint32_t low_price, std::uint32_t open, std::uint32_t close, std::uint32_t total_volume)
  : source_time_(source_time), source_time_ns_(source_time_ns), symbol_index_(symbol_index), high_price_(high_price), low_price_(low_price), open_(open), close_(close), total_volume_(total_volume) {}

std::uint32_t StockSummaryMessage::source_time() const { return source_time_; }
void StockSummaryMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t StockSummaryMessage::source_time_ns() const { return source_time_ns_; }
void StockSummaryMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t StockSummaryMessage::symbol_index() const { return symbol_index_; }
void StockSummaryMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t StockSummaryMessage::high_price() const { return high_price_; }
void StockSummaryMessage::set_high_price(std::uint32_t value) { high_price_ = value; }

std::uint32_t StockSummaryMessage::low_price() const { return low_price_; }
void StockSummaryMessage::set_low_price(std::uint32_t value) { low_price_ = value; }

std::uint32_t StockSummaryMessage::open() const { return open_; }
void StockSummaryMessage::set_open(std::uint32_t value) { open_ = value; }

std::uint32_t StockSummaryMessage::close() const { return close_; }
void StockSummaryMessage::set_close(std::uint32_t value) { close_ = value; }

std::uint32_t StockSummaryMessage::total_volume() const { return total_volume_; }
void StockSummaryMessage::set_total_volume(std::uint32_t value) { total_volume_ = value; }

MessageCode StockSummaryMessage::type() const { return message_type; }

std::string_view StockSummaryMessage::name() const { return "Stock Summary Message"; }

std::size_t StockSummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("StockSummaryMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    high_price_ = wire::read_u32_le(data + offset);
    offset += 4;

    low_price_ = wire::read_u32_le(data + offset);
    offset += 4;

    open_ = wire::read_u32_le(data + offset);
    offset += 4;

    close_ = wire::read_u32_le(data + offset);
    offset += 4;

    total_volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t StockSummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("StockSummaryMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(high_price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(low_price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(open_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(close_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(total_volume_));
    offset += 4;

    return offset;
}

std::size_t StockSummaryMessage::encoded_size() const {
    return wire_size;
}

void StockSummaryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> StockSummaryMessage::clone() const {
    return std::make_unique<StockSummaryMessage>(*this);
}

void StockSummaryMessage::print(std::ostream& out) const {
    out << "StockSummaryMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
    out << ", symbol_index=";
    out << symbol_index_;
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

bool StockSummaryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const StockSummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool StockSummaryMessage::operator==(const StockSummaryMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && high_price_ == other.high_price_
        && low_price_ == other.low_price_
        && open_ == other.open_
        && close_ == other.close_
        && total_volume_ == other.total_volume_;
}

bool StockSummaryMessage::operator!=(const StockSummaryMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
