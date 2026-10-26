#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ResetStartEndFlag.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// A tag requesting the resetting (i.e. cancellation) of all distributed information. When the
// user receives this tag, the user must clear all valid A tags.
class ResetMessage {
  public:
    static constexpr const char* name = "ResetMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ResetMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ResetMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    ResetStartEndFlag reset_start_end_flag() const { return static_cast<ResetStartEndFlag>(wire::read_u8(at(0))); }

    void print(std::ostream& out) const {
        out << "ResetMessage{";
        out << "reset_start_end_flag=";
        out << reset_start_end_flag();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ResetMessage& value) {
    value.print(out);
    return out;
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
