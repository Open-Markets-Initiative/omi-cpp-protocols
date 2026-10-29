#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/MdUpdateAction.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

// Number of entries in Market Data message
class IncrementalRefreshVolumeGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 16;

    IncrementalRefreshVolumeGroup() = default;
    IncrementalRefreshVolumeGroup(std::int32_t md_entry_size, std::int32_t security_id, std::uint32_t rpt_seq, MdUpdateAction md_update_action, const std::array<std::byte, 3>& padding_3);

    // Md Entry Size: Trade quantity
    std::int32_t md_entry_size() const;
    void set_md_entry_size(std::int32_t value);

    // Security Id: Unique instrument ID
    std::int32_t security_id() const;
    void set_security_id(std::int32_t value);

    // Rpt Seq: Sequence number of the last Market Data entry processed for the instrument
    std::uint32_t rpt_seq() const;
    void set_rpt_seq(std::uint32_t value);

    // Md Update Action: Market Data update action
    MdUpdateAction md_update_action() const;
    void set_md_update_action(MdUpdateAction value);

    // Padding 3: 3 bytes padding
    const std::array<std::byte, 3>& padding_3() const;
    std::array<std::byte, 3>& padding_3();
    void set_padding_3(const std::array<std::byte, 3>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const IncrementalRefreshVolumeGroup& other) const;
    bool operator!=(const IncrementalRefreshVolumeGroup& other) const;

  private:
    std::int32_t md_entry_size_{};
    std::int32_t security_id_{};
    std::uint32_t rpt_seq_{};
    MdUpdateAction md_update_action_{};
    std::array<std::byte, 3> padding_3_{};
};

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshVolumeGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_5
