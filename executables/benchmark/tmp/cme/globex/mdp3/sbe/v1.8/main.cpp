// Cme.Globex.Mdp3.Sbe.v1.8: main.cpp
// Cme.Globex.Mdp3.Sbe.v1.8 benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/cme/globex/mdp3/sbe/v1.8.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/tmp/cme/globex/mdp3/sbe/v1.8/cme_globex_mdp3_sbe_v1_8.hpp"

// Cme Globex Mdp3 Sbe 1.8: the reading of its packets, through its Template Meta Programming header
namespace cme::globex::mdp3::sbe::v1_8 {

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

// Request Ack Related Symbol Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_request_ack_related_symbol_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<request_ack_related_symbol_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Request Ack Security Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_request_ack_security_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<request_ack_security_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Request Ack: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_request_ack([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& request_ack_section_1_ = tmp::read<request_ack_section_1>(data + offset, bound - offset, handler); offset += request_ack_section_1::size;
    offset += parse_request_ack_security_groups(data + offset, bound - offset, handler);
    offset += parse_request_ack_related_symbol_groups(data + offset, bound - offset, handler);
    return offset;
}

// Snapshot Full Refresh Order Book Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_snapshot_full_refresh_order_book_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<snapshot_full_refresh_order_book_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Snapshot Full Refresh Order Book: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_snapshot_full_refresh_order_book([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& snapshot_full_refresh_order_book_section_1_ = tmp::read<snapshot_full_refresh_order_book_section_1>(data + offset, bound - offset, handler); offset += snapshot_full_refresh_order_book_section_1::size;
    offset += parse_snapshot_full_refresh_order_book_groups(data + offset, bound - offset, handler);
    return offset;
}

// Incremental Refresh Order Book Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_incremental_refresh_order_book_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<incremental_refresh_order_book_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Md Incremental Refresh Order Book: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_md_incremental_refresh_order_book([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& md_incremental_refresh_order_book_section_1_ = tmp::read<md_incremental_refresh_order_book_section_1>(data + offset, bound - offset, handler); offset += md_incremental_refresh_order_book_section_1::size;
    offset += parse_incremental_refresh_order_book_groups(data + offset, bound - offset, handler);
    return offset;
}

// Incremental Refresh Trade Summary Order Id Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_incremental_refresh_trade_summary_order_id_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_8_byte_ = tmp::read<group_size_8_byte>(data + offset, bound - offset, handler); offset += group_size_8_byte::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_8_byte_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_8_byte_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<incremental_refresh_trade_summary_order_id_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Incremental Refresh Trade Summary Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_incremental_refresh_trade_summary_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<incremental_refresh_trade_summary_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Md Incremental Refresh Trade Summary: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_md_incremental_refresh_trade_summary([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& md_incremental_refresh_trade_summary_section_1_ = tmp::read<md_incremental_refresh_trade_summary_section_1>(data + offset, bound - offset, handler); offset += md_incremental_refresh_trade_summary_section_1::size;
    offset += parse_incremental_refresh_trade_summary_groups(data + offset, bound - offset, handler);
    offset += parse_incremental_refresh_trade_summary_order_id_groups(data + offset, bound - offset, handler);
    return offset;
}

// Option Related Instruments Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_option_related_instruments_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<option_related_instruments_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Option Underlyings Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_option_underlyings_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<option_underlyings_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Lot Type Rules Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_lot_type_rules_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<lot_type_rules_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Inst Attrib Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_inst_attrib_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<inst_attrib_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Feed Types Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_feed_types_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<feed_types_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Events Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_events_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<events_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Md Instrument Definition Option: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_md_instrument_definition_option([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& md_instrument_definition_option_section_1_ = tmp::read<md_instrument_definition_option_section_1>(data + offset, bound - offset, handler); offset += md_instrument_definition_option_section_1::size;
    offset += parse_events_groups(data + offset, bound - offset, handler);
    offset += parse_feed_types_groups(data + offset, bound - offset, handler);
    offset += parse_inst_attrib_groups(data + offset, bound - offset, handler);
    offset += parse_lot_type_rules_groups(data + offset, bound - offset, handler);
    offset += parse_option_underlyings_groups(data + offset, bound - offset, handler);
    offset += parse_option_related_instruments_groups(data + offset, bound - offset, handler);
    return offset;
}

