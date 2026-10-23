#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MdUpdateAction.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of entries in Market Data message
class IncrementalRefreshVolumeLongGroup {
  public:
    static constexpr const char* name = "IncrementalRefreshVolumeLongGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IncrementalRefreshVolumeLongGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IncrementalRefreshVolumeLongGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    std::uint64_t md_entry_size() const { return wire::read_u64_le(at(0)); }

    std::int32_t security_id() const { return wire::read_i32_le(at(8)); }

    std::uint32_t rpt_seq() const { return wire::read_u32_le(at(12)); }

    MdUpdateAction md_update_action() const { return static_cast<MdUpdateAction>(wire::read_u8(at(16))); }

    std::span<const std::byte, 7> padding_7() const { return bytes_.subspan(17).template first<7>(); }

    void print(std::ostream& out) const {
        out << "IncrementalRefreshVolumeLongGroup{";
        out << "md_entry_size=";
        out << md_entry_size();
        out << ", security_id=";
        out << security_id();
        out << ", rpt_seq=";
        out << rpt_seq();
        out << ", md_update_action=";
        out << md_update_action();
        out << ", padding_7=";
        print::hex(out, padding_7().data(), padding_7().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const IncrementalRefreshVolumeLongGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
