#include "ComplexSeriesIndexMappingMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

ComplexSeriesIndexMappingMessage::ComplexSeriesIndexMappingMessage(std::uint32_t series_index, MarketId market_id, std::uint8_t system_id, std::uint16_t no_of_legs, const std::vector<ComplexSeriesIndexMappingLeg>& complex_series_index_mapping_leg)
  : series_index_(series_index), market_id_(market_id), system_id_(system_id), no_of_legs_(no_of_legs), complex_series_index_mapping_leg_(complex_series_index_mapping_leg) {}

std::uint32_t ComplexSeriesIndexMappingMessage::series_index() const { return series_index_; }
void ComplexSeriesIndexMappingMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

MarketId ComplexSeriesIndexMappingMessage::market_id() const { return market_id_; }
void ComplexSeriesIndexMappingMessage::set_market_id(MarketId value) { market_id_ = value; }

std::uint8_t ComplexSeriesIndexMappingMessage::system_id() const { return system_id_; }
void ComplexSeriesIndexMappingMessage::set_system_id(std::uint8_t value) { system_id_ = value; }

std::uint16_t ComplexSeriesIndexMappingMessage::no_of_legs() const { return no_of_legs_; }
void ComplexSeriesIndexMappingMessage::set_no_of_legs(std::uint16_t value) { no_of_legs_ = value; }

const std::vector<ComplexSeriesIndexMappingLeg>& ComplexSeriesIndexMappingMessage::complex_series_index_mapping_leg() const { return complex_series_index_mapping_leg_; }
std::vector<ComplexSeriesIndexMappingLeg>& ComplexSeriesIndexMappingMessage::complex_series_index_mapping_leg() { return complex_series_index_mapping_leg_; }
void ComplexSeriesIndexMappingMessage::set_complex_series_index_mapping_leg(const std::vector<ComplexSeriesIndexMappingLeg>& value) { complex_series_index_mapping_leg_ = value; }

MessageCode ComplexSeriesIndexMappingMessage::type() const { return message_type; }

std::string_view ComplexSeriesIndexMappingMessage::name() const { return "Complex Series Index Mapping Message"; }

std::size_t ComplexSeriesIndexMappingMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ComplexSeriesIndexMappingMessage", offset + 4, length);
    series_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ComplexSeriesIndexMappingMessage", offset + 2, length);
    market_id_ = static_cast<MarketId>(wire::read_u16_le(data + offset));
    offset += 2;

    wire::require("ComplexSeriesIndexMappingMessage", offset + 1, length);
    system_id_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("ComplexSeriesIndexMappingMessage", offset + 2, length);
    no_of_legs_ = wire::read_u16_le(data + offset);
    offset += 2;

    {
        const std::size_t count = wire::count(no_of_legs_);
        complex_series_index_mapping_leg_.clear();
        complex_series_index_mapping_leg_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            ComplexSeriesIndexMappingLeg entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            complex_series_index_mapping_leg_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t ComplexSeriesIndexMappingMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ComplexSeriesIndexMappingMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto no_of_legs = no_of_legs_;
    no_of_legs = static_cast<std::uint16_t>(complex_series_index_mapping_leg_.size());

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_index_));
    offset += 4;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(market_id_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(system_id_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(no_of_legs));
    offset += 2;

    for (const auto& entry : complex_series_index_mapping_leg_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t ComplexSeriesIndexMappingMessage::encoded_size() const {
    return 4 + 2 + 1 + 2 + wire::encoded_size_of(complex_series_index_mapping_leg_);
}

void ComplexSeriesIndexMappingMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ComplexSeriesIndexMappingMessage::clone() const {
    return std::make_unique<ComplexSeriesIndexMappingMessage>(*this);
}

void ComplexSeriesIndexMappingMessage::print(std::ostream& out) const {
    out << "ComplexSeriesIndexMappingMessage{";
    out << "series_index=";
    out << series_index_;
    out << ", market_id=";
    out << market_id_;
    out << ", system_id=";
    out << static_cast<int>(system_id_);
    out << ", no_of_legs=";
    out << no_of_legs_;
    out << ", complex_series_index_mapping_leg=";
    print::sequence(out, complex_series_index_mapping_leg_);
    out << '}';
}

bool ComplexSeriesIndexMappingMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ComplexSeriesIndexMappingMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ComplexSeriesIndexMappingMessage::operator==(const ComplexSeriesIndexMappingMessage& other) const {
    return series_index_ == other.series_index_
        && market_id_ == other.market_id_
        && system_id_ == other.system_id_
        && no_of_legs_ == other.no_of_legs_
        && complex_series_index_mapping_leg_ == other.complex_series_index_mapping_leg_;
}

bool ComplexSeriesIndexMappingMessage::operator!=(const ComplexSeriesIndexMappingMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
