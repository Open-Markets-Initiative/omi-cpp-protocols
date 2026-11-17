// Databento.MarketData.Normalized.Dbn.v2: groups/SymbolMapping.cpp
#include "SymbolMapping.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

SymbolMapping::SymbolMapping(const std::string& raw_symbol_in, std::uint32_t interval_count, const std::vector<MappingInterval>& mapping_interval)
  : raw_symbol_in_(raw_symbol_in), interval_count_(interval_count), mapping_interval_(mapping_interval) {}

const std::string& SymbolMapping::raw_symbol_in() const { return raw_symbol_in_; }
std::string& SymbolMapping::raw_symbol_in() { return raw_symbol_in_; }
void SymbolMapping::set_raw_symbol_in(const std::string& value) { raw_symbol_in_ = value; }

std::uint32_t SymbolMapping::interval_count() const { return interval_count_; }
void SymbolMapping::set_interval_count(std::uint32_t value) { interval_count_ = value; }

const std::vector<MappingInterval>& SymbolMapping::mapping_interval() const { return mapping_interval_; }
std::vector<MappingInterval>& SymbolMapping::mapping_interval() { return mapping_interval_; }
void SymbolMapping::set_mapping_interval(const std::vector<MappingInterval>& value) { mapping_interval_ = value; }

std::size_t SymbolMapping::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("SymbolMapping", offset + 71, length);
    raw_symbol_in_ = wire::read_text(data + offset, 71, '\0');
    offset += 71;

    wire::require("SymbolMapping", offset + 4, length);
    interval_count_ = wire::read_u32_le(data + offset);
    offset += 4;

    {
        const std::size_t count = wire::count(interval_count_);
        mapping_interval_.clear();
        mapping_interval_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            MappingInterval entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            offset += consumed;
            mapping_interval_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t SymbolMapping::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SymbolMapping", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto interval_count = interval_count_;
    interval_count = static_cast<std::uint32_t>(mapping_interval_.size());

    wire::write_text(data + offset, 71, '\0', raw_symbol_in_);
    offset += 71;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(interval_count));
    offset += 4;

    for (const auto& entry : mapping_interval_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t SymbolMapping::encoded_size() const {
    return 71 + 4 + wire::encoded_size_of(mapping_interval_);
}

void SymbolMapping::print(std::ostream& out) const {
    out << "SymbolMapping{";
    out << "raw_symbol_in=";
    print::text(out, raw_symbol_in_);
    out << ", interval_count=";
    out << interval_count_;
    out << ", mapping_interval=";
    print::sequence(out, mapping_interval_);
    out << '}';
}

bool SymbolMapping::operator==(const SymbolMapping& other) const {
    return raw_symbol_in_ == other.raw_symbol_in_
        && interval_count_ == other.interval_count_
        && mapping_interval_ == other.mapping_interval_;
}

bool SymbolMapping::operator!=(const SymbolMapping& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SymbolMapping& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v2
