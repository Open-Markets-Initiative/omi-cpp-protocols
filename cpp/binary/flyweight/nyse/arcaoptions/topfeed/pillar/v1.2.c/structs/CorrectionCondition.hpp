#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Transaction.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Correction Condition
class CorrectionCondition {
  public:
    static constexpr const char* name = "CorrectionCondition";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CorrectionCondition(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CorrectionCondition has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 4;
    static constexpr std::size_t fixed_size = 4;
    std::size_t encoded_size() const { return 4; }

    Transaction transaction() const { return static_cast<Transaction>(wire::read_char(at(0))); }

    std::span<const std::byte, 3> reserved_3() const { return bytes_.subspan(1).template first<3>(); }

    void print(std::ostream& out) const {
        out << "CorrectionCondition{";
        out << "transaction=";
        out << transaction();
        out << ", reserved_3=";
        print::hex(out, reserved_3().data(), reserved_3().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CorrectionCondition& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
