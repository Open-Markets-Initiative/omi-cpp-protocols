#include "InstAttribGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

InstAttribGroups::InstAttribGroups(const GroupSize& group_size, const std::vector<InstAttribGroup>& inst_attrib_group)
  : group_size_(group_size), inst_attrib_group_(inst_attrib_group) {}

const GroupSize& InstAttribGroups::group_size() const { return group_size_; }
GroupSize& InstAttribGroups::group_size() { return group_size_; }
void InstAttribGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<InstAttribGroup>& InstAttribGroups::inst_attrib_group() const { return inst_attrib_group_; }
std::vector<InstAttribGroup>& InstAttribGroups::inst_attrib_group() { return inst_attrib_group_; }
void InstAttribGroups::set_inst_attrib_group(const std::vector<InstAttribGroup>& value) { inst_attrib_group_ = value; }

std::size_t InstAttribGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        inst_attrib_group_.clear();
        inst_attrib_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            InstAttribGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("InstAttribGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            inst_attrib_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t InstAttribGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InstAttribGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(inst_attrib_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(InstAttribGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : inst_attrib_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t InstAttribGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(inst_attrib_group_);
}

void InstAttribGroups::print(std::ostream& out) const {
    out << "InstAttribGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", inst_attrib_group=";
    print::sequence(out, inst_attrib_group_);
    out << '}';
}

bool InstAttribGroups::operator==(const InstAttribGroups& other) const {
    return group_size_ == other.group_size_
        && inst_attrib_group_ == other.inst_attrib_group_;
}

bool InstAttribGroups::operator!=(const InstAttribGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const InstAttribGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
