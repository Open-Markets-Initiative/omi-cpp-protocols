#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ErrorCodes.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// NegotiationReject
class NegotiationReject {
  public:
    static constexpr const char* name = "NegotiationReject";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NegotiationReject(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every NegotiationReject has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 70;
    static constexpr std::size_t fixed_size = 70;
    std::size_t encoded_size() const { return 70; }

    std::string_view reason() const { return view::text(at(0), 48, '\0'); }

    std::uint64_t uuid() const { return wire::read_u64_le(at(48)); }

    std::chrono::nanoseconds request_timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(56)))); }

    ErrorCodes error_codes() const { return static_cast<ErrorCodes>(wire::read_u8(at(64))); }

    std::span<const std::byte, 5> padding_5() const { return bytes_.subspan(65).template first<5>(); }

    void print(std::ostream& out) const {
        out << "NegotiationReject{";
        out << "reason=";
        print::text(out, reason());
        out << ", uuid=";
        out << uuid();
        out << ", request_timestamp=";
        out << request_timestamp().count();
        out << ", error_codes=";
        out << error_codes();
        out << ", padding_5=";
        print::hex(out, padding_5().data(), padding_5().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const NegotiationReject& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
