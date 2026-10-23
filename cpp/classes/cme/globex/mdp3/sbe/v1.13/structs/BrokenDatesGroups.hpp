#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/BrokenDatesGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// NoBrokenDates Block
class BrokenDatesGroups {
  public:

    BrokenDatesGroups() = default;
    BrokenDatesGroups(const GroupSize& group_size, const std::vector<BrokenDatesGroup>& broken_dates_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Broken Dates Group: This group indicates the number of broken dates and references
    // individual broken contracts in user defined tailor made repo. Applicable only to tailor
    // made repos requested by traders with broken dates
    const std::vector<BrokenDatesGroup>& broken_dates_group() const;
    std::vector<BrokenDatesGroup>& broken_dates_group();
    void set_broken_dates_group(const std::vector<BrokenDatesGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const BrokenDatesGroups& other) const;
    bool operator!=(const BrokenDatesGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<BrokenDatesGroup> broken_dates_group_{};
};

std::ostream& operator<<(std::ostream& out, const BrokenDatesGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_13
