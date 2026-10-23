#include "RepoRelatedInstrumentsGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

RepoRelatedInstrumentsGroups::RepoRelatedInstrumentsGroups(const GroupSize& group_size, const std::vector<RepoRelatedInstrumentsGroup>& repo_related_instruments_group)
  : group_size_(group_size), repo_related_instruments_group_(repo_related_instruments_group) {}

const GroupSize& RepoRelatedInstrumentsGroups::group_size() const { return group_size_; }
GroupSize& RepoRelatedInstrumentsGroups::group_size() { return group_size_; }
void RepoRelatedInstrumentsGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<RepoRelatedInstrumentsGroup>& RepoRelatedInstrumentsGroups::repo_related_instruments_group() const { return repo_related_instruments_group_; }
std::vector<RepoRelatedInstrumentsGroup>& RepoRelatedInstrumentsGroups::repo_related_instruments_group() { return repo_related_instruments_group_; }
void RepoRelatedInstrumentsGroups::set_repo_related_instruments_group(const std::vector<RepoRelatedInstrumentsGroup>& value) { repo_related_instruments_group_ = value; }

std::size_t RepoRelatedInstrumentsGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        repo_related_instruments_group_.clear();
        repo_related_instruments_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            RepoRelatedInstrumentsGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("RepoRelatedInstrumentsGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            repo_related_instruments_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t RepoRelatedInstrumentsGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RepoRelatedInstrumentsGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(repo_related_instruments_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(RepoRelatedInstrumentsGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : repo_related_instruments_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t RepoRelatedInstrumentsGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(repo_related_instruments_group_);
}

void RepoRelatedInstrumentsGroups::print(std::ostream& out) const {
    out << "RepoRelatedInstrumentsGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", repo_related_instruments_group=";
    print::sequence(out, repo_related_instruments_group_);
    out << '}';
}

bool RepoRelatedInstrumentsGroups::operator==(const RepoRelatedInstrumentsGroups& other) const {
    return group_size_ == other.group_size_
        && repo_related_instruments_group_ == other.repo_related_instruments_group_;
}

bool RepoRelatedInstrumentsGroups::operator!=(const RepoRelatedInstrumentsGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const RepoRelatedInstrumentsGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
