#include "RetailPriceImprovementMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

RetailPriceImprovementMessage::RetailPriceImprovementMessage(std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, RpiIndicator rpi_indicator)
  : source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), rpi_indicator_(rpi_indicator) {}

std::uint32_t RetailPriceImprovementMessage::source_time_ns() const { return source_time_ns_; }
void RetailPriceImprovementMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t RetailPriceImprovementMessage::symbol_index() const { return symbol_index_; }
void RetailPriceImprovementMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t RetailPriceImprovementMessage::symbol_seq_num() const { return symbol_seq_num_; }
void RetailPriceImprovementMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

RpiIndicator RetailPriceImprovementMessage::rpi_indicator() const { return rpi_indicator_; }
void RetailPriceImprovementMessage::set_rpi_indicator(RpiIndicator value) { rpi_indicator_ = value; }

MessageCode RetailPriceImprovementMessage::type() const { return message_type; }

std::string_view RetailPriceImprovementMessage::name() const { return "Retail Price Improvement Message"; }

std::size_t RetailPriceImprovementMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RetailPriceImprovementMessage", wire_size, length);

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    rpi_indicator_ = static_cast<RpiIndicator>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t RetailPriceImprovementMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RetailPriceImprovementMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(rpi_indicator_));
    offset += 1;

    return offset;
}

std::size_t RetailPriceImprovementMessage::encoded_size() const {
    return wire_size;
}

void RetailPriceImprovementMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> RetailPriceImprovementMessage::clone() const {
    return std::make_unique<RetailPriceImprovementMessage>(*this);
}

void RetailPriceImprovementMessage::print(std::ostream& out) const {
    out << "RetailPriceImprovementMessage{";
    out << "source_time_ns=";
    out << source_time_ns_;
    out << ", symbol_index=";
    out << symbol_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", rpi_indicator=";
    out << rpi_indicator_;
    out << '}';
}

bool RetailPriceImprovementMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const RetailPriceImprovementMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RetailPriceImprovementMessage::operator==(const RetailPriceImprovementMessage& other) const {
    return source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && rpi_indicator_ == other.rpi_indicator_;
}

bool RetailPriceImprovementMessage::operator!=(const RetailPriceImprovementMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
