#include "RefreshOutrightMarketDepthBuyMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

RefreshOutrightMarketDepthBuyMessage::RefreshOutrightMarketDepthBuyMessage(std::uint32_t source_time, std::uint32_t source_ns, std::uint32_t series_index, std::uint32_t symbol_seq_num, std::int32_t first_level_price, std::int32_t second_level_price, std::int32_t third_level_price, std::uint16_t first_volume, std::uint16_t second_volume, std::uint16_t third_volume, QuoteCondition quote_condition, const std::array<std::byte, 1>& reserved_1, std::uint16_t first_level_customer_volume, std::uint16_t second_level_customer_volume, std::uint16_t third_level_customer_volume, const std::array<std::byte, 2>& reserved_2)
  : source_time_(source_time), source_ns_(source_ns), series_index_(series_index), symbol_seq_num_(symbol_seq_num), first_level_price_(first_level_price), second_level_price_(second_level_price), third_level_price_(third_level_price), first_volume_(first_volume), second_volume_(second_volume), third_volume_(third_volume), quote_condition_(quote_condition), reserved_1_(reserved_1), first_level_customer_volume_(first_level_customer_volume), second_level_customer_volume_(second_level_customer_volume), third_level_customer_volume_(third_level_customer_volume), reserved_2_(reserved_2) {}

std::uint32_t RefreshOutrightMarketDepthBuyMessage::source_time() const { return source_time_; }
void RefreshOutrightMarketDepthBuyMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t RefreshOutrightMarketDepthBuyMessage::source_ns() const { return source_ns_; }
void RefreshOutrightMarketDepthBuyMessage::set_source_ns(std::uint32_t value) { source_ns_ = value; }

std::uint32_t RefreshOutrightMarketDepthBuyMessage::series_index() const { return series_index_; }
void RefreshOutrightMarketDepthBuyMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

std::uint32_t RefreshOutrightMarketDepthBuyMessage::symbol_seq_num() const { return symbol_seq_num_; }
void RefreshOutrightMarketDepthBuyMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::int32_t RefreshOutrightMarketDepthBuyMessage::first_level_price() const { return first_level_price_; }
void RefreshOutrightMarketDepthBuyMessage::set_first_level_price(std::int32_t value) { first_level_price_ = value; }

std::int32_t RefreshOutrightMarketDepthBuyMessage::second_level_price() const { return second_level_price_; }
void RefreshOutrightMarketDepthBuyMessage::set_second_level_price(std::int32_t value) { second_level_price_ = value; }

std::int32_t RefreshOutrightMarketDepthBuyMessage::third_level_price() const { return third_level_price_; }
void RefreshOutrightMarketDepthBuyMessage::set_third_level_price(std::int32_t value) { third_level_price_ = value; }

std::uint16_t RefreshOutrightMarketDepthBuyMessage::first_volume() const { return first_volume_; }
void RefreshOutrightMarketDepthBuyMessage::set_first_volume(std::uint16_t value) { first_volume_ = value; }

std::uint16_t RefreshOutrightMarketDepthBuyMessage::second_volume() const { return second_volume_; }
void RefreshOutrightMarketDepthBuyMessage::set_second_volume(std::uint16_t value) { second_volume_ = value; }

std::uint16_t RefreshOutrightMarketDepthBuyMessage::third_volume() const { return third_volume_; }
void RefreshOutrightMarketDepthBuyMessage::set_third_volume(std::uint16_t value) { third_volume_ = value; }

QuoteCondition RefreshOutrightMarketDepthBuyMessage::quote_condition() const { return quote_condition_; }
void RefreshOutrightMarketDepthBuyMessage::set_quote_condition(QuoteCondition value) { quote_condition_ = value; }

const std::array<std::byte, 1>& RefreshOutrightMarketDepthBuyMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& RefreshOutrightMarketDepthBuyMessage::reserved_1() { return reserved_1_; }
void RefreshOutrightMarketDepthBuyMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

std::uint16_t RefreshOutrightMarketDepthBuyMessage::first_level_customer_volume() const { return first_level_customer_volume_; }
void RefreshOutrightMarketDepthBuyMessage::set_first_level_customer_volume(std::uint16_t value) { first_level_customer_volume_ = value; }

std::uint16_t RefreshOutrightMarketDepthBuyMessage::second_level_customer_volume() const { return second_level_customer_volume_; }
void RefreshOutrightMarketDepthBuyMessage::set_second_level_customer_volume(std::uint16_t value) { second_level_customer_volume_ = value; }