// Related Sym Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_related_sym_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<related_sym_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Quote Request: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_quote_request([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& quote_request_section_1_ = tmp::read<quote_request_section_1>(data + offset, bound - offset, handler); offset += quote_request_section_1::size;
    offset += parse_related_sym_groups(data + offset, bound - offset, handler);
    return offset;
}

// Snapshot Full Refresh Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_snapshot_full_refresh_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<snapshot_full_refresh_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Snapshot Full Refresh: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_snapshot_full_refresh([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& snapshot_full_refresh_section_1_ = tmp::read<snapshot_full_refresh_section_1>(data + offset, bound - offset, handler); offset += snapshot_full_refresh_section_1::size;
    offset += parse_snapshot_full_refresh_groups(data + offset, bound - offset, handler);
    return offset;
}

// Incremental Refresh Volume Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_incremental_refresh_volume_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<incremental_refresh_volume_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Md Incremental Refresh Volume: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_md_incremental_refresh_volume([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& md_incremental_refresh_volume_section_1_ = tmp::read<md_incremental_refresh_volume_section_1>(data + offset, bound - offset, handler); offset += md_incremental_refresh_volume_section_1::size;
    offset += parse_incremental_refresh_volume_groups(data + offset, bound - offset, handler);
    return offset;
}

// Incremental Refresh Trade Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_incremental_refresh_trade_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<incremental_refresh_trade_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Md Incremental Refresh Trade: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_md_incremental_refresh_trade([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& md_incremental_refresh_trade_section_1_ = tmp::read<md_incremental_refresh_trade_section_1>(data + offset, bound - offset, handler); offset += md_incremental_refresh_trade_section_1::size;
    offset += parse_incremental_refresh_trade_groups(data + offset, bound - offset, handler);
    return offset;
}

// Incremental Refresh Session Statistics Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_incremental_refresh_session_statistics_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<incremental_refresh_session_statistics_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Md Incremental Refresh Session Statistics: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_md_incremental_refresh_session_statistics([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& md_incremental_refresh_session_statistics_section_1_ = tmp::read<md_incremental_refresh_session_statistics_section_1>(data + offset, bound - offset, handler); offset += md_incremental_refresh_session_statistics_section_1::size;
    offset += parse_incremental_refresh_session_statistics_groups(data + offset, bound - offset, handler);
    return offset;
}

// Incremental Refresh Limits Banding Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_incremental_refresh_limits_banding_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<incremental_refresh_limits_banding_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Md Incremental Refresh Limits Banding: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_md_incremental_refresh_limits_banding([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& md_incremental_refresh_limits_banding_section_1_ = tmp::read<md_incremental_refresh_limits_banding_section_1>(data + offset, bound - offset, handler); offset += md_incremental_refresh_limits_banding_section_1::size;
    offset += parse_incremental_refresh_limits_banding_groups(data + offset, bound - offset, handler);
    return offset;
}

// Incremental Refresh Daily Statistics Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_incremental_refresh_daily_statistics_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<incremental_refresh_daily_statistics_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Md Incremental Refresh Daily Statistics: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_md_incremental_refresh_daily_statistics([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& md_incremental_refresh_daily_statistics_section_1_ = tmp::read<md_incremental_refresh_daily_statistics_section_1>(data + offset, bound - offset, handler); offset += md_incremental_refresh_daily_statistics_section_1::size;
    offset += parse_incremental_refresh_daily_statistics_groups(data + offset, bound - offset, handler);
    return offset;
}

