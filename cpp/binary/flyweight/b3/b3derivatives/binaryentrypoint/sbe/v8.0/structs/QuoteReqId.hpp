#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// quoteReqID data struct
class QuoteReqId {
  public:
    static constexpr const char* name = "QuoteReqId";

    // the bytes it reads, which it does not own: they must outlive it
    explicit QuoteReqId(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every QuoteReqId has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return quote_req_id_data_end(); }

    std::uint8_t quote_req_id_length() const { return wire::read_u8(at(0)); }

    std::size_t quote_req_id_data_size() const { return wire::count(quote_req_id_length()); }
    std::string_view quote_req_id_data() const {
        wire::require("QuoteReqId", 1 + quote_req_id_data_size(), bytes_.size());
        return view::characters(at(1), quote_req_id_data_size());
    }

    void print(std::ostream& out) const {
        out << "QuoteReqId{";
        out << "quote_req_id_length=";
        out << static_cast<int>(quote_req_id_length());
        out << ", quote_req_id_data=";
        print::text(out, quote_req_id_data());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t quote_req_id_data_end() const { return 1 + quote_req_id_data_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const QuoteReqId& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
