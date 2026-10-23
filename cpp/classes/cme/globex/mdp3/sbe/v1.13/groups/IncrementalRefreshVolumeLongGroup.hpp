#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/MdUpdateAction.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of entries in Market Data message
class IncrementalRefreshVolumeLongGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 24;

    IncrementalRefreshVolumeLongGroup() = default;
    IncrementalRefreshVolumeLongGroup(std::uint64_t md_entry_size, std::int32_t security_id, std::uint32_t rpt_seq, MdUpdateAction md_update_action, const std::array<std::byte, 7>& padding_7);

    // Md Entry Size: Consolidated trade quantity, notional
    std::uint64_t md_entry_size() const;
    void set_md_entry_size(std::uint64_t value);

    // Security Id: Security ID
    std::int32_t security_id() const;
    void set_security_id(std::int32_t value);

    // Rpt Seq: Sequence number of the last Market Data entry processed for the instrument
    std::uint32_t rpt_seq() const;
    void set_rpt_seq(std::uint32_t value);

    // Md Update Action: Market Data update action
    MdUpdateAction md_update_action() const;
    void set_md_update_action(MdUpdateAction value);

    // Padding 7: 7 bytes padding
    const std::array<std::byte, 7>& padding_7() const;
    std::array<std::byte, 7>& padding_7();
    void set_padding_7(const std::array<std::byte, 7>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const IncrementalRefreshVolumeLongGroup& other) const;
    bool operator!=(const IncrementalRefreshVolumeLongGroup& other) const;

  private:
    std::uint64_t md_entry_size_{};
    std::int32_t security_id_{};
    std::uint32_t rpt_seq_{};
    MdUpdateAction md_update_action_{};
    std::array<std::byte, 7> padding_7_{};
};

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshVolumeLongGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_13
