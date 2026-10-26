#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/OptionRelatedInstrumentsGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// NoRelatedInstruments Block
class OptionRelatedInstrumentsGroups {
  public:

    OptionRelatedInstrumentsGroups() = default;
    OptionRelatedInstrumentsGroups(const GroupSize& group_size, const std::vector<OptionRelatedInstrumentsGroup>& option_related_instruments_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Option Related Instruments Group: Number of related instruments group
    const std::vector<OptionRelatedInstrumentsGroup>& option_related_instruments_group() const;
    std::vector<OptionRelatedInstrumentsGroup>& option_related_instruments_group();
    void set_option_related_instruments_group(const std::vector<OptionRelatedInstrumentsGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const OptionRelatedInstrumentsGroups& other) const;
    bool operator!=(const OptionRelatedInstrumentsGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<OptionRelatedInstrumentsGroup> option_related_instruments_group_{};
};

std::ostream& operator<<(std::ostream& out, const OptionRelatedInstrumentsGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_8