// Incremental Refresh Book Order Id Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_incremental_refresh_book_order_id_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_8_byte_ = tmp::read<group_size_8_byte>(data + offset, bound - offset, handler); offset += group_size_8_byte::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_8_byte_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_8_byte_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<incremental_refresh_book_order_id_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Incremental Refresh Book Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_incremental_refresh_book_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<incremental_refresh_book_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Md Incremental Refresh Book: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_md_incremental_refresh_book([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& md_incremental_refresh_book_section_1_ = tmp::read<md_incremental_refresh_book_section_1>(data + offset, bound - offset, handler); offset += md_incremental_refresh_book_section_1::size;
    offset += parse_incremental_refresh_book_groups(data + offset, bound - offset, handler);
    offset += parse_incremental_refresh_book_order_id_groups(data + offset, bound - offset, handler);
    return offset;
}

// Legacy Legs Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_legacy_legs_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<legacy_legs_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Md Instrument Definition Spread: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_md_instrument_definition_spread([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& md_instrument_definition_spread_section_1_ = tmp::read<md_instrument_definition_spread_section_1>(data + offset, bound - offset, handler); offset += md_instrument_definition_spread_section_1::size;
    offset += parse_events_groups(data + offset, bound - offset, handler);
    offset += parse_feed_types_groups(data + offset, bound - offset, handler);
    offset += parse_inst_attrib_groups(data + offset, bound - offset, handler);
    offset += parse_lot_type_rules_groups(data + offset, bound - offset, handler);
    offset += parse_legacy_legs_groups(data + offset, bound - offset, handler);
    return offset;
}

// Md Instrument Definition Future: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_md_instrument_definition_future([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& md_instrument_definition_future_section_1_ = tmp::read<md_instrument_definition_future_section_1>(data + offset, bound - offset, handler); offset += md_instrument_definition_future_section_1::size;
    offset += parse_events_groups(data + offset, bound - offset, handler);
    offset += parse_feed_types_groups(data + offset, bound - offset, handler);
    offset += parse_inst_attrib_groups(data + offset, bound - offset, handler);
    offset += parse_lot_type_rules_groups(data + offset, bound - offset, handler);
    return offset;
}

// Channel Reset Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_channel_reset_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<channel_reset_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Channel Reset: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_channel_reset([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& channel_reset_section_1_ = tmp::read<channel_reset_section_1>(data + offset, bound - offset, handler); offset += channel_reset_section_1::size;
    offset += parse_channel_reset_groups(data + offset, bound - offset, handler);
    return offset;
}

