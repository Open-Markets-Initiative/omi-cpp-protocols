#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// This group indicates the number of broken dates and references individual broken contracts
// in user defined tailor made repo. Applicable only to tailor made repos requested by traders
// with broken dates
class BrokenDatesGroup {
  public:
    static constexpr const char* name = "BrokenDatesGroup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit BrokenDatesGroup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every BrokenDatesGroup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::uint64_t broken_date_guid() const { return wire::read_u64_le(at(0)); }

    std::int32_t broken_date_security_id() const { return wire::read_i32_le(at(8)); }

    std::optional<std::uint16_t> broken_date_start() const { return wire::nullable(wire::read_u16_le(at(12)), static_cast<std::uint16_t>(65535ULL)); }

    std::optional<std::uint16_t> broken_date_end() const { return wire::nullable(wire::read_u16_le(at(14)), static_cast<std::uint16_t>(65535ULL)); }

    void print(std::ostream& out) const {
        out << "BrokenDatesGroup{";
        out << "broken_date_guid=";
        out << broken_date_guid();
        out << ", broken_date_security_id=";
        out << broken_date_security_id();
        out << ", broken_date_start=";
        print::optional(out, broken_date_start());
        out << ", broken_date_end=";
        print::optional(out, broken_date_end());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const BrokenDatesGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
