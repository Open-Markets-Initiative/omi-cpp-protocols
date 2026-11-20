// B3.B3Derivatives.BinaryUmdf.Sbe.v1.6: main.cpp
// B3.B3Derivatives.BinaryUmdf.Sbe.v1.6 benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/b3/b3derivatives/binaryumdf/sbe/v1.6.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/tmp/b3/b3derivatives/binaryumdf/sbe/v1.6/b3_b3derivatives_binaryumdf_sbe_v1_6.hpp"

// B3 B3Derivatives BinaryUmdf Sbe 1.6: the reading of its packets, through its Template Meta Programming header
namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

/////////////////////////////////////////////////////////////////////
// Reading
/////////////////////////////////////////////////////////////////////

namespace tmp {
    // Thrown when the bytes end before what they must hold
    struct short_read : std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    inline void require(std::size_t needed, std::size_t available) {
        if (needed > available) {
            throw short_read(std::to_string(needed) + " bytes needed, " + std::to_string(available) + " available");
        }
    }

    // The bytes left for a member when the members after it take some: refused when fewer remain
    inline std::size_t leaving(std::size_t available, std::size_t taken) {
        require(taken, available);
        return available - taken;
    }

    // Hand the handler a value, when it takes one
    template <typename Handler, typename T>
    constexpr void call(Handler& handler, const T& value) {
        if constexpr (requires { handler(value); }) { handler(value); }
    }

    // A type laid over its bytes, handed to the handler
    template <typename T, typename Handler>
    const T& read(const std::byte* data, std::size_t length, Handler& handler) {
        require(T::size, length);
        const auto& value = *reinterpret_cast<const T*>(data);
        call(handler, value);
        return value;
    }

    // A field as a rule reads it: an enum by the code the wire holds, a field by its value, and a
    // bit - which its bitfield answers as a value - as it is
    template <typename T>
    constexpr auto rule(const T& field) noexcept {
        if constexpr (requires { field.raw(); }) { return field.raw(); }
        else if constexpr (requires { field.value(); }) { return field.value(); }
        else { return field; }
    }

    // A field an optional member may hold, read as its type's zero when the member is absent
    template <typename T>
    struct maybe {
        const T* field;

        constexpr auto value() const noexcept {
            using type = decltype(field->value());
            return field != nullptr ? field->value() : type{};
        }

        constexpr auto raw() const noexcept requires requires(const T& held) { held.raw(); } {
            using type = decltype(field->raw());
            return field != nullptr ? field->raw() : type{};
        }

        // a bit of an optional bitfield, nothing when the bitfield is absent
        template <typename Bit>
        constexpr auto get() const noexcept requires requires(const T& held) { held.template get<Bit>(); } {
            using type = std::remove_cvref_t<decltype(field->template get<Bit>())>;
            return field != nullptr ? type{ field->template get<Bit>() } : type{};
        }
    };

    // A type laid over its bytes without handing it on: a frame's length, read before the frame is
    template <typename T>
    const T& at(const std::byte* data) noexcept {
        return *reinterpret_cast<const T*>(data);
    }

    // A type laid over bytes ahead of the walk, at a place every byte before it fixes, which a rule
    // reads before the walk reaches it: a branch's code in the header its messages begin with
    template <typename T>
    const T& ahead(const std::byte* data, std::size_t length, std::size_t at) {
        require(at + T::size, length);
        return *reinterpret_cast<const T*>(data + at);
    }

    // A type laid over its bytes and handed to the handler; what it returns is the bytes it took
    template <typename T, typename Handler>
    std::size_t take(const std::byte* data, std::size_t length, Handler& handler) {
        read<T>(data, length, handler);
        return T::size;
    }

    // The characters before a terminating zero, which the bytes must hold
    inline std::size_t terminated(const std::byte* data, std::size_t length) {
        for (std::size_t index = 0; index < length; ++index) {
            if (data[index] == std::byte{ 0 }) { return index; }
        }
        throw short_read("no terminator in " + std::to_string(length) + " bytes");
    }

