#include "RepoRelatedInstrumentsGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

RepoRelatedInstrumentsGroup::RepoRelatedInstrumentsGroup(std::int32_t related_security_id, const std::string& related_symbol, std::optional<std::uint64_t> related_instrument_guid)
  : related_security_id_(related_security_id), related_symbol_(related_symbol), related_instrument_guid_(related_instrument_guid) {}

std::int32_t RepoRelatedInstrumentsGroup::related_security_id() const { return related_security_id_; }
void RepoRelatedInstrumentsGroup::set_related_security_id(std::int32_t value) { related_security_id_ = value; }

const std::string& RepoRelatedInstrumentsGroup::related_symbol() const { return related_symbol_; }
std::string& RepoRelatedInstrumentsGroup::related_symbol() { return related_symbol_; }
void RepoRelatedInstrumentsGroup::set_related_symbol(const std::string& value) { related_symbol_ = value; }

std::optional<std::uint64_t> RepoRelatedInstrumentsGroup::related_instrument_guid() const { return related_instrument_guid_; }
void RepoRelatedInstrumentsGroup::set_related_instrument_guid(std::optional<std::uint64_t> value) { related_instrument_guid_ = value; }

std::size_t RepoRelatedInstrumentsGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RepoRelatedInstrumentsGroup", wire_size, length);

    related_security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    related_symbol_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    related_instrument_guid_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    return offset;
}

std::size_t RepoRelatedInstrumentsGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RepoRelatedInstrumentsGroup", wire_size, capacity);

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(related_security_id_));
    offset += 4;

    wire::write_text(data + offset, 20, '\0', related_symbol_);
    offset += 20;

    wire::write_u64_le(data + offset, related_instrument_guid_.value_or(static_cast<std::uint64_t>(18446744073709551615ULL)));
    offset += 8;

    return offset;
}

std::size_t RepoRelatedInstrumentsGroup::encoded_size() const {
    return wire_size;
}

void RepoRelatedInstrumentsGroup::print(std::ostream& out) const {
    out << "RepoRelatedInstrumentsGroup{";
    out << "related_security_id=";
    out << related_security_id_;
    out << ", related_symbol=";
    print::text(out, related_symbol_);
    out << ", related_instrument_guid=";
    print::optional(out, related_instrument_guid_);
    out << '}';
}

bool RepoRelatedInstrumentsGroup::operator==(const RepoRelatedInstrumentsGroup& other) const {
    return related_security_id_ == other.related_security_id_
        && related_symbol_ == other.related_symbol_
        && related_instrument_guid_ == other.related_instrument_guid_;
}

bool RepoRelatedInstrumentsGroup::operator!=(const RepoRelatedInstrumentsGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const RepoRelatedInstrumentsGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
