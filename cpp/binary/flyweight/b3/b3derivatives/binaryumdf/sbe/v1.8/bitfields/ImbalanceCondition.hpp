// B3.B3Derivatives.BinaryUmdf.Sbe.v1.8: bitfields/ImbalanceCondition.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

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

    bool imbalance_more_buyers() const { return (raw() & static_cast<std::uint16_t>(0x100)) != 0; }

    bool imbalance_more_sellers() const { return (raw() & static_cast<std::uint16_t>(0x200)) != 0; }

    void print(std::ostream& out) const {
        out << "ImbalanceCondition{";
        out << "imbalance_more_buyers=";
        out << (imbalance_more_buyers() ? "true" : "false");
        out << ", imbalance_more_sellers=";
        out << (imbalance_more_sellers() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ImbalanceCondition& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