    // The bytes before the first of a field's delimiters, which it leaves for what follows it; at
    // most its maximum, and the bytes must hold a delimiter when they are shorter than that
    template <std::size_t Count>
    std::size_t delimited(const std::byte* data, std::size_t length, std::size_t maximum, const std::array<std::byte, Count>& delimiters) {
        const std::size_t limit = std::min(maximum, length);
        for (std::size_t index = 0; index < limit; ++index) {
            for (const std::byte delimiter : delimiters) {
                if (data[index] == delimiter) { return index; }
            }
        }
        if (limit < length) { return limit; }
        throw short_read("no delimiter in " + std::to_string(length) + " bytes");
    }

    // The bytes of a frame ending on a terminator, the terminator included; none while the bytes
    // do not hold it yet
    inline std::size_t through(const std::byte* data, std::size_t length, std::byte terminator) noexcept {
        for (std::size_t index = 0; index < length; ++index) {
            if (data[index] == terminator) { return index + 1; }
        }
        return 0;
    }

    // Bytes a branch's code selects no message for, handed to the handler when it takes them
    template <typename Handler>
    void unknown(Handler& handler, const std::byte* data, std::size_t length) {
        if constexpr (requires { handler.unknown(data, length); }) { handler.unknown(data, length); }
    }

    // How many a count or a length states: a number, or digits of text
    template <typename T>
        requires std::is_integral_v<T>
    constexpr std::size_t count(T value) noexcept { return static_cast<std::size_t>(value); }

    inline std::size_t count(char digit) {
        if (digit < '0' || digit > '9') { throw short_read(std::string("'") + digit + "' is not a digit"); }
        return static_cast<std::size_t>(digit - '0');
    }

    inline std::size_t count(std::string_view digits) {
        std::size_t value = 0;
        for (const char digit : digits) {
            if (digit == ' ') { continue; }
            if (digit < '0' || digit > '9') { throw short_read("\"" + std::string(digits) + "\" is not a number"); }
            value = value * 10 + static_cast<std::size_t>(digit - '0');
        }
        return value;
    }
} // namespace tmp

/////////////////////////////////////////////////////////////////////
// Parsing
/////////////////////////////////////////////////////////////////////

// Snapshot Full Refresh Orders Mb O 71 Message No M D Entries Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_encoding_ = tmp::read<group_size_encoding>(data + offset, bound - offset, handler); offset += group_size_encoding::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Snapshot Full Refresh Orders Mb O 71 Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_snapshot_full_refresh_orders_mb_o_71_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& snapshot_full_refresh_orders_mb_o_71_message_section_1_ = tmp::read<snapshot_full_refresh_orders_mb_o_71_message_section_1>(data + offset, bound - offset, handler); offset += snapshot_full_refresh_orders_mb_o_71_message_section_1::size;
    offset += parse_snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups(data + offset, bound - offset, handler);
    return offset;
}

// Url Link: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_url_link([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& url_link_section_1_ = tmp::read<url_link_section_1>(data + offset, bound - offset, handler); offset += url_link_section_1::size;
    if (static_cast<bool>(tmp::rule(url_link_section_1_.template get<url_link_length>()) > 0)) {
        {
            const std::size_t size = static_cast<std::size_t>(tmp::rule(url_link_section_1_.template get<url_link_length>()));
            tmp::require(offset + size, bound);
            tmp::call(handler, url_link_data{ data + offset, size });
            offset += size;
        }
    }
    return offset;
}

// Text: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_text([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& text_section_1_ = tmp::read<text_section_1>(data + offset, bound - offset, handler); offset += text_section_1::size;
    if (static_cast<bool>(tmp::rule(text_section_1_.template get<text_length>()) > 0)) {
        {
            const std::size_t size = static_cast<std::size_t>(tmp::rule(text_section_1_.template get<text_length>()));
            tmp::require(offset + size, bound);
            tmp::call(handler, text_data{ data + offset, size });
            offset += size;
        }
    }
    return offset;
}

// Headline: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_headline([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& headline_section_1_ = tmp::read<headline_section_1>(data + offset, bound - offset, handler); offset += headline_section_1::size;
    if (static_cast<bool>(tmp::rule(headline_section_1_.template get<headline_length>()) > 0)) {
        {
            const std::size_t size = static_cast<std::size_t>(tmp::rule(headline_section_1_.template get<headline_length>()));
            tmp::require(offset + size, bound);
            tmp::call(handler, headline_data{ data + offset, size });
            offset += size;
        }
    }
    return offset;
}