// Server Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_server_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const template_id& template_id_, const block_length& block_length_) {
    if (static_cast<bool>(tmp::rule(template_id_) == 4)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_channel_reset(data + offset, bound - offset, handler);
            tmp::call(handler, channel_reset{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 12)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, admin_heartbeat{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 15)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<admin_login>(data + offset, bound - offset, handler);
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
            offset += tmp::take<admin_logout>(data + offset, bound - offset, handler);
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
            offset += parse_md_instrument_definition_future(data + offset, bound - offset, handler);
            tmp::call(handler, md_instrument_definition_future{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 29)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_instrument_definition_spread(data + offset, bound - offset, handler);
            tmp::call(handler, md_instrument_definition_spread{});
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
            offset += tmp::take<security_status>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 32)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_incremental_refresh_book(data + offset, bound - offset, handler);
            tmp::call(handler, md_incremental_refresh_book{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 33)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_incremental_refresh_daily_statistics(data + offset, bound - offset, handler);
            tmp::call(handler, md_incremental_refresh_daily_statistics{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 34)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_incremental_refresh_limits_banding(data + offset, bound - offset, handler);
            tmp::call(handler, md_incremental_refresh_limits_banding{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 35)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_incremental_refresh_session_statistics(data + offset, bound - offset, handler);
            tmp::call(handler, md_incremental_refresh_session_statistics{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 36)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_incremental_refresh_trade(data + offset, bound - offset, handler);
            tmp::call(handler, md_incremental_refresh_trade{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 37)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_incremental_refresh_volume(data + offset, bound - offset, handler);
            tmp::call(handler, md_incremental_refresh_volume{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 38)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_snapshot_full_refresh(data + offset, bound - offset, handler);
            tmp::call(handler, snapshot_full_refresh{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 39)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_quote_request(data + offset, bound - offset, handler);
            tmp::call(handler, quote_request{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 41)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_instrument_definition_option(data + offset, bound - offset, handler);
            tmp::call(handler, md_instrument_definition_option{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 42)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_incremental_refresh_trade_summary(data + offset, bound - offset, handler);
            tmp::call(handler, md_incremental_refresh_trade_summary{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 43)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_incremental_refresh_order_book(data + offset, bound - offset, handler);
            tmp::call(handler, md_incremental_refresh_order_book{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 44)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_snapshot_full_refresh_order_book(data + offset, bound - offset, handler);
            tmp::call(handler, snapshot_full_refresh_order_book{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 201)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<negotiation_reject>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 202)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<negotiation_response>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 203)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<terminate>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 206)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_request_ack(data + offset, bound - offset, handler);
            tmp::call(handler, request_ack{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 207)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<request_reject>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Server Tcp Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_server_tcp_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& message_header_ = tmp::read<message_header>(data + offset, bound - offset, handler); offset += message_header::size;
    offset += parse_server_payload(data + offset, bound - offset, handler, message_header_.template get<simple_binary_header>().template get<template_id>(), message_header_.template get<simple_binary_header>().template get<block_length>());
    return offset;
}

// Server Tcp Frame: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_server_tcp_frame([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& server_technical_header_ = tmp::read<server_technical_header>(data + offset, bound - offset, handler); offset += server_technical_header::size;
    offset += parse_server_tcp_message(data + offset, bound - offset, handler);
    bound = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(tmp::ahead<message_size>(data, length, 14)))) + 14);
    tmp::require(bound, length);
    return bound;
}

// Server Tcp Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_server_tcp_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    while (offset < bound) {
        if (bound - offset < 14 + message_size::size) { return offset; }
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(tmp::at<message_size>(data + offset + 14)))) + 14);
        if (bound - offset < size) { return offset; }
        parse_server_tcp_frame(data + offset, size, handler);
        offset += size;
    }
    return offset;
}

// Security Status Request Related Symbol Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_security_status_request_related_symbol_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<security_status_request_related_symbol_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Security Status Request Security Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_security_status_request_security_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<security_status_request_security_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Security Status Request: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_security_status_request([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& security_status_request_section_1_ = tmp::read<security_status_request_section_1>(data + offset, bound - offset, handler); offset += security_status_request_section_1::size;
    offset += parse_security_status_request_security_groups(data + offset, bound - offset, handler);
    offset += parse_security_status_request_related_symbol_groups(data + offset, bound - offset, handler);
    return offset;
}

// Security List Request Related Symbol Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_security_list_request_related_symbol_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<security_list_request_related_symbol_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Security List Request Security Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_security_list_request_security_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<security_list_request_security_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Security List Request: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_security_list_request([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& security_list_request_section_1_ = tmp::read<security_list_request_section_1>(data + offset, bound - offset, handler); offset += security_list_request_section_1::size;
    offset += parse_security_list_request_security_groups(data + offset, bound - offset, handler);
    offset += parse_security_list_request_related_symbol_groups(data + offset, bound - offset, handler);
    return offset;
}

// Market Data Request Related Symbol Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_market_data_request_related_symbol_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<market_data_request_related_symbol_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Market Data Request Security Groups: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_market_data_request_security_groups([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& group_size_ = tmp::read<group_size>(data + offset, bound - offset, handler); offset += group_size::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(group_size_.template get<num_in_group>()));
        while (count-- > 0) {
            {
                const std::size_t block = static_cast<std::size_t>(tmp::rule(group_size_.template get<block_length>()));
                const std::size_t start = offset;
                offset += tmp::take<market_data_request_security_group>(data + offset, bound - offset, handler);
                if (offset - start < block) { offset = start + block; }
                tmp::require(offset, bound);
            }
        }
    }
    return offset;
}

// Market Data Request: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_market_data_request([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& market_data_request_section_1_ = tmp::read<market_data_request_section_1>(data + offset, bound - offset, handler); offset += market_data_request_section_1::size;
    offset += parse_market_data_request_security_groups(data + offset, bound - offset, handler);
    offset += parse_market_data_request_related_symbol_groups(data + offset, bound - offset, handler);
    return offset;
}

