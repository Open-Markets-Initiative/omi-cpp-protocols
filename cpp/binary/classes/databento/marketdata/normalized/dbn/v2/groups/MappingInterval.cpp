#include "MappingInterval.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

MappingInterval::MappingInterval(std::uint32_t start_date, std::uint32_t end_date, const std::string& mapped_symbol)
  : start_date_(start_date), end_date_(end_date), mapped_symbol_(mapped_symbol) {}

std::uint32_t MappingInterval::start_date() const { return start_date_; }
void MappingInterval::set_start_date(std::uint32_t value) { start_date_ = value; }

std::uint32_t MappingInterval::end_date() const { return end_date_; }
void MappingInterval::set_end_date(std::uint32_t value) { end_date_ = value; }

const std::string& MappingInterval::mapped_symbol() const { return mapped_symbol_; }
std::string& MappingInterval::mapped_symbol() { return mapped_symbol_; }
void MappingInterval::set_mapped_symbol(const std::string& value) { mapped_symbol_ = value; }

std::size_t MappingInterval::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MappingInterval", wire_size, length);

    start_date_ = wire::read_u32_le(data + offset);
    offset += 4;

    end_date_ = wire::read_u32_le(data + offset);
    offset += 4;

    mapped_symbol_ = wire::read_text(data + offset, 71, '\0');
    offset += 71;

    return offset;
}

std::size_t MappingInterval::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MappingInterval", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(start_date_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(end_date_));
    offset += 4;

    wire::write_text(data + offset, 71, '\0', mapped_symbol_);
    offset += 71;

    return offset;
}

std::size_t MappingInterval::encoded_size() const {
    return wire_size;
}

void MappingInterval::print(std::ostream& out) const {
    out << "MappingInterval{";
    out << "start_date=";
    out << start_date_;
    out << ", end_date=";
    out << end_date_;
    out << ", mapped_symbol=";
    print::text(out, mapped_symbol_);
    out << '}';
}

bool MappingInterval::operator==(const MappingInterval& other) const {
    return start_date_ == other.start_date_
        && end_date_ == other.end_date_
        && mapped_symbol_ == other.mapped_symbol_;
}

bool MappingInterval::operator!=(const MappingInterval& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MappingInterval& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v2
