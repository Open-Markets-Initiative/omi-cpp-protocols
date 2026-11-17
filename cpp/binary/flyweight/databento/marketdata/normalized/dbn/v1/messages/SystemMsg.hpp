// Databento.MarketData.Normalized.Dbn.v1: messages/SystemMsg.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

// A non-error message from the Databento Live Subscription Gateway (LSG); also used for
// heartbeating
class SystemMsg {
  public:
    static constexpr const char* name = "SystemMsg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SystemMsg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SystemMsg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 64;
    static constexpr std::size_t fixed_size = 64;
    std::size_t encoded_size() const { return 64; }

    std::string_view msg() const { return view::text(at(0), 64, '\0'); }

    void print(std::ostream& out) const {
        out << "SystemMsg{";
        out << "msg=";
        print::text(out, msg());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SystemMsg& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v1
