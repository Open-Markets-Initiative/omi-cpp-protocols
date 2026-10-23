#include "RepoUnderlyingsGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

RepoUnderlyingsGroups::RepoUnderlyingsGroups(const GroupSize& group_size, const std::vector<RepoUnderlyingsGroup>& repo_underlyings_group)
  : group_size_(group_size), repo_underlyings_group_(repo_underlyings_group) {}

const GroupSize& RepoUnderlyingsGroups::group_size() const { return group_size_; }
GroupSize& RepoUnderlyingsGroups::group_size() { return group_size_; }
void RepoUnderlyingsGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<RepoUnderlyingsGroup>& RepoUnderlyingsGroups::repo_underlyings_group() const { return repo_underlyings_group_; }
std::vector<RepoUnderlyingsGroup>& RepoUnderlyingsGroups::repo_underlyings_group() { return repo_underlyings_group_; }
void RepoUnderlyingsGroups::set_repo_underlyings_group(const std::vector<RepoUnderlyingsGroup>& value) { repo_underlyings_group_ = value; }

std::size_t RepoUnderlyingsGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        repo_underlyings_group_.clear();
        repo_underlyings_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            RepoUnderlyingsGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("RepoUnderlyingsGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            repo_underlyings_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t RepoUnderlyingsGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RepoUnderlyingsGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(repo_underlyings_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(RepoUnderlyingsGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : repo_underlyings_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t RepoUnderlyingsGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(repo_underlyings_group_);
}

void RepoUnderlyingsGroups::print(std::ostream& out) const {
    out << "RepoUnderlyingsGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", repo_underlyings_group=";
    print::sequence(out, repo_underlyings_group_);
    out << '}';
}

bool RepoUnderlyingsGroups::operator==(const RepoUnderlyingsGroups& other) const {
    return group_size_ == other.group_size_
        && repo_underlyings_group_ == other.repo_underlyings_group_;
}

bool RepoUnderlyingsGroups::operator!=(const RepoUnderlyingsGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const RepoUnderlyingsGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
