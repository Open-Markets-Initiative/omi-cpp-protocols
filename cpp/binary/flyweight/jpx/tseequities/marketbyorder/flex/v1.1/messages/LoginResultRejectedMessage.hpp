#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ResultCode.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Tcp login response rejecting the request. Same layout as the accepted response; Result Code
// carries the reason the request failed.
class LoginResultRejectedMessage {
  public:
    static constexpr const char* name = "LoginResultRejectedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LoginResultRejectedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LoginResultRejectedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 2;
    static constexpr std::size_t fixed_size = 2;
    std::size_t encoded_size() const { return 2; }

    std::uint8_t multicast_group_number() const { return wire::read_u8(at(0)); }

    ResultCode result_code() const { return static_cast<ResultCode>(wire::read_char(at(1))); }

    void print(std::ostream& out) const {
        out << "LoginResultRejectedMessage{";
        out << "multicast_group_number=";
        out << static_cast<int>(multicast_group_number());
        out << ", result_code=";
        out << result_code();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LoginResultRejectedMessage& value) {
    value.print(out);
    return out;
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
