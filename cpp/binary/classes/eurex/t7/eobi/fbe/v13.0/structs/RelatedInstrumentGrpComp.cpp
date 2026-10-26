#include "RelatedInstrumentGrpComp.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

RelatedInstrumentGrpComp::RelatedInstrumentGrpComp(std::optional<std::int64_t> related_security_id)
  : related_security_id_(related_security_id) {}

std::optional<std::int64_t> RelatedInstrumentGrpComp::related_security_id() const { return related_security_id_; }
void RelatedInstrumentGrpComp::set_related_security_id(std::optional<std::int64_t> value) { related_security_id_ = value; }

std::size_t RelatedInstrumentGrpComp::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RelatedInstrumentGrpComp", wire_size, length);

    related_security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    return offset;
}

std::size_t RelatedInstrumentGrpComp::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RelatedInstrumentGrpComp", wire_size, capacity);

    wire::write_i64_le(data + offset, related_security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    return offset;
}

std::size_t RelatedInstrumentGrpComp::encoded_size() const {
    return wire_size;
}

void RelatedInstrumentGrpComp::print(std::ostream& out) const {
    out << "RelatedInstrumentGrpComp{";
    out << "related_security_id=";
    print::optional(out, related_security_id_);
    out << '}';
}

bool RelatedInstrumentGrpComp::operator==(const RelatedInstrumentGrpComp& other) const {
    return related_security_id_ == other.related_security_id_;
}

bool RelatedInstrumentGrpComp::operator!=(const RelatedInstrumentGrpComp& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const RelatedInstrumentGrpComp& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v13_0
