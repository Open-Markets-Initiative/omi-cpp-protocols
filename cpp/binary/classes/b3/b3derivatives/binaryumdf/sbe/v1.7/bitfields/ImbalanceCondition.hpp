// B3.B3Derivatives.BinaryUmdf.Sbe.v1.7: bitfields/ImbalanceCondition.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// ImbalanceCondition bit set
class ImbalanceCondition {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 2;

    ImbalanceCondition() = default;
    explicit ImbalanceCondition(std::uint16_t raw);

    // Imbalance More Buyers: ImbalanceMoreBuyers
    bool imbalance_more_buyers() const;
    void set_imbalance_more_buyers(bool value);

    // Imbalance More Sellers: ImbalanceMoreSellers
    bool imbalance_more_sellers() const;
    void set_imbalance_more_sellers(bool value);

    // The whole bitfield as its wire integer
    std::uint16_t raw() const;
    void set_raw(std::uint16_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const ImbalanceCondition& other) const;
    bool operator!=(const ImbalanceCondition& other) const;

  private:
    std::uint16_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const ImbalanceCondition& value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
