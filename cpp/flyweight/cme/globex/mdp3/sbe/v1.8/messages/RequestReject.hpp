#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MdReqRejReason.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// RequestReject
class RequestReject {
  public:
    static constexpr const char* name = "RequestReject";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RequestReject(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RequestReject has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 105;
    static constexpr std::size_t fixed_size = 105;
    std::size_t encoded_size() const { return 105; }

    std::optional<std::uint32_t> md_req_id_optional() const { return wire::nullable(wire::read_u32_le(at(0)), static_cast<std::uint32_t>(4294967295ULL)); }

    MdReqRejReason md_req_rej_reason() const { return static_cast<MdReqRejReason>(wire::read_u8(at(4))); }

    std::string_view text() const { return view::text(at(5), 100, '\0'); }

    void print(std::ostream& out) const {
        out << "RequestReject{";
        out << "md_req_id_optional=";
        print::optional(out, md_req_id_optional());
        out << ", md_req_rej_reason=";
        out << md_req_rej_reason();
        out << ", text=";
        print::text(out, text());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RequestReject& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
