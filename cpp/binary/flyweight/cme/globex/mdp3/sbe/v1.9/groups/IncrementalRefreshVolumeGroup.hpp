#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MdUpdateAction.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// Number of entries in Market Data message
class IncrementalRefreshVolumeGroup {
  public:
    static constexpr const char* name = "IncrementalRefreshVolumeGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IncrementalRefreshVolumeGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IncrementalRefreshVolumeGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::int32_t md_entry_size_short() const { return wire::read_i32_le(at(0)); }

    std::int32_t security_id() const { return wire::read_i32_le(at(4)); }

    std::uint32_t rpt_seq() const { return wire::read_u32_le(at(8)); }

    MdUpdateAction md_update_action() const { return static_cast<MdUpdateAction>(wire::read_u8(at(12))); }

    std::span<const std::byte, 3> padding_3() const { return bytes_.subspan(13).template first<3>(); }

    void print(std::ostream& out) const {
        out << "IncrementalRefreshVolumeGroup{";
        out << "md_entry_size_short=";
        out << md_entry_size_short();
        out << ", security_id=";
        out << security_id();
        out << ", rpt_seq=";
        out << rpt_seq();
        out << ", md_update_action=";
        out << md_update_action();
        out << ", padding_3=";
        print::hex(out, padding_3().data(), padding_3().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const IncrementalRefreshVolumeGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
