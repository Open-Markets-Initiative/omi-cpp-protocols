#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

class Eop {
  public:
    static constexpr const char* name = "Eop";

    // the bytes it reads, which it does not own: they must outlive it
    explicit Eop(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every Eop has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 5;
    static constexpr std::size_t fixed_size = 5;
    std::size_t encoded_size() const { return 5; }

    std::int8_t eop_exponent() const { return wire::read_i8(at(0)); }

    std::int32_t eop_mantissa() const { return wire::read_i32_be(at(1)); }

    void print(std::ostream& out) const {
        out << "Eop{";
        out << "eop_exponent=";
        out << static_cast<int>(eop_exponent());
        out << ", eop_mantissa=";
        out << eop_mantissa();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const Eop& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
