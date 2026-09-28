#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// ImbalanceCondition bit set
class ImbalanceCondition {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 2;

    ImbalanceCondition() = default;
    explicit ImbalanceCondition(std::uint16_t raw);

    // Unused Imbalance Condition 0: Unused ImbalanceCondition 0
    bool unused_imbalance_condition_0() const;
    void set_unused_imbalance_condition_0(bool value);

    // Unused Imbalance Condition 1: Unused ImbalanceCondition 1
    bool unused_imbalance_condition_1() const;
    void set_unused_imbalance_condition_1(bool value);

    // Unused Imbalance Condition 2: Unused ImbalanceCondition 2
    bool unused_imbalance_condition_2() const;
    void set_unused_imbalance_condition_2(bool value);

    // Unused Imbalance Condition 3: Unused ImbalanceCondition 3
    bool unused_imbalance_condition_3() const;
    void set_unused_imbalance_condition_3(bool value);

    // Unused Imbalance Condition 4: Unused ImbalanceCondition 4
    bool unused_imbalance_condition_4() const;
    void set_unused_imbalance_condition_4(bool value);

    // Unused Imbalance Condition 5: Unused ImbalanceCondition 5
    bool unused_imbalance_condition_5() const;
    void set_unused_imbalance_condition_5(bool value);

    // Unused Imbalance Condition 6: Unused ImbalanceCondition 6
    bool unused_imbalance_condition_6() const;
    void set_unused_imbalance_condition_6(bool value);

    // Unused Imbalance Condition 7: Unused ImbalanceCondition 7
    bool unused_imbalance_condition_7() const;
    void set_unused_imbalance_condition_7(bool value);

    // Imbalance More Buyers: ImbalanceMoreBuyers
    bool imbalance_more_buyers() const;
    void set_imbalance_more_buyers(bool value);

    // Imbalance More Sellers: ImbalanceMoreSellers
    bool imbalance_more_sellers() const;
    void set_imbalance_more_sellers(bool value);

    // Reserved 6: 6 reserved bits
    std::uint8_t reserved_6() const;
    void set_reserved_6(std::uint8_t value);

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

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