// Client Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_client_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const template_id& template_id_, const block_length& block_length_) {
    if (static_cast<bool>(tmp::rule(template_id_) == 200)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<negotiate>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 203)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<terminate>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 205)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_market_data_request(data + offset, bound - offset, handler);
            tmp::call(handler, market_data_request{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 208)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_security_list_request(data + offset, bound - offset, handler);
            tmp::call(handler, security_list_request{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 209)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_security_status_request(data + offset, bound - offset, handler);
            tmp::call(handler, security_status_request{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 210)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, subscriber_heartbeat{});
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Client Tcp Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_client_tcp_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& message_header_ = tmp::read<message_header>(data + offset, bound - offset, handler); offset += message_header::size;
    offset += parse_client_payload(data + offset, bound - offset, handler, message_header_.template get<simple_binary_header>().template get<template_id>(), message_header_.template get<simple_binary_header>().template get<block_length>());
    return offset;
}

// Client Tcp Frame: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_client_tcp_frame([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& client_technical_header_ = tmp::read<client_technical_header>(data + offset, bound - offset, handler); offset += client_technical_header::size;
    offset += parse_client_tcp_message(data + offset, bound - offset, handler);
    bound = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(tmp::ahead<message_size>(data, length, 14)))) + 14);
    tmp::require(bound, length);
    return bound;
}

// Client Tcp Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_client_tcp_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    while (offset < bound) {
        if (bound - offset < 14 + message_size::size) { return offset; }
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(tmp::at<message_size>(data + offset + 14)))) + 14);
        if (bound - offset < size) { return offset; }
        parse_client_tcp_frame(data + offset, size, handler);
        offset += size;
    }
    return offset;
}

// Mdpsessionmgmt Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_mdpsessionmgmt_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const template_id& template_id_, const block_length& block_length_) {
    if (static_cast<bool>(tmp::rule(template_id_) == 200)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<negotiate>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 201)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<negotiation_reject>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 202)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<negotiation_response>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 203)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<terminate>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 205)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_market_data_request(data + offset, bound - offset, handler);
            tmp::call(handler, market_data_request{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 206)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_request_ack(data + offset, bound - offset, handler);
            tmp::call(handler, request_ack{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 207)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<request_reject>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 208)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_security_list_request(data + offset, bound - offset, handler);
            tmp::call(handler, security_list_request{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 209)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_security_status_request(data + offset, bound - offset, handler);
            tmp::call(handler, security_status_request{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 210)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, subscriber_heartbeat{});
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Mdpsessionmgmt Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_mdpsessionmgmt_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const template_id& template_id_, const block_length& block_length_) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    offset += parse_mdpsessionmgmt_payload(data + offset, bound - offset, handler, template_id_, block_length_);
    return offset;
}

