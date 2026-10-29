#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Published when the order book is expected to be emptied.
class OrderMassDeleteMessage {
  public:
    static constexpr const char* name = "OrderMassDeleteMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderMassDeleteMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderMassDeleteMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::int64_t security_id() const { return wire::read_i64_le(at(0)); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(8)))); }

    void print(std::ostream& out) const {
        out << "OrderMassDeleteMessage{";
        out << "security_id=";
        out << security_id();
        out << ", transact_time=";
        out << transact_time().count();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderMassDeleteMessage& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
