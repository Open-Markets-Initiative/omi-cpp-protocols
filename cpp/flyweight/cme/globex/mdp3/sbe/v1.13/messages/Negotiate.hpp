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

namespace cme::globex::mdp3::sbe::v1_13 {

// Negotiate
class Negotiate {
  public:
    static constexpr const char* name = "Negotiate";

    // the bytes it reads, which it does not own: they must outlive it
    explicit Negotiate(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every Negotiate has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 78;
    static constexpr std::size_t fixed_size = 78;
    std::size_t encoded_size() const { return 78; }

    std::string_view hmac_signature() const { return view::text(at(0), 32, '\0'); }

    std::string_view access_key_id() const { return view::text(at(32), 20, '\0'); }

    std::uint64_t uuid() const { return wire::read_u64_le(at(52)); }

    std::chrono::nanoseconds request_timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(60)))); }

    std::string_view session() const { return view::text(at(68), 5, '\0'); }

    std::string_view firm() const { return view::text(at(73), 5, '\0'); }

    void print(std::ostream& out) const {
        out << "Negotiate{";
        out << "hmac_signature=";
        print::text(out, hmac_signature());
        out << ", access_key_id=";
        print::text(out, access_key_id());
        out << ", uuid=";
        out << uuid();
        out << ", request_timestamp=";
        out << request_timestamp().count();
        out << ", session=";
        print::text(out, session());
        out << ", firm=";
        print::text(out, firm());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const Negotiate& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