// Mktdata Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_mktdata_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const template_id& template_id_, const block_length& block_length_) {
    if (static_cast<bool>(tmp::rule(template_id_) == 4)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_channel_reset(data + offset, bound - offset, handler);
            tmp::call(handler, channel_reset{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 12)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, admin_heartbeat{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 15)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += tmp::take<admin_login>(data + offset, bound - offset, handler);
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
            offset += tmp::take<admin_logout>(data + offset, bound - offset, handler);
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
            offset += parse_md_instrument_definition_future(data + offset, bound - offset, handler);
            tmp::call(handler, md_instrument_definition_future{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 29)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_instrument_definition_spread(data + offset, bound - offset, handler);
            tmp::call(handler, md_instrument_definition_spread{});
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
            offset += tmp::take<security_status>(data + offset, bound - offset, handler);
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 32)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_incremental_refresh_book(data + offset, bound - offset, handler);
            tmp::call(handler, md_incremental_refresh_book{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 33)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_incremental_refresh_daily_statistics(data + offset, bound - offset, handler);
            tmp::call(handler, md_incremental_refresh_daily_statistics{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 34)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_incremental_refresh_limits_banding(data + offset, bound - offset, handler);
            tmp::call(handler, md_incremental_refresh_limits_banding{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 35)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_incremental_refresh_session_statistics(data + offset, bound - offset, handler);
            tmp::call(handler, md_incremental_refresh_session_statistics{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 36)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_incremental_refresh_trade(data + offset, bound - offset, handler);
            tmp::call(handler, md_incremental_refresh_trade{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 37)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_incremental_refresh_volume(data + offset, bound - offset, handler);
            tmp::call(handler, md_incremental_refresh_volume{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 38)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_snapshot_full_refresh(data + offset, bound - offset, handler);
            tmp::call(handler, snapshot_full_refresh{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 39)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_quote_request(data + offset, bound - offset, handler);
            tmp::call(handler, quote_request{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 41)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_instrument_definition_option(data + offset, bound - offset, handler);
            tmp::call(handler, md_instrument_definition_option{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 42)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_incremental_refresh_trade_summary(data + offset, bound - offset, handler);
            tmp::call(handler, md_incremental_refresh_trade_summary{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 43)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_md_incremental_refresh_order_book(data + offset, bound - offset, handler);
            tmp::call(handler, md_incremental_refresh_order_book{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    if (static_cast<bool>(tmp::rule(template_id_) == 44)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            const std::size_t block = static_cast<std::size_t>(tmp::rule(block_length_));
            const std::size_t start = offset;
            offset += parse_snapshot_full_refresh_order_book(data + offset, bound - offset, handler);
            tmp::call(handler, snapshot_full_refresh_order_book{});
            if (offset - start < block) { offset = start + block; }
            tmp::require(offset, bound);
        }
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Mktdata Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_mktdata_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const template_id& template_id_, const block_length& block_length_) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    offset += parse_mktdata_payload(data + offset, bound - offset, handler, template_id_, block_length_);
    return offset;
}

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const schema_id& schema_id_, const template_id& template_id_, const block_length& block_length_) {
    if (static_cast<bool>(tmp::rule(schema_id_) == 1)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_mktdata_message(data + offset, bound - offset, handler, template_id_, block_length_);
        return offset;
    }
    if (static_cast<bool>(tmp::rule(schema_id_) == 2)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_mdpsessionmgmt_message(data + offset, bound - offset, handler, template_id_, block_length_);
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
    [[maybe_unused]] const auto& message_header_ = tmp::read<message_header>(data + offset, bound - offset, handler); offset += message_header::size;
    bound = static_cast<std::size_t>(tmp::rule(message_header_.template get<message_size>()));
    tmp::require(bound, length);
    offset += parse_payload(data + offset, bound - offset, handler, message_header_.template get<simple_binary_header>().template get<schema_id>(), message_header_.template get<simple_binary_header>().template get<template_id>(), message_header_.template get<simple_binary_header>().template get<block_length>());
    return bound;
}

// Udp Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_udp_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& binary_packet_header_ = tmp::read<binary_packet_header>(data + offset, bound - offset, handler); offset += binary_packet_header::size;
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


} // namespace cme::globex::mdp3::sbe::v1_8

namespace protocol = ::cme::globex::mdp3::sbe::v1_8;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::binary_packet_header& header) {
        if constexpr (requires { header.template get<protocol::packet_sequence_number>(); }) { checksum += bench::digest(header.template get<protocol::packet_sequence_number>().value()); }
        if constexpr (requires { header.template get<protocol::sending_time>(); }) { checksum += bench::digest(header.template get<protocol::sending_time>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        checksum += index++;
        if constexpr (requires { header.template get<protocol::message_size>(); }) { checksum += bench::digest(header.template get<protocol::message_size>().value()); }
    }

    void operator()(const protocol::mktdata_message&) {
    }

    void operator()(const protocol::mdpsessionmgmt_message&) {
    }
};

// The values the Tmp reading reads from one datagram, folded into a checksum. A datagram it cannot read
// is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::parse_udp_packet(frame.payload, frame.payload_len, reader);
    } catch (const std::exception& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Cme.Globex.Mdp3.Sbe.v1.8", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
