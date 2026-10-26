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
#include "../bitfields/MatchEventIndicator.hpp"
#include "../structs/RelatedSymGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// QuoteRequest
class QuoteRequest {
  public:
    static constexpr const char* name = "QuoteRequest";

    // the bytes it reads, which it does not own: they must outlive it
    explicit QuoteRequest(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every QuoteRequest has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 35;
    std::size_t encoded_size() const { return related_sym_groups_end(); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::string_view quote_req_id() const { return view::text(at(8), 23, '\0'); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(31) }; }

    std::span<const std::byte, 3> padding_3() const { return bytes_.subspan(32).template first<3>(); }

    RelatedSymGroups related_sym_groups() const { return RelatedSymGroups{ bytes_.subspan(35) }; }

    void print(std::ostream& out) const {
        out << "QuoteRequest{";
        out << "transact_time=";
        out << transact_time().count();
        out << ", quote_req_id=";
        print::text(out, quote_req_id());
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", padding_3=";
        print::hex(out, padding_3().data(), padding_3().size());
        out << ", related_sym_groups=";
        related_sym_groups().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t related_sym_groups_end() const { return 35 + related_sym_groups().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const QuoteRequest& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