std::uint16_t RefreshOutrightMarketDepthBuyMessage::third_level_customer_volume() const { return third_level_customer_volume_; }
void RefreshOutrightMarketDepthBuyMessage::set_third_level_customer_volume(std::uint16_t value) { third_level_customer_volume_ = value; }

const std::array<std::byte, 2>& RefreshOutrightMarketDepthBuyMessage::reserved_2() const { return reserved_2_; }
std::array<std::byte, 2>& RefreshOutrightMarketDepthBuyMessage::reserved_2() { return reserved_2_; }
void RefreshOutrightMarketDepthBuyMessage::set_reserved_2(const std::array<std::byte, 2>& value) { reserved_2_ = value; }

MessageCode RefreshOutrightMarketDepthBuyMessage::type() const { return message_type; }

std::string_view RefreshOutrightMarketDepthBuyMessage::name() const { return "Refresh Outright Market Depth Buy Message"; }

std::size_t RefreshOutrightMarketDepthBuyMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RefreshOutrightMarketDepthBuyMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    first_level_price_ = wire::read_i32_le(data + offset);
    offset += 4;

    second_level_price_ = wire::read_i32_le(data + offset);
    offset += 4;

    third_level_price_ = wire::read_i32_le(data + offset);
    offset += 4;

    first_volume_ = wire::read_u16_le(data + offset);
    offset += 2;

    second_volume_ = wire::read_u16_le(data + offset);
    offset += 2;

    third_volume_ = wire::read_u16_le(data + offset);
    offset += 2;

    quote_condition_ = static_cast<QuoteCondition>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    first_level_customer_volume_ = wire::read_u16_le(data + offset);
    offset += 2;

    second_level_customer_volume_ = wire::read_u16_le(data + offset);
    offset += 2;

    third_level_customer_volume_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::read_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t RefreshOutrightMarketDepthBuyMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RefreshOutrightMarketDepthBuyMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(first_level_price_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(second_level_price_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(third_level_price_));
    offset += 4;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(first_volume_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(second_volume_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(third_volume_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(quote_condition_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(first_level_customer_volume_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(second_level_customer_volume_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(third_level_customer_volume_));
    offset += 2;

    wire::write_bytes(data + offset, reserved_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t RefreshOutrightMarketDepthBuyMessage::encoded_size() const {
    return wire_size;
}

void RefreshOutrightMarketDepthBuyMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> RefreshOutrightMarketDepthBuyMessage::clone() const {
    return std::make_unique<RefreshOutrightMarketDepthBuyMessage>(*this);
}

void RefreshOutrightMarketDepthBuyMessage::print(std::ostream& out) const {
    out << "RefreshOutrightMarketDepthBuyMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_ns=";
    out << source_ns_;
    out << ", series_index=";
    out << series_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", first_level_price=";
    out << first_level_price_;
    out << ", second_level_price=";
    out << second_level_price_;
    out << ", third_level_price=";
    out << third_level_price_;
    out << ", first_volume=";
    out << first_volume_;
    out << ", second_volume=";
    out << second_volume_;
    out << ", third_volume=";
    out << third_volume_;
    out << ", quote_condition=";
    out << quote_condition_;
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
    out << ", first_level_customer_volume=";
    out << first_level_customer_volume_;
    out << ", second_level_customer_volume=";
    out << second_level_customer_volume_;
    out << ", third_level_customer_volume=";
    out << third_level_customer_volume_;
    out << ", reserved_2=";
    print::hex(out, reserved_2_.data(), reserved_2_.size());
    out << '}';
}

bool RefreshOutrightMarketDepthBuyMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const RefreshOutrightMarketDepthBuyMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RefreshOutrightMarketDepthBuyMessage::operator==(const RefreshOutrightMarketDepthBuyMessage& other) const {
    return source_time_ == other.source_time_
        && source_ns_ == other.source_ns_
        && series_index_ == other.series_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && first_level_price_ == other.first_level_price_
        && second_level_price_ == other.second_level_price_
        && third_level_price_ == other.third_level_price_
        && first_volume_ == other.first_volume_
        && second_volume_ == other.second_volume_
        && third_volume_ == other.third_volume_
        && quote_condition_ == other.quote_condition_
        && reserved_1_ == other.reserved_1_
        && first_level_customer_volume_ == other.first_level_customer_volume_
        && second_level_customer_volume_ == other.second_level_customer_volume_
        && third_level_customer_volume_ == other.third_level_customer_volume_
        && reserved_2_ == other.reserved_2_;
}

bool RefreshOutrightMarketDepthBuyMessage::operator!=(const RefreshOutrightMarketDepthBuyMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
