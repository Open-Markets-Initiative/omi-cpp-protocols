#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

class MdEntryPx {
  public:
    static constexpr const char* name = "MdEntryPx";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MdEntryPx(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MdEntryPx has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 5;
    static constexpr std::size_t fixed_size = 5;
    std::size_t encoded_size() const { return 5; }

    std::int8_t md_entry_px_exponent() const { return wire::read_i8(at(0)); }

    std::int32_t md_entry_px_mantissa() const { return wire::read_i32_be(at(1)); }

    void print(std::ostream& out) const {
        out << "MdEntryPx{";
        out << "md_entry_px_exponent=";
        out << static_cast<int>(md_entry_px_exponent());
        out << ", md_entry_px_mantissa=";
        out << md_entry_px_mantissa();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MdEntryPx& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
