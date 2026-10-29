#pragma once

#include <array>
#include <cstddef>
#include <ostream>

#include "../enums/Transaction.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Correction Condition
class CorrectionCondition {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 4;

    CorrectionCondition() = default;
    CorrectionCondition(Transaction transaction, const std::array<std::byte, 3>& reserved_3);

    // Transaction: Settlement related conditions. Valid values:
    Transaction transaction() const;
    void set_transaction(Transaction value);

    // Reserved 3: Reserved for future use
    const std::array<std::byte, 3>& reserved_3() const;
    std::array<std::byte, 3>& reserved_3();
    void set_reserved_3(const std::array<std::byte, 3>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const CorrectionCondition& other) const;
    bool operator!=(const CorrectionCondition& other) const;

  private:
    Transaction transaction_{};
    std::array<std::byte, 3> reserved_3_{};
};

std::ostream& operator<<(std::ostream& out, const CorrectionCondition& value);

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