// News 5 Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_news_5_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& news_5_message_section_1_ = tmp::read<news_5_message_section_1>(data + offset, bound - offset, handler); offset += news_5_message_section_1::size;
    offset += parse_headline(data + offset, bound - offset, handler);
    offset += parse_text(data + offset, bound - offset, handler);
    offset += parse_url_link(data + offset, bound - offset, handler);
    return offset;
}

// Security Desc: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_security_desc([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& security_desc_section_1_ = tmp::read<security_desc_section_1>(data + offset, bound - offset, handler); offset += security_desc_section_1::size;
    if (static_cast<bool>(tmp::rule(security_desc_section_1_.template get<security_desc_length>()) > 0)) {
        {
            const std::size_t size = static_cast<std::size_t>(tmp::rule(security_desc_section_1_.template get<security_desc_length>()));
            tmp::require(offset + size, bound);
            tmp::call(handler, security_desc_data{ data + offset, size });
            offset += size;
        }
    }
    return offset;
}

// Deprecated Instr Attribs Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_deprecated_instr_attribs_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_encoding_ = tmp::read<group_size_encoding>(data + offset, bound - offset, handler); offset += group_size_encoding::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<deprecated_instr_attribs_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Deprecated Legs Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_deprecated_legs_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_encoding_ = tmp::read<group_size_encoding>(data + offset, bound - offset, handler); offset += group_size_encoding::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<deprecated_legs_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Deprecated Underlyings Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_deprecated_underlyings_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_encoding_ = tmp::read<group_size_encoding>(data + offset, bound - offset, handler); offset += group_size_encoding::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_encoding_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<deprecated_underlyings_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Deprecated Security Definition Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_deprecated_security_definition_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& deprecated_security_definition_message_section_1_ = tmp::read<deprecated_security_definition_message_section_1>(data + offset, bound - offset, handler); offset += deprecated_security_definition_message_section_1::size;
    offset += parse_deprecated_underlyings_groups(data + offset, bound - offset, handler);
    offset += parse_deprecated_legs_groups(data + offset, bound - offset, handler);
    offset += parse_deprecated_instr_attribs_groups(data + offset, bound - offset, handler);
    offset += parse_security_desc(data + offset, bound - offset, handler);
    return offset;
}

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const template_id& template_id_, const block_length& block_length_) {
    if (static_cast<bool>(tmp::rule(template_id_) == 1)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, sequence_reset_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 2)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<sequence_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 3)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<security_status_3_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 10)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<security_group_phase_10_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 4)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_deprecated_security_definition_message(data + offset, bound - offset, handler);
            tmp::call(handler, deprecated_security_definition_message{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 5)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_news_5_message(data + offset, bound - offset, handler);
            tmp::call(handler, news_5_message{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 9)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<empty_book_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 11)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<channel_reset_11_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 15)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<opening_price_15_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 16)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<theoretical_opening_price_16_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 17)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<closing_price_17_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 19)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<auction_imbalance_19_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 20)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<price_band_20_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 21)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<quantity_band_21_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 24)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<high_price_24_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 25)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<low_price_25_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 27)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<last_trade_price_27_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 30)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<snapshot_full_refresh_header_30_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 50)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<order_mb_o_50_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 51)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<delete_order_mb_o_51_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 52)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<mass_delete_orders_mb_o_52_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 53)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<trade_53_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 54)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<forward_trade_54_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 55)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<execution_summary_55_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 56)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<execution_statistics_56_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 57)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<trade_bust_57_message>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 71)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_snapshot_full_refresh_orders_mb_o_71_message(data + offset, bound - offset, handler);
            tmp::call(handler, snapshot_full_refresh_orders_mb_o_71_message{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& message_section_1_ = tmp::read<message_section_1>(data + offset, bound - offset, handler); offset += message_section_1::size;
    bound = static_cast<std::size_t>(tmp::rule(message_section_1_.template get<framing_header>().template get<message_length>()));
    tmp::require(bound, length);
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(message_section_1_.template get<framing_header>().template get<message_length>()))) - 12);
        tmp::require(offset + size, bound);
        parse_payload(data + offset, size, handler, message_section_1_.template get<message_header>().template get<template_id>(), message_section_1_.template get<message_header>().template get<block_length>());
        offset += size;
    }
    return bound;
}

// Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& packet_header_ = tmp::read<packet_header>(data + offset, bound - offset, handler); offset += packet_header::size;
    {
        const std::size_t end = static_cast<std::size_t>(static_cast<std::int64_t>(bound));
        tmp::require(end, bound);
        while (offset < end) {
            [[maybe_unused]] const std::size_t bound = end;
            offset += parse_message(data + offset, bound - offset, handler);
        }
    }
    return offset;
}


} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6

namespace protocol = ::b3::b3derivatives::binaryumdf::sbe::v1_6;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::packet_header& header) {
        if constexpr (requires { header.template get<protocol::channel_id>(); }) { checksum += bench::digest(header.template get<protocol::channel_id>().value()); }
        if constexpr (requires { header.template get<protocol::packet_reserved>(); }) { checksum += bench::digest(header.template get<protocol::packet_reserved>().value()); }
        if constexpr (requires { header.template get<protocol::sequence_version>(); }) { checksum += bench::digest(header.template get<protocol::sequence_version>().value()); }
        if constexpr (requires { header.template get<protocol::sequence_number>(); }) { checksum += bench::digest(header.template get<protocol::sequence_number>().value()); }
        if constexpr (requires { header.template get<protocol::sending_time>(); }) { checksum += bench::digest(header.template get<protocol::sending_time>().value()); }
    }

    void operator()(const protocol::framing_header& header) {
        checksum += index++;
        if constexpr (requires { header.template get<protocol::message_length>(); }) { checksum += bench::digest(header.template get<protocol::message_length>().value()); }
        if constexpr (requires { header.template get<protocol::encoding_type>(); }) { checksum += bench::digest(header.template get<protocol::encoding_type>().value()); }
    }

    void operator()(const protocol::sequence_message& message) {
        if constexpr (requires { message.template get<protocol::next_seq_no>(); }) { checksum += bench::digest(message.template get<protocol::next_seq_no>().value()); }
    }

    void operator()(const protocol::security_status_3_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { checksum += bench::digest(message.template get<protocol::trading_session_id>().value()); }
        if constexpr (requires { message.template get<protocol::security_trading_status>(); }) { checksum += bench::digest(message.template get<protocol::security_trading_status>().value()); }
        if constexpr (requires { message.template get<protocol::security_trading_event>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::security_trading_event>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::security_trading_event>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::trad_ses_open_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trad_ses_open_time>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trad_ses_open_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? bench::digest(message.template get<protocol::rpt_seq>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::security_group_phase_10_message& message) {
        if constexpr (requires { message.template get<protocol::security_group>(); }) { checksum += bench::digest(message.template get<protocol::security_group>().value()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { checksum += bench::digest(message.template get<protocol::trading_session_id>().value()); }
        if constexpr (requires { message.template get<protocol::trading_session_sub_id>(); }) { checksum += bench::digest(message.template get<protocol::trading_session_sub_id>().value()); }
        if constexpr (requires { message.template get<protocol::security_trading_event>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::security_trading_event>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::security_trading_event>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::trad_ses_open_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trad_ses_open_time>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trad_ses_open_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::transact_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::transact_time>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::transact_time>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::deprecated_security_definition_message&) {
    }

    void operator()(const protocol::news_5_message&) {
    }

    void operator()(const protocol::empty_book_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_timestamp>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::channel_reset_11_message& message) {
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_timestamp>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::opening_price_15_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::md_update_action>(); }) { checksum += bench::digest(message.template get<protocol::md_update_action>().value()); }
        if constexpr (requires { message.template get<protocol::open_close_settl_flag>(); }) { checksum += bench::digest(message.template get<protocol::open_close_settl_flag>().value()); }
        if constexpr (requires { message.template get<protocol::md_future_price>(); }) { checksum += bench::digest(message.template get<protocol::md_future_price>().value()); }
        if constexpr (requires { message.template get<protocol::net_chg_prev_day>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::net_chg_prev_day>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::net_chg_prev_day>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_timestamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? bench::digest(message.template get<protocol::rpt_seq>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::theoretical_opening_price_16_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::md_update_action>(); }) { checksum += bench::digest(message.template get<protocol::md_update_action>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::md_corporate_offset_price_optional>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_corporate_offset_price_optional>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::md_corporate_offset_price_optional>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::md_entry_size_optional>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_size_optional>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::md_entry_size_optional>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_timestamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? bench::digest(message.template get<protocol::rpt_seq>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::closing_price_17_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::open_close_settl_flag>(); }) { checksum += bench::digest(message.template get<protocol::open_close_settl_flag>().value()); }
        if constexpr (requires { message.template get<protocol::md_corporate_price>(); }) { checksum += bench::digest(message.template get<protocol::md_corporate_price>().value()); }
        if constexpr (requires { message.template get<protocol::last_trade_date>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::last_trade_date>().value()) != 0x0U ? bench::digest(message.template get<protocol::last_trade_date>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_timestamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? bench::digest(message.template get<protocol::rpt_seq>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::auction_imbalance_19_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::md_update_action>(); }) { checksum += bench::digest(message.template get<protocol::md_update_action>().value()); }
        if constexpr (requires { message.template get<protocol::imbalance_condition>(); }) { checksum += bench::digest(message.template get<protocol::imbalance_condition>().template get<protocol::imbalance_more_buyers>()); }
        if constexpr (requires { message.template get<protocol::imbalance_condition>(); }) { checksum += bench::digest(message.template get<protocol::imbalance_condition>().template get<protocol::imbalance_more_sellers>()); }
        if constexpr (requires { message.template get<protocol::md_entry_size_optional>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_size_optional>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::md_entry_size_optional>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_timestamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? bench::digest(message.template get<protocol::rpt_seq>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::price_band_20_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::price_band_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::price_band_type>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::price_band_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::price_limit_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::price_limit_type>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::price_limit_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::price_band_midpoint_price_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::price_band_midpoint_price_type>().value()) != 0x0FFU ? bench::digest(message.template get<protocol::price_band_midpoint_price_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::low_limit_price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::low_limit_price>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::low_limit_price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::high_limit_price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::high_limit_price>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::high_limit_price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trading_reference_price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trading_reference_price>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::trading_reference_price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_timestamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? bench::digest(message.template get<protocol::rpt_seq>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::quantity_band_21_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::avg_daily_traded_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::avg_daily_traded_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::avg_daily_traded_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::max_trade_vol>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::max_trade_vol>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::max_trade_vol>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_timestamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? bench::digest(message.template get<protocol::rpt_seq>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::high_price_24_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::md_update_action>(); }) { checksum += bench::digest(message.template get<protocol::md_update_action>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::md_future_price>(); }) { checksum += bench::digest(message.template get<protocol::md_future_price>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_timestamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? bench::digest(message.template get<protocol::rpt_seq>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::low_price_25_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::md_update_action>(); }) { checksum += bench::digest(message.template get<protocol::md_update_action>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::md_future_price>(); }) { checksum += bench::digest(message.template get<protocol::md_future_price>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_timestamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? bench::digest(message.template get<protocol::rpt_seq>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::last_trade_price_27_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { checksum += bench::digest(message.template get<protocol::trading_session_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::opening_price>()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::crossed>()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::last_trade_at_the_same_price>()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::out_of_sequence>()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::trade_on_behalf>()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::regular_trade>()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::block_trade>()); }
        if constexpr (requires { message.template get<protocol::md_future_price>(); }) { checksum += bench::digest(message.template get<protocol::md_future_price>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_size>(); }) { checksum += bench::digest(message.template get<protocol::md_entry_size>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { checksum += bench::digest(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_buyer>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::md_entry_buyer>().value()) != 0x0U ? bench::digest(message.template get<protocol::md_entry_buyer>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::md_entry_seller>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::md_entry_seller>().value()) != 0x0U ? bench::digest(message.template get<protocol::md_entry_seller>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_timestamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? bench::digest(message.template get<protocol::rpt_seq>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::seller_days>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::seller_days>().value()) != 0x0U ? bench::digest(message.template get<protocol::seller_days>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::md_entry_interest_rate>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_interest_rate>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_interest_rate>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trd_sub_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::trd_sub_type>().value()) != 0x0U ? bench::digest(message.template get<protocol::trd_sub_type>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::snapshot_full_refresh_header_30_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::last_msg_seq_num_processed>(); }) { checksum += bench::digest(message.template get<protocol::last_msg_seq_num_processed>().value()); }
        if constexpr (requires { message.template get<protocol::tot_num_reports>(); }) { checksum += bench::digest(message.template get<protocol::tot_num_reports>().value()); }
        if constexpr (requires { message.template get<protocol::tot_num_bids>(); }) { checksum += bench::digest(message.template get<protocol::tot_num_bids>().value()); }
        if constexpr (requires { message.template get<protocol::tot_num_offers>(); }) { checksum += bench::digest(message.template get<protocol::tot_num_offers>().value()); }
        if constexpr (requires { message.template get<protocol::tot_num_stats>(); }) { checksum += bench::digest(message.template get<protocol::tot_num_stats>().value()); }
        if constexpr (requires { message.template get<protocol::last_rpt_seq>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::last_rpt_seq>().value()) != 0x0U ? bench::digest(message.template get<protocol::last_rpt_seq>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::order_mb_o_50_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::md_update_action>(); }) { checksum += bench::digest(message.template get<protocol::md_update_action>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_type>(); }) { checksum += bench::digest(message.template get<protocol::md_entry_type>().value()); }
        if constexpr (requires { message.template get<protocol::md_corporate_offset_price_optional>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_corporate_offset_price_optional>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::md_corporate_offset_price_optional>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::md_entry_size>(); }) { checksum += bench::digest(message.template get<protocol::md_entry_size>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_position_no>(); }) { checksum += bench::digest(message.template get<protocol::md_entry_position_no>().value()); }
        if constexpr (requires { message.template get<protocol::entering_firm>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::entering_firm>().value()) != 0x0U ? bench::digest(message.template get<protocol::entering_firm>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::md_insert_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_insert_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_insert_timestamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::secondary_order_id>(); }) { checksum += bench::digest(message.template get<protocol::secondary_order_id>().value()); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? bench::digest(message.template get<protocol::rpt_seq>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_timestamp>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::delete_order_mb_o_51_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::md_entry_type>(); }) { checksum += bench::digest(message.template get<protocol::md_entry_type>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_position_no>(); }) { checksum += bench::digest(message.template get<protocol::md_entry_position_no>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_size_optional>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_size_optional>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::md_entry_size_optional>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::secondary_order_id>(); }) { checksum += bench::digest(message.template get<protocol::secondary_order_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_timestamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? bench::digest(message.template get<protocol::rpt_seq>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::mass_delete_orders_mb_o_52_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::md_update_action>(); }) { checksum += bench::digest(message.template get<protocol::md_update_action>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_type>(); }) { checksum += bench::digest(message.template get<protocol::md_entry_type>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_position_no>(); }) { checksum += bench::digest(message.template get<protocol::md_entry_position_no>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_timestamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? bench::digest(message.template get<protocol::rpt_seq>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::trade_53_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { checksum += bench::digest(message.template get<protocol::trading_session_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::opening_price>()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::crossed>()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::last_trade_at_the_same_price>()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::out_of_sequence>()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::trade_on_behalf>()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::regular_trade>()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::block_trade>()); }
        if constexpr (requires { message.template get<protocol::md_future_price>(); }) { checksum += bench::digest(message.template get<protocol::md_future_price>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_size>(); }) { checksum += bench::digest(message.template get<protocol::md_entry_size>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { checksum += bench::digest(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_buyer>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::md_entry_buyer>().value()) != 0x0U ? bench::digest(message.template get<protocol::md_entry_buyer>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::md_entry_seller>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::md_entry_seller>().value()) != 0x0U ? bench::digest(message.template get<protocol::md_entry_seller>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::trd_sub_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::trd_sub_type>().value()) != 0x0U ? bench::digest(message.template get<protocol::trd_sub_type>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_timestamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? bench::digest(message.template get<protocol::rpt_seq>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::forward_trade_54_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { checksum += bench::digest(message.template get<protocol::trading_session_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::opening_price>()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::crossed>()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::last_trade_at_the_same_price>()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::out_of_sequence>()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::trade_on_behalf>()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::regular_trade>()); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { checksum += bench::digest(message.template get<protocol::trade_condition>().template get<protocol::block_trade>()); }
        if constexpr (requires { message.template get<protocol::md_future_price>(); }) { checksum += bench::digest(message.template get<protocol::md_future_price>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_size>(); }) { checksum += bench::digest(message.template get<protocol::md_entry_size>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { checksum += bench::digest(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_buyer>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::md_entry_buyer>().value()) != 0x0U ? bench::digest(message.template get<protocol::md_entry_buyer>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::md_entry_seller>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::md_entry_seller>().value()) != 0x0U ? bench::digest(message.template get<protocol::md_entry_seller>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_timestamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? bench::digest(message.template get<protocol::rpt_seq>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::seller_days>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::seller_days>().value()) != 0x0U ? bench::digest(message.template get<protocol::seller_days>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::md_entry_interest_rate>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_interest_rate>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_interest_rate>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trd_sub_type>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::trd_sub_type>().value()) != 0x0U ? bench::digest(message.template get<protocol::trd_sub_type>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::execution_summary_55_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::aggressor_side>(); }) { checksum += bench::digest(message.template get<protocol::aggressor_side>().value()); }
        if constexpr (requires { message.template get<protocol::last_px>(); }) { checksum += bench::digest(message.template get<protocol::last_px>().value()); }
        if constexpr (requires { message.template get<protocol::fill_qty>(); }) { checksum += bench::digest(message.template get<protocol::fill_qty>().value()); }
        if constexpr (requires { message.template get<protocol::traded_hidden_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::traded_hidden_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::traded_hidden_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::cxl_qty>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::cxl_qty>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::cxl_qty>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::aggressor_time>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::aggressor_time>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::aggressor_time>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? bench::digest(message.template get<protocol::rpt_seq>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_timestamp>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::execution_statistics_56_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { checksum += bench::digest(message.template get<protocol::trading_session_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::trade_volume>(); }) { checksum += bench::digest(message.template get<protocol::trade_volume>().value()); }
        if constexpr (requires { message.template get<protocol::vwap_px>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::vwap_px>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::vwap_px>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::net_chg_prev_day>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::net_chg_prev_day>().value()) != 0x08000000000000000ULL ? bench::digest(message.template get<protocol::net_chg_prev_day>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::number_of_trades>(); }) { checksum += bench::digest(message.template get<protocol::number_of_trades>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_timestamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? bench::digest(message.template get<protocol::rpt_seq>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::trade_bust_57_message& message) {
        if constexpr (requires { message.template get<protocol::security_id>(); }) { checksum += bench::digest(message.template get<protocol::security_id>().value()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_trade_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_volume_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_quote_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_stats_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::last_implied_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::recovery_msg>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::unused>()); }
        if constexpr (requires { message.template get<protocol::match_event_indicator>(); }) { checksum += bench::digest(message.template get<protocol::match_event_indicator>().template get<protocol::end_of_event>()); }
        if constexpr (requires { message.template get<protocol::trading_session_id>(); }) { checksum += bench::digest(message.template get<protocol::trading_session_id>().value()); }
        if constexpr (requires { message.template get<protocol::md_future_price>(); }) { checksum += bench::digest(message.template get<protocol::md_future_price>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_size>(); }) { checksum += bench::digest(message.template get<protocol::md_entry_size>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { checksum += bench::digest(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += bench::digest(message.template get<protocol::trade_date>().value()); }
        if constexpr (requires { message.template get<protocol::md_entry_timestamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::md_entry_timestamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::md_entry_timestamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::rpt_seq>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::rpt_seq>().value()) != 0x0U ? bench::digest(message.template get<protocol::rpt_seq>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::snapshot_full_refresh_orders_mb_o_71_message&) {
    }
};

// The values the Tmp reading reads from one datagram, folded into a checksum. A datagram it cannot read
// is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::parse_packet(frame.payload, frame.payload_len, reader);
    } catch (const std::exception& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("B3.B3Derivatives.BinaryUmdf.Sbe.v1.6", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
