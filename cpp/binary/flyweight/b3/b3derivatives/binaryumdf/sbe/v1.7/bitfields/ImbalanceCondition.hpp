#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// ImbalanceCondition bit set
class ImbalanceCondition {
  public:
    static constexpr const char* name = "ImbalanceCondition";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ImbalanceCondition(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 2;
    static constexpr std::size_t fixed_size = 2;
    std::size_t encoded_size() const { return 2; }

    std::uint16_t raw() const { return wire::read_u16_le(bytes_.data()); }

    bool unused_imbalance_condition_0() const { return (raw() & static_cast<std::uint16_t>(0x1)) != 0; }

    bool unused_imbalance_condition_1() const { return (raw() & static_cast<std::uint16_t>(0x2)) != 0; }

    bool unused_imbalance_condition_2() const { return (raw() & static_cast<std::uint16_t>(0x4)) != 0; }

    bool unused_imbalance_condition_3() const { return (raw() & static_cast<std::uint16_t>(0x8)) != 0; }

    bool unused_imbalance_condition_4() const { return (raw() & static_cast<std::uint16_t>(0x10)) != 0; }

    bool unused_imbalance_condition_5() const { return (raw() & static_cast<std::uint16_t>(0x20)) != 0; }

    bool unused_imbalance_condition_6() const { return (raw() & static_cast<std::uint16_t>(0x40)) != 0; }

    bool unused_imbalance_condition_7() const { return (raw() & static_cast<std::uint16_t>(0x80)) != 0; }

    bool imbalance_more_buyers() const { return (raw() & static_cast<std::uint16_t>(0x100)) != 0; }

    bool imbalance_more_sellers() const { return (raw() & static_cast<std::uint16_t>(0x200)) != 0; }

    std::uint8_t reserved_6() const { return static_cast<std::uint8_t>((raw() & static_cast<std::uint16_t>(0xFC00)) >> 10); }

    void print(std::ostream& out) const {
        out << "ImbalanceCondition{";
        out << "unused_imbalance_condition_0=";
        out << (unused_imbalance_condition_0() ? "true" : "false");
        out << ", unused_imbalance_condition_1=";
        out << (unused_imbalance_condition_1() ? "true" : "false");
        out << ", unused_imbalance_condition_2=";
        out << (unused_imbalance_condition_2() ? "true" : "false");
        out << ", unused_imbalance_condition_3=";
        out << (unused_imbalance_condition_3() ? "true" : "false");
        out << ", unused_imbalance_condition_4=";
        out << (unused_imbalance_condition_4() ? "true" : "false");
        out << ", unused_imbalance_condition_5=";
        out << (unused_imbalance_condition_5() ? "true" : "false");
        out << ", unused_imbalance_condition_6=";
        out << (unused_imbalance_condition_6() ? "true" : "false");
        out << ", unused_imbalance_condition_7=";
        out << (unused_imbalance_condition_7() ? "true" : "false");
        out << ", imbalance_more_buyers=";
        out << (imbalance_more_buyers() ? "true" : "false");
        out << ", imbalance_more_sellers=";
        out << (imbalance_more_sellers() ? "true" : "false");
        out << ", reserved_6=";
        out << static_cast<unsigned long long>(reserved_6());
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ImbalanceCondition& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
