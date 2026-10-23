// Cme Globex Mdp3 Sbe 1.8 Template Meta Programming

#pragma once

#include <algorithm>
#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>

// A member of a struct laid over its bytes: the overload get<Field>() finds it by, and the member
#ifndef MDP3FIELD
#define MDP3FIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef MDP3SEQUENCE
#define MDP3SEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace cme::globex::mdp3::sbe::v1_8 {

/////////////////////////////////////////////////////////////////////
// Wire
/////////////////////////////////////////////////////////////////////

namespace tmp {
    // The types of a struct's members, in wire order: what generic code walks a struct by
    template <typename... Fields>
    struct list {};

    // A repeating group of a message: the type of its entries, each laid over its bytes in turn
    template <typename Entry>
    struct sequence {
        using entry = Entry;
    };

    // An integer as the wire holds it, in the host's order: swapped when the wire's order is not the host's
    template <std::endian Order, typename T>
    constexpr T ordered(T value) noexcept {
        if constexpr (sizeof(T) == 1 || Order == std::endian::native) { return value; }
        else { return std::byteswap(value); }
    }

    // An integer of a width no C++ integer has, assembled from its bytes in the wire's order
    template <std::endian Order, typename T, std::size_t N>
    constexpr T assembled(const std::array<std::byte, N>& bytes) noexcept {
        using U = std::make_unsigned_t<T>;
        U value = 0;
        for (std::size_t index = 0; index < N; ++index) {
            const std::size_t at = Order == std::endian::big ? index : N - 1 - index;
            value = static_cast<U>((value << 8) | std::to_integer<U>(bytes[at]));
        }
        if constexpr (std::is_signed_v<T>) {
            constexpr int spare = static_cast<int>(sizeof(T) - N) * 8;
            return static_cast<T>(static_cast<T>(value << spare) >> spare);
        }
        else { return value; }
    }

    // Text of a fixed width, as the characters before its fill
    template <std::size_t N>
    constexpr std::string_view trimmed(const std::array<char, N>& text, char fill) noexcept {
        std::size_t length = N;
        while (length > 0 && text[length - 1] == fill) { --length; }
        return { text.data(), length };
    }

    // Text of a fixed width justified right, as the characters after its fill
    template <std::size_t N>
    constexpr std::string_view trimmed_front(const std::array<char, N>& text, char fill) noexcept {
        std::size_t start = 0;
        while (start < N && text[start] == fill) { ++start; }
        return { text.data() + start, N - start };
    }

    // The integer the digits of text state, its fill skipped; it ends at anything else
    template <typename T>
    constexpr T number(std::string_view text, char fill) noexcept {
        T value = 0;
        for (const char character : text) {
            if (character == fill) { continue; }
            if (character < '0' || character > '9') { break; }
            value = static_cast<T>(value * 10 + static_cast<T>(character - '0'));
        }
        return value;
    }
} // namespace tmp

/////////////////////////////////////////////////////////////////////
// Types
/////////////////////////////////////////////////////////////////////

// Access Key Id: Contains the AccessKeyID assigned to this session on this port
struct access_key_id {
    using type = std::string_view;
    static constexpr std::size_t size = 20;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 20> value_;
};

// Actual
struct actual {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// Aggressor Side: Indicates aggressor side in the trade, if value is 0 then there is no aggressor
struct aggressor_side {
    enum class type : std::uint8_t {
        no_aggressor = 0,
        buy = 1,
        sell = 2,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Appl Id: The channel ID as defined in the XML Configuration file
struct appl_id {
    using type = std::int16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Asset: The underlying asset code also known as Product Code
struct asset {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Block Length
struct block_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Block Trade Eligible: BlockTradeEligible
struct block_trade_eligible {
    using type = bool;
    static constexpr std::uint64_t mask = 0x4ULL;
    static constexpr int shift = 2;
};

// Cfi Code: ISO standard instrument categorization code
struct cfi_code {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Cleared Volume: The total cleared volume of instrument traded during the prior trading session.
struct cleared_volume {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(2147483647LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Contract Multiplier: Number of deliverable units per instrument, e.g., peak days in maturity month or number of calendar days in maturity month
struct contract_multiplier {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(2147483647LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Contract Multiplier Unit: Indicates the type of multiplier being applied to the product. Optionally used in combination with tag 231-ContractMultiplier
struct contract_multiplier_unit {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(127LL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Currency: Identifies currency used for price
struct currency {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Current Chunk: Chunk sequence
struct current_chunk {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Daily Product Eligibility: DailyProductEligibility
struct daily_product_eligibility {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20000ULL;
    static constexpr int shift = 17;
};

// Day: DD
struct day {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255ULL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Decay Quantity: Indicates the quantity that a contract will decay daily by once the decay start date is reached
struct decay_quantity {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(2147483647LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Decay Start Date: Indicates the date at which a decaying contract will begin to decay
struct decay_start_date {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(65535ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Decaying Product Eligibility: DecayingProductEligibility
struct decaying_product_eligibility {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8000ULL;
    static constexpr int shift = 15;
};

// Display Factor: Contains the multiplier to convert the CME Globex display price to the conventional price
struct display_factor {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -7;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Ebf Eligible: EBFEligible
struct ebf_eligible {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// Efp Eligible: EFPEligible
struct efp_eligible {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Efr Eligible: EFREligible
struct efr_eligible {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40ULL;
    static constexpr int shift = 6;
};

// Efs Eligible: EFSEligible
struct efs_eligible {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20ULL;
    static constexpr int shift = 5;
};

// Electronic Match Eligible: ElectronicMatchEligible
struct electronic_match_eligible {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Encoding Type
struct encoding_type {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// End Of Event: EndOfEvent
struct end_of_event {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Error Codes: Error code for reject reason
struct error_codes {
    enum class type : std::uint8_t {
        hmac_reject = 0,
        invalid_value = 1,
        slow_connection = 2,
        other = 3,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Event Time: Date and Time of instument Activation or Expiration event sent as number of nanoseconds since Unix epoch
struct event_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Event Type: Code to represent the type of event
struct event_type {
    enum class type : std::uint8_t {
        activation = 5,
        last_eligible_trade_date = 7,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Final
struct final {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Firm: Firm ID
struct firm {
    using type = std::string_view;
    static constexpr std::size_t size = 5;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 5> value_;
};

// Flow Schedule Type: The schedule according to which the electricity is delivered in a physical contract, or priced in a financial contract. Specifies whether the contract is defined according to the Easter Peak, Eastern Off-Peak, Western Peak or Western Off-Peak.
struct flow_schedule_type {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(127LL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Gt Orders Eligibility: GTOrdersEligibility
struct gt_orders_eligibility {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40000ULL;
    static constexpr int shift = 18;
};

// Halt Reason: Identifies the reason for the status change
struct halt_reason {
    enum class type : std::uint8_t {
        group_schedule = 0,
        surveillance_intervention = 1,
        market_event = 2,
        instrument_activation = 3,
        instrument_expiration = 4,
        unknown = 5,
        recovery_in_process = 6,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Heart Bt Int: Heartbeat interval (seconds)
struct heart_bt_int {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// High Limit Price: Allowable high limit price for the trading day
struct high_limit_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -7;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Hmac Signature: Contains the HMAC signature
struct hmac_signature {
    using type = std::string_view;
    static constexpr std::size_t size = 32;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 32> value_;
};

// ILink Indicative Mass Quoting Eligible: iLinkIndicativeMassQuotingEligible
struct ilink_indicative_mass_quoting_eligible {
    using type = bool;
    static constexpr std::uint64_t mask = 0x100ULL;
    static constexpr int shift = 8;
};

// Implied Matching Eligibility: ImpliedMatchingEligibility
struct implied_matching_eligibility {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80000ULL;
    static constexpr int shift = 19;
};

// Intraday
struct intraday {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Is Fractional: IsFractional
struct is_fractional {
    using type = bool;
    static constexpr std::uint64_t mask = 0x800ULL;
    static constexpr int shift = 11;
};

// Last Implied Msg: LastImpliedMsg
struct last_implied_msg {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// Last Msg Seq Num Processed: Sequence number of the last Incremental feed packet processed. This value is used to synchronize the snapshot loop with the real-time feed
struct last_msg_seq_num_processed {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Qty: Quantity bought or sold on this last fill
struct last_qty {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Quote Msg: LastQuoteMsg
struct last_quote_msg {
    using type = bool;
    static constexpr std::uint64_t mask = 0x4ULL;
    static constexpr int shift = 2;
};

// Last Stats Msg: LastStatsMsg
struct last_stats_msg {
    using type = bool;
    static constexpr std::uint64_t mask = 0x8ULL;
    static constexpr int shift = 3;
};

// Last Trade Msg: LastTradeMsg
struct last_trade_msg {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1ULL;
    static constexpr int shift = 0;
};

// Last Update Time: Timestamp of when the instrument was last added, modified or deleted
struct last_update_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Last Volume Msg: LastVolumeMsg
struct last_volume_msg {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// Leg Option Delta: Delta used to calculate the quantity of futures used to cover the option or option strategy
struct leg_option_delta {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(2147483647LL);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Price: Price for the future leg of a UDS Covered instrument
struct leg_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -7;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Ratio Qty: Leg ratio of quantity for this individual leg relative to the entire multi-leg instrument
struct leg_ratio_qty {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Security Id
struct leg_security_id {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Leg Side
struct leg_side {
    enum class type : std::uint8_t {
        buy_side = 1,
        sell_side = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Lot Type: This tag is required to interpret the value in tag 1231-MinLotSize
struct lot_type {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Low Limit Price: Allowable low limit price for the trading day
struct low_limit_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -7;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Main Fraction: Price Denominator of Main Fraction
struct main_fraction {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255ULL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Depth: Book depth
struct market_depth {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market Segment Id: Identifies the market segment, populated for all CME Globex instruments
struct market_segment_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Match Algorithm: Matching algorithm
struct match_algorithm {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Max Price Variation: Differential value for price banding.
struct max_price_variation {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -7;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Max Trade Vol: The maximum trading volume for a security
struct max_trade_vol {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Display Qty: Visible order qty
struct md_display_qty {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Display Qty Optional: Visible qty of order
struct md_display_qty_optional {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(2147483647LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Px: Market Data entry price
struct md_entry_px {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -7;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Px Optional: Market Data entry price
struct md_entry_px_optional {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -7;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Size: Trade quantity
struct md_entry_size {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Size Optional: Market Data entry size
struct md_entry_size_optional {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(2147483647LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Entry Type: Market Data entry type
struct md_entry_type {
    enum class type : char {
        bid = '0',
        offer = '1',
        trade = '2',
        open_price = '4',
        settlement_price = '6',
        trading_session_high_price = '7',
        trading_session_low_price = '8',
        cleared_volume = 'B',
        open_interest = 'C',
        implied_bid = 'E',
        implied_offer = 'F',
        book_reset = 'J',
        session_high_bid = 'N',
        session_low_offer = 'O',
        fixing_price = 'W',
        electronic_volume = 'e',
        threshold_limitsand_price_band_variation = 'g',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Md Entry Type Book: Market Data entry type
struct md_entry_type_book {
    enum class type : char {
        bid = '0',
        offer = '1',
        implied_bid = 'E',
        implied_offer = 'F',
        book_reset = 'J',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Md Entry Type Daily Statistics: Market Data entry type
struct md_entry_type_daily_statistics {
    enum class type : char {
        settlement_price = '6',
        cleared_volume = 'B',
        open_interest = 'C',
        fixing_price = 'W',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Md Entry Type Statistics: Market Data entry type
struct md_entry_type_statistics {
    enum class type : char {
        open_price = '4',
        high_trade = '7',
        low_trade = '8',
        highest_bid = 'N',
        lowest_offer = 'O',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Md Feed Type: Describes a class of service for a given data feed. GBX- Real Book, GBI-Implied Book
struct md_feed_type {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Md Order Priority: Order priority for execution on the order book
struct md_order_priority {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(18446744073709551615ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Price Level: Aggregate book level
struct md_price_level {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Price Level Optional: Aggregate book position
struct md_price_level_optional {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(127LL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Req Id: Unique identifier for Market Data Request. Must be unique per session so it can be referenced in Request Ack or Request Reject responses from the exchange
struct md_req_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Req Id Optional: Unique identifier for Market Data Request
struct md_req_id_optional {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(4294967295ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Req Id Status: Status of the request acknowledgement
struct md_req_id_status {
    enum class type : std::uint8_t {
        full_ack = 0,
        partial_ack = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Md Req Rej Reason: Market Data Request Reject reason code
struct md_req_rej_reason {
    enum class type : std::uint8_t {
        unknown_security = 0,
        unknown_message = 1,
        unsupported_scope = 2,
        other = 3,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Md Security Trading Status: Identifies the current state of the instrument. In Security Definition message this tag is available in the Instrument Replay feed only
struct md_security_trading_status {
    enum class type : std::uint8_t {
        trading_halt = 2,
        close = 4,
        new_price_indication = 15,
        ready_to_trade = 17,
        not_available_for_trading = 18,
        unknown_or_invalid = 20,
        pre_open = 21,
        pre_cross = 24,
        cross = 25,
        post_close = 26,
        no_change = 103,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Md Trade Entry Id: Market Data Trade entry ID
struct md_trade_entry_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(4294967295ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Md Update Action: Market Data update action
struct md_update_action {
    enum class type : std::uint8_t {
        new_value = 0,
        change = 1,
        delete_value = 2,
        delete_thru = 3,
        delete_from = 4,
        overlay = 5,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Message Sequence Number: Packet Sequence Number
struct message_sequence_number {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Message Size
struct message_size {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Min Cab Price: Defines cabinet price for outright options products
struct min_cab_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -7;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Min Lot Size: Minimum quantity accepted for order entry. If tag 1093-LotType=4, this value is the minimum quantity for order entry expressed in the applicable units, specified in tag 996-UnitOfMeasure, e.g. megawatts
struct min_lot_size {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(2147483647LL);
    static constexpr int exponent = -4;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Min Price Increment: Minimum constant tick for the instrument, sent only if instrument is non-VTT (Variable Tick table) eligible
struct min_price_increment {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr int exponent = -7;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Min Price Increment Amount: Monetary value equivalent to the minimum price fluctuation
struct min_price_increment_amount {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -7;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Min Price Increment Optional: Minimum constant tick for the instrument
struct min_price_increment_optional {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -7;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Min Trade Vol: The minimum trading volume for a security
struct min_trade_vol {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Month: MM
struct month {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255ULL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Negative Price Outright Eligible: NegativePriceOutrightEligible
struct negative_price_outright_eligible {
    using type = bool;
    static constexpr std::uint64_t mask = 0x400ULL;
    static constexpr int shift = 10;
};

// Negative Strike Eligible: NegativeStrikeEligible
struct negative_strike_eligible {
    using type = bool;
    static constexpr std::uint64_t mask = 0x200ULL;
    static constexpr int shift = 9;
};

// No Chunks: Total number of packets that constitutes a single instrument order book
struct no_chunks {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Null Value: NullValue
struct null_value {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Num In Group
struct num_in_group {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Number Of Orders: In Book entry - aggregate number of orders at given price level
struct number_of_orders {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(2147483647LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Open Close Settl Flag: Flag describing IOP and Open Price entries
struct open_close_settl_flag {
    enum class type : std::uint8_t {
        daily_open_price = 0,
        indicative_opening_price = 5,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Open Interest Qty: The total open interest for the market at the close of the prior trading session.
struct open_interest_qty {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(2147483647LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Cross Eligible: OrderCrossEligible
struct order_cross_eligible {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2ULL;
    static constexpr int shift = 1;
};

// Order Id: Unique Order ID
struct order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Id Optional: Order ID
struct order_id_optional {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(18446744073709551615ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Qty: Quantity requested
struct order_qty {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(2147483647LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Update Action: Order book update action to be applied to the order referenced by OrderID
struct order_update_action {
    enum class type : std::uint8_t {
        new_value = 0,
        update = 1,
        delete_value = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Original Contract Size: Fixed contract value assigned to each product
struct original_contract_size {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(2147483647LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Otc Eligible: OTCEligible
struct otc_eligible {
    using type = bool;
    static constexpr std::uint64_t mask = 0x80ULL;
    static constexpr int shift = 7;
};

// Packet Sequence Number
struct packet_sequence_number {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Padding 1: 1 bytes padding
struct padding_1 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Padding 2: 2 bytes padding
struct padding_2 {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Padding 3: 3 bytes padding
struct padding_3 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 3;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 3> value_;
};

// Padding 4: 4 bytes padding
struct padding_4 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Padding 5: 5 bytes padding
struct padding_5 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 5;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 5> value_;
};

// Padding 6: 6 bytes padding
struct padding_6 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 6;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 6> value_;
};

// Padding 7: 7 bytes padding
struct padding_7 {
    using type = std::uint64_t;
    static constexpr std::size_t size = 7;
    static constexpr std::endian order = std::endian::big;

    constexpr type value() const noexcept { return tmp::assembled<order, type>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<std::byte, 7> value_;
};

// Price Display Format: Number of decimals in fractional display price
struct price_display_format {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255ULL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price Ratio: Used for price calculation in spread and leg pricing
struct price_ratio {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -7;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Put Or Call: Indicates whether an option instrument is a put or call
struct put_or_call {
    enum class type : std::uint8_t {
        put = 0,
        call = 1,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Quote Req Id: Quote Request ID defined by the exchange
struct quote_req_id {
    using type = std::string_view;
    static constexpr std::size_t size = 23;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 23> value_;
};

// Quote Type: Type of quote requested
struct quote_type {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reason: Reject reason details
struct reason {
    using type = std::string_view;
    static constexpr std::size_t size = 48;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 48> value_;
};

// Recovery Msg: RecoveryMsg
struct recovery_msg {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20ULL;
    static constexpr int shift = 5;
};

// Reference Id: Reference to corresponding Price and Security ID, sequence of MD entry in the message
struct reference_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255ULL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Related Security Id
struct related_security_id {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Related Symbol: Related instrument Symbol
struct related_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 20;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 20> value_;
};

// Request Timestamp: Time of request, recommended to use timestamp as number of nanoseconds since Unix epoch
struct request_timestamp {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Reserved
struct reserved {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40ULL;
    static constexpr int shift = 6;
};

// Reserved 12: 12 reserved bits
struct reserved_12 {
    using type = std::uint32_t;
    static constexpr std::uint64_t mask = 0xFFF00000ULL;
    static constexpr int shift = 20;
};

// Reserved Bits: ReservedBits
struct reserved_bits {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10ULL;
    static constexpr int shift = 4;
};

// Rfq Cross Eligible: RFQCrossEligible
struct rfq_cross_eligible {
    using type = bool;
    static constexpr std::uint64_t mask = 0x2000ULL;
    static constexpr int shift = 13;
};

// Rounded
struct rounded {
    using type = bool;
    static constexpr std::uint64_t mask = 0x4ULL;
    static constexpr int shift = 2;
};

// Rpt Seq: Sequence number of the last Market Data entry processed for the instrument
struct rpt_seq {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Schema Id
struct schema_id {
    enum class type : std::uint16_t {
        mktdata = 1,
        mdpsessionmgmt = 2,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Secret Key Secure Id Expiration: This indicates in how many days the HMAC secret key will expire
struct secret_key_secure_id_expiration {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(65535ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Exchange: Exchange used to identify a security
struct security_exchange {
    using type = std::string_view;
    static constexpr std::size_t size = 4;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 4> value_;
};

// Security Group
struct security_group {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Security Id
struct security_id {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Id Optional: If this tag is present, 35=f message is sent for the instrument
struct security_id_optional {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(2147483647LL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Security Sub Type: Strategy type
struct security_sub_type {
    using type = std::string_view;
    static constexpr std::size_t size = 5;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 5> value_;
};

// Security Trading Event: Identifies an additional event or a rule related to the status
struct security_trading_event {
    enum class type : std::uint8_t {
        no_event = 0,
        no_cancel = 1,
        reset_statistics = 4,
        implied_matching_on = 5,
        implied_matching_off = 6,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Trading Status: Identifies the trading status applicable to the instrument or Security Group
struct security_trading_status {
    enum class type : std::uint8_t {
        trading_halt = 2,
        close = 4,
        new_price_indication = 15,
        ready_to_trade = 17,
        not_available_for_trading = 18,
        unknownor_invalid = 20,
        pre_open = 21,
        pre_cross = 24,
        cross = 25,
        post_close = 26,
        no_change = 103,
    };

    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255);

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Security Type
struct security_type {
    using type = std::string_view;
    static constexpr std::size_t size = 6;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 6> value_;
};

// Security Update Action: Last Security update action on Incremental feed, 'D' or 'M' is used when a mid-week deletion or modification (i.e. extension) occurs
struct security_update_action {
    enum class type : char {
        add = 'A',
        delete_value = 'D',
        modify = 'M',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Sending Time: Packet Sending Time
struct sending_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Session: Session ID
struct session {
    using type = std::string_view;
    static constexpr std::size_t size = 5;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 5> value_;
};

// Settl Currency: Identifies currency used for settlement, if different from trading currency
struct settl_currency {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Side: Side requested
struct side {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(127LL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Strike Currency: Currency in which the StrikePrice is denominated
struct strike_currency {
    using type = std::string_view;
    static constexpr std::size_t size = 3;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 3> value_;
};

// Strike Price: Strike Price for an option instrument
struct strike_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -7;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Sub Fraction: Price Denominator of Sub Fraction
struct sub_fraction {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255ULL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Subscription Req Type: Subscription Request Type indicates to the type of response expected
struct subscription_req_type {
    enum class type : std::uint8_t {
        snapshot = 0,
        snapshot_and_updates = 1,
        unsubscribe = 2,
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Symbol: Instrument Name or Symbol
struct symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 20;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 20> value_;
};

// Tcp Message Size: Message Size
struct tcp_message_size {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Tcp Sending Time: Packet Sending Time, nanoseconds since the Unix epoch
struct tcp_sending_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Template Id
struct template_id {
    enum class type : std::uint16_t {
        channel_reset = 4,
        admin_heartbeat = 12,
        admin_login = 15,
        admin_logout = 16,
        md_instrument_definition_future = 27,
        md_instrument_definition_spread = 29,
        security_status = 30,
        md_incremental_refresh_book = 32,
        md_incremental_refresh_daily_statistics = 33,
        md_incremental_refresh_limits_banding = 34,
        md_incremental_refresh_session_statistics = 35,
        md_incremental_refresh_trade = 36,
        md_incremental_refresh_volume = 37,
        snapshot_full_refresh = 38,
        quote_request = 39,
        md_instrument_definition_option = 41,
        md_incremental_refresh_trade_summary = 42,
        md_incremental_refresh_order_book = 43,
        snapshot_full_refresh_order_book = 44,
        negotiate = 200,
        negotiation_reject = 201,
        negotiation_response = 202,
        terminate = 203,
        market_data_request = 205,
        request_ack = 206,
        request_reject = 207,
        security_list_request = 208,
        security_status_request = 209,
        subscriber_heartbeat = 210,
    };

    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    std::underlying_type_t<type> value_;
};

// Text: Reject reason details
struct text {
    using type = std::string_view;
    static constexpr std::size_t size = 100;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 100> value_;
};

// Tick Rule
struct tick_rule {
    using type = std::int8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(127LL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Tot Num Reports: Total number of messages replayed in the loop
struct tot_num_reports {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Tot Num Reports Optional: Total number of instruments in the Replay loop. Used on Replay Feed only
struct tot_num_reports_optional {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(4294967295ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Date: Trade Session Date
struct trade_date {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(65535ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Id: Unique Trade ID per instrument and Trading Date
struct trade_id {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trading Reference Date: Indicates session date corresponding to the settlement price in tag 1150-TradingReferencePrice
struct trading_reference_date {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(65535ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trading Reference Price: Reference price for prelisted instruments or the last calculated Settlement whether it be Theoretical, Preliminary or a Final Settle of the session.
struct trading_reference_price {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -7;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Transact Time: Start of event processing time in number of nanoseconds since Unix epoch
struct transact_time {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Underlying Product: Product complex
struct underlying_product {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Underlying Product Optional: Product complex
struct underlying_product_optional {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255ULL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Underlying Security Id: Unique Instrument ID as qualified by the exchange per tag 305-UnderlyingSecurityIDSource
struct underlying_security_id {
    using type = std::int32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Underlying Symbol: Underlying Instrument Symbol (Contract Name)
struct underlying_symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 20;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 20> value_;
};

// Unit Of Measure: Unit of measure for the products' original contract size. This will be populated for all products listed on CME Globex
struct unit_of_measure {
    using type = std::string_view;
    static constexpr std::size_t size = 30;
    static constexpr char fill = '\0';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 30> value_;
};

// Unit Of Measure Qty: This field contains the contract size for each instrument. Used in combination with tag 996-UnitofMeasure
struct unit_of_measure_qty {
    using type = std::int64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(9223372036854775807LL);
    static constexpr int exponent = -7;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Unused Settl Price Type 5: Unused SettlPriceType 5
struct unused_settl_price_type_5 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x20ULL;
    static constexpr int shift = 5;
};

// Unused Settl Price Type 6: Unused SettlPriceType 6
struct unused_settl_price_type_6 {
    using type = bool;
    static constexpr std::uint64_t mask = 0x40ULL;
    static constexpr int shift = 6;
};

// User Defined Instrument: User-defined instruments flag
struct user_defined_instrument {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Uuid: Session Identifier defined as type long uInt64, recommended to use timestamp as number of microseconds since Unix epoch
struct uuid {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Variable Product Eligibility: VariableProductEligibility
struct variable_product_eligibility {
    using type = bool;
    static constexpr std::uint64_t mask = 0x10000ULL;
    static constexpr int shift = 16;
};

// Version
struct version {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Volatility Quoted Option: VolatilityQuotedOption
struct volatility_quoted_option {
    using type = bool;
    static constexpr std::uint64_t mask = 0x1000ULL;
    static constexpr int shift = 12;
};

// Week: WW
struct week {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(255ULL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Year: YYYY
struct year {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(65535ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Zero Price Outright Eligible: ZeroPriceOutrightEligible
struct zero_price_outright_eligible {
    using type = bool;
    static constexpr std::uint64_t mask = 0x4000ULL;
    static constexpr int shift = 14;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Request Reject: RequestReject
struct request_reject {
    static constexpr std::string_view name = "Request Reject";
    static constexpr std::size_t size = 105;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_req_id_optional,
        md_req_rej_reason,
        text>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(md_req_id_optional);
    MDP3FIELD(md_req_rej_reason);
    MDP3FIELD(text);
};

static_assert(sizeof(request_reject) == request_reject::size, "request_reject lies over its bytes exactly");

// Request Ack Related Symbol Group: Number of securities acknowledged
struct request_ack_related_symbol_group {
    static constexpr std::string_view name = "Request Ack Related Symbol Group";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(security_id);
};

static_assert(sizeof(request_ack_related_symbol_group) == request_ack_related_symbol_group::size, "request_ack_related_symbol_group lies over its bytes exactly");

// Group Size: Repeating group dimensions
struct group_size {
    static constexpr std::string_view name = "Group Size";
    static constexpr std::size_t size = 3;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        block_length,
        num_in_group>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(block_length);
    MDP3FIELD(num_in_group);
};

static_assert(sizeof(group_size) == group_size::size, "group_size lies over its bytes exactly");

// Request Ack Related Symbol Groups: NoRelatedSym Block
struct request_ack_related_symbol_groups {
    static constexpr std::string_view name = "Request Ack Related Symbol Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(request_ack_related_symbol_group);
};

// Request Ack Security Group: Number of SecurityGroups acknowledged
struct request_ack_security_group {
    static constexpr std::string_view name = "Request Ack Security Group";
    static constexpr std::size_t size = 6;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_group>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(security_group);
};

static_assert(sizeof(request_ack_security_group) == request_ack_security_group::size, "request_ack_security_group lies over its bytes exactly");

// Request Ack Security Groups: NoSecurityGroups Block
struct request_ack_security_groups {
    static constexpr std::string_view name = "Request Ack Security Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(request_ack_security_group);
};

// Request Ack Section 1
struct request_ack_section_1 {
    static constexpr std::string_view name = "Request Ack Section 1";
    static constexpr std::size_t size = 6;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_req_id,
        subscription_req_type,
        md_req_id_status>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(md_req_id);
    MDP3FIELD(subscription_req_type);
    MDP3FIELD(md_req_id_status);
};

static_assert(sizeof(request_ack_section_1) == request_ack_section_1::size, "request_ack_section_1 lies over its bytes exactly");

// Request Ack: RequestAck
struct request_ack {
    static constexpr std::string_view name = "Request Ack";
    static constexpr bool is_message = true;
};

// Terminate
struct terminate {
    static constexpr std::string_view name = "Terminate";
    static constexpr std::size_t size = 70;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        reason,
        uuid,
        request_timestamp,
        error_codes,
        padding_5>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(reason);
    MDP3FIELD(uuid);
    MDP3FIELD(request_timestamp);
    MDP3FIELD(error_codes);
    MDP3FIELD(padding_5);
};

static_assert(sizeof(terminate) == terminate::size, "terminate lies over its bytes exactly");

// Negotiation Response: NegotiationResponse
struct negotiation_response {
    static constexpr std::string_view name = "Negotiation Response";
    static constexpr std::size_t size = 22;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        uuid,
        request_timestamp,
        secret_key_secure_id_expiration,
        padding_4>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(uuid);
    MDP3FIELD(request_timestamp);
    MDP3FIELD(secret_key_secure_id_expiration);
    MDP3FIELD(padding_4);
};

static_assert(sizeof(negotiation_response) == negotiation_response::size, "negotiation_response lies over its bytes exactly");

// Negotiation Reject: NegotiationReject
struct negotiation_reject {
    static constexpr std::string_view name = "Negotiation Reject";
    static constexpr std::size_t size = 70;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        reason,
        uuid,
        request_timestamp,
        error_codes,
        padding_5>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(reason);
    MDP3FIELD(uuid);
    MDP3FIELD(request_timestamp);
    MDP3FIELD(error_codes);
    MDP3FIELD(padding_5);
};

static_assert(sizeof(negotiation_reject) == negotiation_reject::size, "negotiation_reject lies over its bytes exactly");

// Snapshot Full Refresh Order Book Group: Number of entries in Market Data message
struct snapshot_full_refresh_order_book_group {
    static constexpr std::string_view name = "Snapshot Full Refresh Order Book Group";
    static constexpr std::size_t size = 29;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        order_id,
        md_order_priority,
        md_entry_px,
        md_display_qty,
        md_entry_type_book>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(order_id);
    MDP3FIELD(md_order_priority);
    MDP3FIELD(md_entry_px);
    MDP3FIELD(md_display_qty);
    MDP3FIELD(md_entry_type_book);
};

static_assert(sizeof(snapshot_full_refresh_order_book_group) == snapshot_full_refresh_order_book_group::size, "snapshot_full_refresh_order_book_group lies over its bytes exactly");

// Snapshot Full Refresh Order Book Groups: NoMDEntries Block
struct snapshot_full_refresh_order_book_groups {
    static constexpr std::string_view name = "Snapshot Full Refresh Order Book Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(snapshot_full_refresh_order_book_group);
};

// Snapshot Full Refresh Order Book Section 1
struct snapshot_full_refresh_order_book_section_1 {
    static constexpr std::string_view name = "Snapshot Full Refresh Order Book Section 1";
    static constexpr std::size_t size = 28;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        last_msg_seq_num_processed,
        tot_num_reports,
        security_id,
        no_chunks,
        current_chunk,
        transact_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(last_msg_seq_num_processed);
    MDP3FIELD(tot_num_reports);
    MDP3FIELD(security_id);
    MDP3FIELD(no_chunks);
    MDP3FIELD(current_chunk);
    MDP3FIELD(transact_time);
};

static_assert(sizeof(snapshot_full_refresh_order_book_section_1) == snapshot_full_refresh_order_book_section_1::size, "snapshot_full_refresh_order_book_section_1 lies over its bytes exactly");

// Snapshot Full Refresh Order Book: SnapshotFullRefreshOrderBook
struct snapshot_full_refresh_order_book {
    static constexpr std::string_view name = "Snapshot Full Refresh Order Book";
    static constexpr bool is_message = true;
};

// Incremental Refresh Order Book Group: Number of entries in Market Data message
struct incremental_refresh_order_book_group {
    static constexpr std::string_view name = "Incremental Refresh Order Book Group";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        order_id_optional,
        md_order_priority,
        md_entry_px_optional,
        md_display_qty_optional,
        security_id,
        md_update_action,
        md_entry_type_book,
        padding_6>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(order_id_optional);
    MDP3FIELD(md_order_priority);
    MDP3FIELD(md_entry_px_optional);
    MDP3FIELD(md_display_qty_optional);
    MDP3FIELD(security_id);
    MDP3FIELD(md_update_action);
    MDP3FIELD(md_entry_type_book);
    MDP3FIELD(padding_6);
};

static_assert(sizeof(incremental_refresh_order_book_group) == incremental_refresh_order_book_group::size, "incremental_refresh_order_book_group lies over its bytes exactly");

// Incremental Refresh Order Book Groups: NoMDEntries Block
struct incremental_refresh_order_book_groups {
    static constexpr std::string_view name = "Incremental Refresh Order Book Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(incremental_refresh_order_book_group);
};

// Match Event Indicator: MatchEventIndicator bit set
struct match_event_indicator {
    static constexpr std::string_view name = "Match Event Indicator";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(match_event_indicator) == match_event_indicator::size, "match_event_indicator lies over its bytes exactly");

// Md Incremental Refresh Order Book Section 1
struct md_incremental_refresh_order_book_section_1 {
    static constexpr std::string_view name = "Md Incremental Refresh Order Book Section 1";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        transact_time,
        match_event_indicator,
        padding_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(transact_time);
    MDP3FIELD(match_event_indicator);
    MDP3FIELD(padding_2);
};

static_assert(sizeof(md_incremental_refresh_order_book_section_1) == md_incremental_refresh_order_book_section_1::size, "md_incremental_refresh_order_book_section_1 lies over its bytes exactly");

// Md Incremental Refresh Order Book: MDIncrementalRefreshOrderBook
struct md_incremental_refresh_order_book {
    static constexpr std::string_view name = "Md Incremental Refresh Order Book";
    static constexpr bool is_message = true;
};

// Incremental Refresh Trade Summary Order Id Group: Number of OrderID entries
struct incremental_refresh_trade_summary_order_id_group {
    static constexpr std::string_view name = "Incremental Refresh Trade Summary Order Id Group";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        order_id,
        last_qty,
        padding_4>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(order_id);
    MDP3FIELD(last_qty);
    MDP3FIELD(padding_4);
};

static_assert(sizeof(incremental_refresh_trade_summary_order_id_group) == incremental_refresh_trade_summary_order_id_group::size, "incremental_refresh_trade_summary_order_id_group lies over its bytes exactly");

// Group Size 8 Byte: 8 Byte aligned repeating group dimensions
struct group_size_8_byte {
    static constexpr std::string_view name = "Group Size 8 Byte";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        block_length,
        padding_5,
        num_in_group>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(block_length);
    MDP3FIELD(padding_5);
    MDP3FIELD(num_in_group);
};

static_assert(sizeof(group_size_8_byte) == group_size_8_byte::size, "group_size_8_byte lies over its bytes exactly");

// Incremental Refresh Trade Summary Order Id Groups: NoOrderIDEntries Block
struct incremental_refresh_trade_summary_order_id_groups {
    static constexpr std::string_view name = "Incremental Refresh Trade Summary Order Id Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(incremental_refresh_trade_summary_order_id_group);
};

// Incremental Refresh Trade Summary Group: Number of Trade Summary entries
struct incremental_refresh_trade_summary_group {
    static constexpr std::string_view name = "Incremental Refresh Trade Summary Group";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_entry_px,
        md_entry_size,
        security_id,
        rpt_seq,
        number_of_orders,
        aggressor_side,
        md_update_action,
        md_trade_entry_id,
        padding_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(md_entry_px);
    MDP3FIELD(md_entry_size);
    MDP3FIELD(security_id);
    MDP3FIELD(rpt_seq);
    MDP3FIELD(number_of_orders);
    MDP3FIELD(aggressor_side);
    MDP3FIELD(md_update_action);
    MDP3FIELD(md_trade_entry_id);
    MDP3FIELD(padding_2);
};

static_assert(sizeof(incremental_refresh_trade_summary_group) == incremental_refresh_trade_summary_group::size, "incremental_refresh_trade_summary_group lies over its bytes exactly");

// Incremental Refresh Trade Summary Groups: NoMDEntries Block
struct incremental_refresh_trade_summary_groups {
    static constexpr std::string_view name = "Incremental Refresh Trade Summary Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(incremental_refresh_trade_summary_group);
};

// Md Incremental Refresh Trade Summary Section 1
struct md_incremental_refresh_trade_summary_section_1 {
    static constexpr std::string_view name = "Md Incremental Refresh Trade Summary Section 1";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        transact_time,
        match_event_indicator,
        padding_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(transact_time);
    MDP3FIELD(match_event_indicator);
    MDP3FIELD(padding_2);
};

static_assert(sizeof(md_incremental_refresh_trade_summary_section_1) == md_incremental_refresh_trade_summary_section_1::size, "md_incremental_refresh_trade_summary_section_1 lies over its bytes exactly");

// Md Incremental Refresh Trade Summary: MDIncrementalRefreshTradeSummary
struct md_incremental_refresh_trade_summary {
    static constexpr std::string_view name = "Md Incremental Refresh Trade Summary";
    static constexpr bool is_message = true;
};

// Option Related Instruments Group: Number of related instruments group
struct option_related_instruments_group {
    static constexpr std::string_view name = "Option Related Instruments Group";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        related_security_id,
        related_symbol>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(related_security_id);
    MDP3FIELD(related_symbol);
};

static_assert(sizeof(option_related_instruments_group) == option_related_instruments_group::size, "option_related_instruments_group lies over its bytes exactly");

// Option Related Instruments Groups: NoRelatedInstruments Block
struct option_related_instruments_groups {
    static constexpr std::string_view name = "Option Related Instruments Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(option_related_instruments_group);
};

// Option Underlyings Group: Number of underlying instruments
struct option_underlyings_group {
    static constexpr std::string_view name = "Option Underlyings Group";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        underlying_security_id,
        underlying_symbol>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(underlying_security_id);
    MDP3FIELD(underlying_symbol);
};

static_assert(sizeof(option_underlyings_group) == option_underlyings_group::size, "option_underlyings_group lies over its bytes exactly");

// Option Underlyings Groups: NoUnderlyings Block
struct option_underlyings_groups {
    static constexpr std::string_view name = "Option Underlyings Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(option_underlyings_group);
};

// Lot Type Rules Group: Number of entries
struct lot_type_rules_group {
    static constexpr std::string_view name = "Lot Type Rules Group";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        lot_type,
        min_lot_size>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(lot_type);
    MDP3FIELD(min_lot_size);
};

static_assert(sizeof(lot_type_rules_group) == lot_type_rules_group::size, "lot_type_rules_group lies over its bytes exactly");

// Lot Type Rules Groups: NoLotTypeRules Block
struct lot_type_rules_groups {
    static constexpr std::string_view name = "Lot Type Rules Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(lot_type_rules_group);
};

// Inst Attrib Value: InstAttribValue bit set
struct inst_attrib_value {
    static constexpr std::string_view name = "Inst Attrib Value";
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }

  protected:
    type value_;
};

static_assert(sizeof(inst_attrib_value) == inst_attrib_value::size, "inst_attrib_value lies over its bytes exactly");

// Inst Attrib Group: Number of repeating InstrAttribType entries
struct inst_attrib_group {
    static constexpr std::string_view name = "Inst Attrib Group";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        inst_attrib_value>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(inst_attrib_value);
};

static_assert(sizeof(inst_attrib_group) == inst_attrib_group::size, "inst_attrib_group lies over its bytes exactly");

// Inst Attrib Groups: NoInstAttrib Block
struct inst_attrib_groups {
    static constexpr std::string_view name = "Inst Attrib Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(inst_attrib_group);
};

// Feed Types Group: Number of repeating FeedType entries
struct feed_types_group {
    static constexpr std::string_view name = "Feed Types Group";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_feed_type,
        market_depth>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(md_feed_type);
    MDP3FIELD(market_depth);
};

static_assert(sizeof(feed_types_group) == feed_types_group::size, "feed_types_group lies over its bytes exactly");

// Feed Types Groups: NoMDFeedTypes Block
struct feed_types_groups {
    static constexpr std::string_view name = "Feed Types Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(feed_types_group);
};

// Events Group: Number of repeating EventType entries
struct events_group {
    static constexpr std::string_view name = "Events Group";
    static constexpr std::size_t size = 9;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        event_type,
        event_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(event_type);
    MDP3FIELD(event_time);
};

static_assert(sizeof(events_group) == events_group::size, "events_group lies over its bytes exactly");

// Events Groups: NoEvents Block
struct events_groups {
    static constexpr std::string_view name = "Events Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(events_group);
};

// Settl Price Type: SettlPriceType bit set
struct settl_price_type {
    static constexpr std::string_view name = "Settl Price Type";
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    // the bits of the type asked for
    template <typename Bit>
    constexpr typename Bit::type get() const noexcept { return static_cast<typename Bit::type>((value() & Bit::mask) >> Bit::shift); }

    constexpr type value() const noexcept { return value_; }

  protected:
    type value_;
};

static_assert(sizeof(settl_price_type) == settl_price_type::size, "settl_price_type lies over its bytes exactly");

// Maturity Month Year: MDInstrumentDefinitionFuture
struct maturity_month_year {
    static constexpr std::string_view name = "Maturity Month Year";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        year,
        month,
        day,
        week>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(year);
    MDP3FIELD(month);
    MDP3FIELD(day);
    MDP3FIELD(week);
};

static_assert(sizeof(maturity_month_year) == maturity_month_year::size, "maturity_month_year lies over its bytes exactly");

// Md Instrument Definition Option Section 1
struct md_instrument_definition_option_section_1 {
    static constexpr std::string_view name = "Md Instrument Definition Option Section 1";
    static constexpr std::size_t size = 213;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        match_event_indicator,
        tot_num_reports_optional,
        security_update_action,
        last_update_time,
        md_security_trading_status,
        appl_id,
        market_segment_id,
        underlying_product,
        security_exchange,
        security_group,
        asset,
        symbol,
        security_id,
        security_type,
        cfi_code,
        put_or_call,
        maturity_month_year,
        currency,
        strike_price,
        strike_currency,
        settl_currency,
        min_cab_price,
        match_algorithm,
        min_trade_vol,
        max_trade_vol,
        min_price_increment_optional,
        min_price_increment_amount,
        display_factor,
        tick_rule,
        main_fraction,
        sub_fraction,
        price_display_format,
        unit_of_measure,
        unit_of_measure_qty,
        trading_reference_price,
        settl_price_type,
        cleared_volume,
        open_interest_qty,
        low_limit_price,
        high_limit_price,
        user_defined_instrument,
        trading_reference_date>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(match_event_indicator);
    MDP3FIELD(tot_num_reports_optional);
    MDP3FIELD(security_update_action);
    MDP3FIELD(last_update_time);
    MDP3FIELD(md_security_trading_status);
    MDP3FIELD(appl_id);
    MDP3FIELD(market_segment_id);
    MDP3FIELD(underlying_product);
    MDP3FIELD(security_exchange);
    MDP3FIELD(security_group);
    MDP3FIELD(asset);
    MDP3FIELD(symbol);
    MDP3FIELD(security_id);
    MDP3FIELD(security_type);
    MDP3FIELD(cfi_code);
    MDP3FIELD(put_or_call);
    MDP3FIELD(maturity_month_year);
    MDP3FIELD(currency);
    MDP3FIELD(strike_price);
    MDP3FIELD(strike_currency);
    MDP3FIELD(settl_currency);
    MDP3FIELD(min_cab_price);
    MDP3FIELD(match_algorithm);
    MDP3FIELD(min_trade_vol);
    MDP3FIELD(max_trade_vol);
    MDP3FIELD(min_price_increment_optional);
    MDP3FIELD(min_price_increment_amount);
    MDP3FIELD(display_factor);
    MDP3FIELD(tick_rule);
    MDP3FIELD(main_fraction);
    MDP3FIELD(sub_fraction);
    MDP3FIELD(price_display_format);
    MDP3FIELD(unit_of_measure);
    MDP3FIELD(unit_of_measure_qty);
    MDP3FIELD(trading_reference_price);
    MDP3FIELD(settl_price_type);
    MDP3FIELD(cleared_volume);
    MDP3FIELD(open_interest_qty);
    MDP3FIELD(low_limit_price);
    MDP3FIELD(high_limit_price);
    MDP3FIELD(user_defined_instrument);
    MDP3FIELD(trading_reference_date);
};

static_assert(sizeof(md_instrument_definition_option_section_1) == md_instrument_definition_option_section_1::size, "md_instrument_definition_option_section_1 lies over its bytes exactly");

// Md Instrument Definition Option: MDInstrumentDefinitionOption
struct md_instrument_definition_option {
    static constexpr std::string_view name = "Md Instrument Definition Option";
    static constexpr bool is_message = true;
};

// Related Sym Group: Indicates the number of repeating symbols specified
struct related_sym_group {
    static constexpr std::string_view name = "Related Sym Group";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        security_id,
        order_qty,
        quote_type,
        side,
        padding_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(symbol);
    MDP3FIELD(security_id);
    MDP3FIELD(order_qty);
    MDP3FIELD(quote_type);
    MDP3FIELD(side);
    MDP3FIELD(padding_2);
};

static_assert(sizeof(related_sym_group) == related_sym_group::size, "related_sym_group lies over its bytes exactly");

// Related Sym Groups: NoRelatedSym Block
struct related_sym_groups {
    static constexpr std::string_view name = "Related Sym Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(related_sym_group);
};

// Quote Request Section 1
struct quote_request_section_1 {
    static constexpr std::string_view name = "Quote Request Section 1";
    static constexpr std::size_t size = 35;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        transact_time,
        quote_req_id,
        match_event_indicator,
        padding_3>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(transact_time);
    MDP3FIELD(quote_req_id);
    MDP3FIELD(match_event_indicator);
    MDP3FIELD(padding_3);
};

static_assert(sizeof(quote_request_section_1) == quote_request_section_1::size, "quote_request_section_1 lies over its bytes exactly");

// Quote Request: QuoteRequest
struct quote_request {
    static constexpr std::string_view name = "Quote Request";
    static constexpr bool is_message = true;
};

// Snapshot Full Refresh Group: Number of entries in Market Data message
struct snapshot_full_refresh_group {
    static constexpr std::string_view name = "Snapshot Full Refresh Group";
    static constexpr std::size_t size = 22;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_entry_px_optional,
        md_entry_size_optional,
        number_of_orders,
        md_price_level_optional,
        trading_reference_date,
        open_close_settl_flag,
        settl_price_type,
        md_entry_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(md_entry_px_optional);
    MDP3FIELD(md_entry_size_optional);
    MDP3FIELD(number_of_orders);
    MDP3FIELD(md_price_level_optional);
    MDP3FIELD(trading_reference_date);
    MDP3FIELD(open_close_settl_flag);
    MDP3FIELD(settl_price_type);
    MDP3FIELD(md_entry_type);
};

static_assert(sizeof(snapshot_full_refresh_group) == snapshot_full_refresh_group::size, "snapshot_full_refresh_group lies over its bytes exactly");

// Snapshot Full Refresh Groups: NoMDEntries Block
struct snapshot_full_refresh_groups {
    static constexpr std::string_view name = "Snapshot Full Refresh Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(snapshot_full_refresh_group);
};

// Snapshot Full Refresh Section 1
struct snapshot_full_refresh_section_1 {
    static constexpr std::string_view name = "Snapshot Full Refresh Section 1";
    static constexpr std::size_t size = 59;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        last_msg_seq_num_processed,
        tot_num_reports,
        security_id,
        rpt_seq,
        transact_time,
        last_update_time,
        trade_date,
        md_security_trading_status,
        high_limit_price,
        low_limit_price,
        max_price_variation>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(last_msg_seq_num_processed);
    MDP3FIELD(tot_num_reports);
    MDP3FIELD(security_id);
    MDP3FIELD(rpt_seq);
    MDP3FIELD(transact_time);
    MDP3FIELD(last_update_time);
    MDP3FIELD(trade_date);
    MDP3FIELD(md_security_trading_status);
    MDP3FIELD(high_limit_price);
    MDP3FIELD(low_limit_price);
    MDP3FIELD(max_price_variation);
};

static_assert(sizeof(snapshot_full_refresh_section_1) == snapshot_full_refresh_section_1::size, "snapshot_full_refresh_section_1 lies over its bytes exactly");

// Snapshot Full Refresh: SnapshotFullRefresh
struct snapshot_full_refresh {
    static constexpr std::string_view name = "Snapshot Full Refresh";
    static constexpr bool is_message = true;
};

// Incremental Refresh Volume Group: Number of entries in Market Data message
struct incremental_refresh_volume_group {
    static constexpr std::string_view name = "Incremental Refresh Volume Group";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_entry_size,
        security_id,
        rpt_seq,
        md_update_action,
        padding_3>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(md_entry_size);
    MDP3FIELD(security_id);
    MDP3FIELD(rpt_seq);
    MDP3FIELD(md_update_action);
    MDP3FIELD(padding_3);
};

static_assert(sizeof(incremental_refresh_volume_group) == incremental_refresh_volume_group::size, "incremental_refresh_volume_group lies over its bytes exactly");

// Incremental Refresh Volume Groups: NoMDEntries Block
struct incremental_refresh_volume_groups {
    static constexpr std::string_view name = "Incremental Refresh Volume Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(incremental_refresh_volume_group);
};

// Md Incremental Refresh Volume Section 1
struct md_incremental_refresh_volume_section_1 {
    static constexpr std::string_view name = "Md Incremental Refresh Volume Section 1";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        transact_time,
        match_event_indicator,
        padding_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(transact_time);
    MDP3FIELD(match_event_indicator);
    MDP3FIELD(padding_2);
};

static_assert(sizeof(md_incremental_refresh_volume_section_1) == md_incremental_refresh_volume_section_1::size, "md_incremental_refresh_volume_section_1 lies over its bytes exactly");

// Md Incremental Refresh Volume: MDIncrementalRefreshVolume
struct md_incremental_refresh_volume {
    static constexpr std::string_view name = "Md Incremental Refresh Volume";
    static constexpr bool is_message = true;
};

// Incremental Refresh Trade Group: Number of entries in Market Data message
struct incremental_refresh_trade_group {
    static constexpr std::string_view name = "Incremental Refresh Trade Group";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_entry_px,
        md_entry_size,
        security_id,
        rpt_seq,
        number_of_orders,
        trade_id,
        aggressor_side,
        md_update_action,
        padding_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(md_entry_px);
    MDP3FIELD(md_entry_size);
    MDP3FIELD(security_id);
    MDP3FIELD(rpt_seq);
    MDP3FIELD(number_of_orders);
    MDP3FIELD(trade_id);
    MDP3FIELD(aggressor_side);
    MDP3FIELD(md_update_action);
    MDP3FIELD(padding_2);
};

static_assert(sizeof(incremental_refresh_trade_group) == incremental_refresh_trade_group::size, "incremental_refresh_trade_group lies over its bytes exactly");

// Incremental Refresh Trade Groups: NoMDEntries Block
struct incremental_refresh_trade_groups {
    static constexpr std::string_view name = "Incremental Refresh Trade Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(incremental_refresh_trade_group);
};

// Md Incremental Refresh Trade Section 1
struct md_incremental_refresh_trade_section_1 {
    static constexpr std::string_view name = "Md Incremental Refresh Trade Section 1";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        transact_time,
        match_event_indicator,
        padding_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(transact_time);
    MDP3FIELD(match_event_indicator);
    MDP3FIELD(padding_2);
};

static_assert(sizeof(md_incremental_refresh_trade_section_1) == md_incremental_refresh_trade_section_1::size, "md_incremental_refresh_trade_section_1 lies over its bytes exactly");

// Md Incremental Refresh Trade: MDIncrementalRefreshTrade
struct md_incremental_refresh_trade {
    static constexpr std::string_view name = "Md Incremental Refresh Trade";
    static constexpr bool is_message = true;
};

// Incremental Refresh Session Statistics Group: Number of entries in Market Data message
struct incremental_refresh_session_statistics_group {
    static constexpr std::string_view name = "Incremental Refresh Session Statistics Group";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_entry_px,
        security_id,
        rpt_seq,
        open_close_settl_flag,
        md_update_action,
        md_entry_type_statistics,
        md_entry_size_optional,
        padding_1>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(md_entry_px);
    MDP3FIELD(security_id);
    MDP3FIELD(rpt_seq);
    MDP3FIELD(open_close_settl_flag);
    MDP3FIELD(md_update_action);
    MDP3FIELD(md_entry_type_statistics);
    MDP3FIELD(md_entry_size_optional);
    MDP3FIELD(padding_1);
};

static_assert(sizeof(incremental_refresh_session_statistics_group) == incremental_refresh_session_statistics_group::size, "incremental_refresh_session_statistics_group lies over its bytes exactly");

// Incremental Refresh Session Statistics Groups: NoMDEntries Block
struct incremental_refresh_session_statistics_groups {
    static constexpr std::string_view name = "Incremental Refresh Session Statistics Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(incremental_refresh_session_statistics_group);
};

// Md Incremental Refresh Session Statistics Section 1
struct md_incremental_refresh_session_statistics_section_1 {
    static constexpr std::string_view name = "Md Incremental Refresh Session Statistics Section 1";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        transact_time,
        match_event_indicator,
        padding_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(transact_time);
    MDP3FIELD(match_event_indicator);
    MDP3FIELD(padding_2);
};

static_assert(sizeof(md_incremental_refresh_session_statistics_section_1) == md_incremental_refresh_session_statistics_section_1::size, "md_incremental_refresh_session_statistics_section_1 lies over its bytes exactly");

// Md Incremental Refresh Session Statistics: MDIncrementalRefreshSessionStatistics
struct md_incremental_refresh_session_statistics {
    static constexpr std::string_view name = "Md Incremental Refresh Session Statistics";
    static constexpr bool is_message = true;
};

// Incremental Refresh Limits Banding Group: Number of entries in Market Data message
struct incremental_refresh_limits_banding_group {
    static constexpr std::string_view name = "Incremental Refresh Limits Banding Group";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        high_limit_price,
        low_limit_price,
        max_price_variation,
        security_id,
        rpt_seq>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(high_limit_price);
    MDP3FIELD(low_limit_price);
    MDP3FIELD(max_price_variation);
    MDP3FIELD(security_id);
    MDP3FIELD(rpt_seq);
};

static_assert(sizeof(incremental_refresh_limits_banding_group) == incremental_refresh_limits_banding_group::size, "incremental_refresh_limits_banding_group lies over its bytes exactly");

// Incremental Refresh Limits Banding Groups: NoMDEntries Block
struct incremental_refresh_limits_banding_groups {
    static constexpr std::string_view name = "Incremental Refresh Limits Banding Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(incremental_refresh_limits_banding_group);
};

// Md Incremental Refresh Limits Banding Section 1
struct md_incremental_refresh_limits_banding_section_1 {
    static constexpr std::string_view name = "Md Incremental Refresh Limits Banding Section 1";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        transact_time,
        match_event_indicator,
        padding_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(transact_time);
    MDP3FIELD(match_event_indicator);
    MDP3FIELD(padding_2);
};

static_assert(sizeof(md_incremental_refresh_limits_banding_section_1) == md_incremental_refresh_limits_banding_section_1::size, "md_incremental_refresh_limits_banding_section_1 lies over its bytes exactly");

// Md Incremental Refresh Limits Banding: MDIncrementalRefreshLimitsBanding
struct md_incremental_refresh_limits_banding {
    static constexpr std::string_view name = "Md Incremental Refresh Limits Banding";
    static constexpr bool is_message = true;
};

// Incremental Refresh Daily Statistics Group: Number of entries in Market Data message
struct incremental_refresh_daily_statistics_group {
    static constexpr std::string_view name = "Incremental Refresh Daily Statistics Group";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_entry_px_optional,
        md_entry_size_optional,
        security_id,
        rpt_seq,
        trading_reference_date,
        settl_price_type,
        md_update_action,
        md_entry_type_daily_statistics,
        padding_7>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(md_entry_px_optional);
    MDP3FIELD(md_entry_size_optional);
    MDP3FIELD(security_id);
    MDP3FIELD(rpt_seq);
    MDP3FIELD(trading_reference_date);
    MDP3FIELD(settl_price_type);
    MDP3FIELD(md_update_action);
    MDP3FIELD(md_entry_type_daily_statistics);
    MDP3FIELD(padding_7);
};

static_assert(sizeof(incremental_refresh_daily_statistics_group) == incremental_refresh_daily_statistics_group::size, "incremental_refresh_daily_statistics_group lies over its bytes exactly");

// Incremental Refresh Daily Statistics Groups: NoMDEntries Block
struct incremental_refresh_daily_statistics_groups {
    static constexpr std::string_view name = "Incremental Refresh Daily Statistics Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(incremental_refresh_daily_statistics_group);
};

// Md Incremental Refresh Daily Statistics Section 1
struct md_incremental_refresh_daily_statistics_section_1 {
    static constexpr std::string_view name = "Md Incremental Refresh Daily Statistics Section 1";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        transact_time,
        match_event_indicator,
        padding_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(transact_time);
    MDP3FIELD(match_event_indicator);
    MDP3FIELD(padding_2);
};

static_assert(sizeof(md_incremental_refresh_daily_statistics_section_1) == md_incremental_refresh_daily_statistics_section_1::size, "md_incremental_refresh_daily_statistics_section_1 lies over its bytes exactly");

// Md Incremental Refresh Daily Statistics: MDIncrementalRefreshDailyStatistics
struct md_incremental_refresh_daily_statistics {
    static constexpr std::string_view name = "Md Incremental Refresh Daily Statistics";
    static constexpr bool is_message = true;
};

// Incremental Refresh Book Order Id Group: Number of OrderID entries
struct incremental_refresh_book_order_id_group {
    static constexpr std::string_view name = "Incremental Refresh Book Order Id Group";
    static constexpr std::size_t size = 24;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        order_id,
        md_order_priority,
        md_display_qty_optional,
        reference_id,
        order_update_action,
        padding_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(order_id);
    MDP3FIELD(md_order_priority);
    MDP3FIELD(md_display_qty_optional);
    MDP3FIELD(reference_id);
    MDP3FIELD(order_update_action);
    MDP3FIELD(padding_2);
};

static_assert(sizeof(incremental_refresh_book_order_id_group) == incremental_refresh_book_order_id_group::size, "incremental_refresh_book_order_id_group lies over its bytes exactly");

// Incremental Refresh Book Order Id Groups: NoOrderIDEntries Block
struct incremental_refresh_book_order_id_groups {
    static constexpr std::string_view name = "Incremental Refresh Book Order Id Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(incremental_refresh_book_order_id_group);
};

// Incremental Refresh Book Group: Number of entries in Market Data message
struct incremental_refresh_book_group {
    static constexpr std::string_view name = "Incremental Refresh Book Group";
    static constexpr std::size_t size = 32;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_entry_px_optional,
        md_entry_size_optional,
        security_id,
        rpt_seq,
        number_of_orders,
        md_price_level,
        md_update_action,
        md_entry_type_book,
        padding_5>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(md_entry_px_optional);
    MDP3FIELD(md_entry_size_optional);
    MDP3FIELD(security_id);
    MDP3FIELD(rpt_seq);
    MDP3FIELD(number_of_orders);
    MDP3FIELD(md_price_level);
    MDP3FIELD(md_update_action);
    MDP3FIELD(md_entry_type_book);
    MDP3FIELD(padding_5);
};

static_assert(sizeof(incremental_refresh_book_group) == incremental_refresh_book_group::size, "incremental_refresh_book_group lies over its bytes exactly");

// Incremental Refresh Book Groups: NoMDEntries Block
struct incremental_refresh_book_groups {
    static constexpr std::string_view name = "Incremental Refresh Book Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(incremental_refresh_book_group);
};

// Md Incremental Refresh Book Section 1
struct md_incremental_refresh_book_section_1 {
    static constexpr std::string_view name = "Md Incremental Refresh Book Section 1";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        transact_time,
        match_event_indicator,
        padding_2>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(transact_time);
    MDP3FIELD(match_event_indicator);
    MDP3FIELD(padding_2);
};

static_assert(sizeof(md_incremental_refresh_book_section_1) == md_incremental_refresh_book_section_1::size, "md_incremental_refresh_book_section_1 lies over its bytes exactly");

// Md Incremental Refresh Book: MDIncrementalRefreshBook
struct md_incremental_refresh_book {
    static constexpr std::string_view name = "Md Incremental Refresh Book";
    static constexpr bool is_message = true;
};

// Security Status: SecurityStatus
struct security_status {
    static constexpr std::string_view name = "Security Status";
    static constexpr std::size_t size = 30;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        transact_time,
        security_group,
        asset,
        security_id_optional,
        trade_date,
        match_event_indicator,
        security_trading_status,
        halt_reason,
        security_trading_event>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(transact_time);
    MDP3FIELD(security_group);
    MDP3FIELD(asset);
    MDP3FIELD(security_id_optional);
    MDP3FIELD(trade_date);
    MDP3FIELD(match_event_indicator);
    MDP3FIELD(security_trading_status);
    MDP3FIELD(halt_reason);
    MDP3FIELD(security_trading_event);
};

static_assert(sizeof(security_status) == security_status::size, "security_status lies over its bytes exactly");

// Legacy Legs Group: Number of Leg entries
struct legacy_legs_group {
    static constexpr std::string_view name = "Legacy Legs Group";
    static constexpr std::size_t size = 18;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        leg_security_id,
        leg_side,
        leg_ratio_qty,
        leg_price,
        leg_option_delta>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(leg_security_id);
    MDP3FIELD(leg_side);
    MDP3FIELD(leg_ratio_qty);
    MDP3FIELD(leg_price);
    MDP3FIELD(leg_option_delta);
};

static_assert(sizeof(legacy_legs_group) == legacy_legs_group::size, "legacy_legs_group lies over its bytes exactly");

// Legacy Legs Groups: NoLegs Block
struct legacy_legs_groups {
    static constexpr std::string_view name = "Legacy Legs Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(legacy_legs_group);
};

// Md Instrument Definition Spread Section 1
struct md_instrument_definition_spread_section_1 {
    static constexpr std::string_view name = "Md Instrument Definition Spread Section 1";
    static constexpr std::size_t size = 195;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        match_event_indicator,
        tot_num_reports_optional,
        security_update_action,
        last_update_time,
        md_security_trading_status,
        appl_id,
        market_segment_id,
        underlying_product_optional,
        security_exchange,
        security_group,
        asset,
        symbol,
        security_id,
        security_type,
        cfi_code,
        maturity_month_year,
        currency,
        security_sub_type,
        user_defined_instrument,
        match_algorithm,
        min_trade_vol,
        max_trade_vol,
        min_price_increment,
        display_factor,
        price_display_format,
        price_ratio,
        tick_rule,
        unit_of_measure,
        trading_reference_price,
        settl_price_type,
        open_interest_qty,
        cleared_volume,
        high_limit_price,
        low_limit_price,
        max_price_variation,
        main_fraction,
        sub_fraction,
        trading_reference_date>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(match_event_indicator);
    MDP3FIELD(tot_num_reports_optional);
    MDP3FIELD(security_update_action);
    MDP3FIELD(last_update_time);
    MDP3FIELD(md_security_trading_status);
    MDP3FIELD(appl_id);
    MDP3FIELD(market_segment_id);
    MDP3FIELD(underlying_product_optional);
    MDP3FIELD(security_exchange);
    MDP3FIELD(security_group);
    MDP3FIELD(asset);
    MDP3FIELD(symbol);
    MDP3FIELD(security_id);
    MDP3FIELD(security_type);
    MDP3FIELD(cfi_code);
    MDP3FIELD(maturity_month_year);
    MDP3FIELD(currency);
    MDP3FIELD(security_sub_type);
    MDP3FIELD(user_defined_instrument);
    MDP3FIELD(match_algorithm);
    MDP3FIELD(min_trade_vol);
    MDP3FIELD(max_trade_vol);
    MDP3FIELD(min_price_increment);
    MDP3FIELD(display_factor);
    MDP3FIELD(price_display_format);
    MDP3FIELD(price_ratio);
    MDP3FIELD(tick_rule);
    MDP3FIELD(unit_of_measure);
    MDP3FIELD(trading_reference_price);
    MDP3FIELD(settl_price_type);
    MDP3FIELD(open_interest_qty);
    MDP3FIELD(cleared_volume);
    MDP3FIELD(high_limit_price);
    MDP3FIELD(low_limit_price);
    MDP3FIELD(max_price_variation);
    MDP3FIELD(main_fraction);
    MDP3FIELD(sub_fraction);
    MDP3FIELD(trading_reference_date);
};

static_assert(sizeof(md_instrument_definition_spread_section_1) == md_instrument_definition_spread_section_1::size, "md_instrument_definition_spread_section_1 lies over its bytes exactly");

// Md Instrument Definition Spread: MDInstrumentDefinitionSpread
struct md_instrument_definition_spread {
    static constexpr std::string_view name = "Md Instrument Definition Spread";
    static constexpr bool is_message = true;
};

// Md Instrument Definition Future Section 1
struct md_instrument_definition_future_section_1 {
    static constexpr std::string_view name = "Md Instrument Definition Future Section 1";
    static constexpr std::size_t size = 216;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        match_event_indicator,
        tot_num_reports_optional,
        security_update_action,
        last_update_time,
        md_security_trading_status,
        appl_id,
        market_segment_id,
        underlying_product,
        security_exchange,
        security_group,
        asset,
        symbol,
        security_id,
        security_type,
        cfi_code,
        maturity_month_year,
        currency,
        settl_currency,
        match_algorithm,
        min_trade_vol,
        max_trade_vol,
        min_price_increment,
        display_factor,
        main_fraction,
        sub_fraction,
        price_display_format,
        unit_of_measure,
        unit_of_measure_qty,
        trading_reference_price,
        settl_price_type,
        open_interest_qty,
        cleared_volume,
        high_limit_price,
        low_limit_price,
        max_price_variation,
        decay_quantity,
        decay_start_date,
        original_contract_size,
        contract_multiplier,
        contract_multiplier_unit,
        flow_schedule_type,
        min_price_increment_amount,
        user_defined_instrument,
        trading_reference_date>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(match_event_indicator);
    MDP3FIELD(tot_num_reports_optional);
    MDP3FIELD(security_update_action);
    MDP3FIELD(last_update_time);
    MDP3FIELD(md_security_trading_status);
    MDP3FIELD(appl_id);
    MDP3FIELD(market_segment_id);
    MDP3FIELD(underlying_product);
    MDP3FIELD(security_exchange);
    MDP3FIELD(security_group);
    MDP3FIELD(asset);
    MDP3FIELD(symbol);
    MDP3FIELD(security_id);
    MDP3FIELD(security_type);
    MDP3FIELD(cfi_code);
    MDP3FIELD(maturity_month_year);
    MDP3FIELD(currency);
    MDP3FIELD(settl_currency);
    MDP3FIELD(match_algorithm);
    MDP3FIELD(min_trade_vol);
    MDP3FIELD(max_trade_vol);
    MDP3FIELD(min_price_increment);
    MDP3FIELD(display_factor);
    MDP3FIELD(main_fraction);
    MDP3FIELD(sub_fraction);
    MDP3FIELD(price_display_format);
    MDP3FIELD(unit_of_measure);
    MDP3FIELD(unit_of_measure_qty);
    MDP3FIELD(trading_reference_price);
    MDP3FIELD(settl_price_type);
    MDP3FIELD(open_interest_qty);
    MDP3FIELD(cleared_volume);
    MDP3FIELD(high_limit_price);
    MDP3FIELD(low_limit_price);
    MDP3FIELD(max_price_variation);
    MDP3FIELD(decay_quantity);
    MDP3FIELD(decay_start_date);
    MDP3FIELD(original_contract_size);
    MDP3FIELD(contract_multiplier);
    MDP3FIELD(contract_multiplier_unit);
    MDP3FIELD(flow_schedule_type);
    MDP3FIELD(min_price_increment_amount);
    MDP3FIELD(user_defined_instrument);
    MDP3FIELD(trading_reference_date);
};

static_assert(sizeof(md_instrument_definition_future_section_1) == md_instrument_definition_future_section_1::size, "md_instrument_definition_future_section_1 lies over its bytes exactly");

// Md Instrument Definition Future: MDInstrumentDefinitionFuture
struct md_instrument_definition_future {
    static constexpr std::string_view name = "Md Instrument Definition Future";
    static constexpr bool is_message = true;
};

// Admin Logout: AdminLogout
struct admin_logout {
    static constexpr std::string_view name = "Admin Logout";
    static constexpr std::size_t size = 100;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        text>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(text);
};

static_assert(sizeof(admin_logout) == admin_logout::size, "admin_logout lies over its bytes exactly");

// Admin Login: AdminLogin
struct admin_login {
    static constexpr std::string_view name = "Admin Login";
    static constexpr std::size_t size = 1;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        heart_bt_int>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(heart_bt_int);
};

static_assert(sizeof(admin_login) == admin_login::size, "admin_login lies over its bytes exactly");

// Admin Heartbeat
struct admin_heartbeat {
    static constexpr std::string_view name = "Admin Heartbeat";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Channel Reset Group: Number of entries in Market Data message
struct channel_reset_group {
    static constexpr std::string_view name = "Channel Reset Group";
    static constexpr std::size_t size = 2;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        appl_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(appl_id);
};

static_assert(sizeof(channel_reset_group) == channel_reset_group::size, "channel_reset_group lies over its bytes exactly");

// Channel Reset Groups: NoMDEntries Block
struct channel_reset_groups {
    static constexpr std::string_view name = "Channel Reset Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(channel_reset_group);
};

// Channel Reset Section 1
struct channel_reset_section_1 {
    static constexpr std::string_view name = "Channel Reset Section 1";
    static constexpr std::size_t size = 9;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        transact_time,
        match_event_indicator>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(transact_time);
    MDP3FIELD(match_event_indicator);
};

static_assert(sizeof(channel_reset_section_1) == channel_reset_section_1::size, "channel_reset_section_1 lies over its bytes exactly");

// Channel Reset: ChannelReset
struct channel_reset {
    static constexpr std::string_view name = "Channel Reset";
    static constexpr bool is_message = true;
};

// Server Payload: Cme message body sent by Cme to the firm
struct server_payload {
    static constexpr std::string_view name = "Server Payload";
    static constexpr bool is_message = false;
};

// Message Header: Template ID and length of message root
struct message_header {
    static constexpr std::string_view name = "Message Header";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        block_length,
        template_id,
        schema_id,
        version>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(block_length);
    MDP3FIELD(template_id);
    MDP3FIELD(schema_id);
    MDP3FIELD(version);
};

static_assert(sizeof(message_header) == message_header::size, "message_header lies over its bytes exactly");

// Server Tcp Message: Cme Tcp Message sent by Cme to the firm
struct server_tcp_message {
    static constexpr std::string_view name = "Server Tcp Message";
    static constexpr bool is_message = false;
};

// Server Technical Header: Cme Technical Header sent by Cme to the firm. Tcp Message Size is the last field so this fixed 16 byte header spans everything up to and including the length the reassembly reads.
struct server_technical_header {
    static constexpr std::string_view name = "Server Technical Header";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        encoding_type,
        message_sequence_number,
        tcp_sending_time,
        tcp_message_size>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(encoding_type);
    MDP3FIELD(message_sequence_number);
    MDP3FIELD(tcp_sending_time);
    MDP3FIELD(tcp_message_size);
};

static_assert(sizeof(server_technical_header) == server_technical_header::size, "server_technical_header lies over its bytes exactly");

// Server Tcp Frame: One technical header and the message it carries: the unit the wire repeats
struct server_tcp_frame {
    static constexpr std::string_view name = "Server Tcp Frame";
    static constexpr bool is_message = false;
};

// Server Tcp Packet: Cme Sbe Tcp Packet sent by Cme to the firm
struct server_tcp_packet {
    static constexpr std::string_view name = "Server Tcp Packet";
    static constexpr bool is_message = false;
};

// Subscriber Heartbeat
struct subscriber_heartbeat {
    static constexpr std::string_view name = "Subscriber Heartbeat";
    static constexpr std::size_t size = 0;
    static constexpr bool is_message = true;
};

// Security Status Request Related Symbol Group: Number of instruments requested. When NoSecurityGroups > 0 specified in the request, the NoRelatedSym should be equal 0
struct security_status_request_related_symbol_group {
    static constexpr std::string_view name = "Security Status Request Related Symbol Group";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(security_id);
};

static_assert(sizeof(security_status_request_related_symbol_group) == security_status_request_related_symbol_group::size, "security_status_request_related_symbol_group lies over its bytes exactly");

// Security Status Request Related Symbol Groups: NoRelatedSym Block
struct security_status_request_related_symbol_groups {
    static constexpr std::string_view name = "Security Status Request Related Symbol Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(security_status_request_related_symbol_group);
};

// Security Status Request Security Group: Number of SecurityGroups specified in subscription request. Should be equal 0, when subscription is requested for all groups on the segment or individual Security IDs are listed in the criteria for subscription
struct security_status_request_security_group {
    static constexpr std::string_view name = "Security Status Request Security Group";
    static constexpr std::size_t size = 6;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_group>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(security_group);
};

static_assert(sizeof(security_status_request_security_group) == security_status_request_security_group::size, "security_status_request_security_group lies over its bytes exactly");

// Security Status Request Security Groups: NoSecurityGroups Block
struct security_status_request_security_groups {
    static constexpr std::string_view name = "Security Status Request Security Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(security_status_request_security_group);
};

// Security Status Request Section 1
struct security_status_request_section_1 {
    static constexpr std::string_view name = "Security Status Request Section 1";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_req_id,
        subscription_req_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(md_req_id);
    MDP3FIELD(subscription_req_type);
};

static_assert(sizeof(security_status_request_section_1) == security_status_request_section_1::size, "security_status_request_section_1 lies over its bytes exactly");

// Security Status Request: SecurityStatusRequest
struct security_status_request {
    static constexpr std::string_view name = "Security Status Request";
    static constexpr bool is_message = true;
};

// Security List Request Related Symbol Group: Number of instruments requested. When NoSecurityGroups > 0 specified in the request, the NoRelatedSym should be equal 0
struct security_list_request_related_symbol_group {
    static constexpr std::string_view name = "Security List Request Related Symbol Group";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(security_id);
};

static_assert(sizeof(security_list_request_related_symbol_group) == security_list_request_related_symbol_group::size, "security_list_request_related_symbol_group lies over its bytes exactly");

// Security List Request Related Symbol Groups: NoRelatedSym Block
struct security_list_request_related_symbol_groups {
    static constexpr std::string_view name = "Security List Request Related Symbol Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(security_list_request_related_symbol_group);
};

// Security List Request Security Group: Number of SecurityGroups specified in subscription request. Should be equal 0, when subscription is requested for all groups on the segment or individual Security IDs are listed in the criteria for subscription
struct security_list_request_security_group {
    static constexpr std::string_view name = "Security List Request Security Group";
    static constexpr std::size_t size = 6;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_group>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(security_group);
};

static_assert(sizeof(security_list_request_security_group) == security_list_request_security_group::size, "security_list_request_security_group lies over its bytes exactly");

// Security List Request Security Groups: NoSecurityGroups Block
struct security_list_request_security_groups {
    static constexpr std::string_view name = "Security List Request Security Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(security_list_request_security_group);
};

// Security List Request Section 1
struct security_list_request_section_1 {
    static constexpr std::string_view name = "Security List Request Section 1";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_req_id,
        subscription_req_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(md_req_id);
    MDP3FIELD(subscription_req_type);
};

static_assert(sizeof(security_list_request_section_1) == security_list_request_section_1::size, "security_list_request_section_1 lies over its bytes exactly");

// Security List Request: SecurityListRequest
struct security_list_request {
    static constexpr std::string_view name = "Security List Request";
    static constexpr bool is_message = true;
};

// Market Data Request Related Symbol Group: Number of instruments requested. When NoSecurityGroups > 0 specified in the request, the NoRelatedSym should be equal 0
struct market_data_request_related_symbol_group {
    static constexpr std::string_view name = "Market Data Request Related Symbol Group";
    static constexpr std::size_t size = 4;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(security_id);
};

static_assert(sizeof(market_data_request_related_symbol_group) == market_data_request_related_symbol_group::size, "market_data_request_related_symbol_group lies over its bytes exactly");

// Market Data Request Related Symbol Groups: NoRelatedSym Block
struct market_data_request_related_symbol_groups {
    static constexpr std::string_view name = "Market Data Request Related Symbol Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(market_data_request_related_symbol_group);
};

// Market Data Request Security Group: Number of SecurityGroups specified in subscription request. Should be equal 0, when subscription is requested for all groups on the segment or individual Security IDs are listed in the criteria for subscription
struct market_data_request_security_group {
    static constexpr std::string_view name = "Market Data Request Security Group";
    static constexpr std::size_t size = 6;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        security_group>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(security_group);
};

static_assert(sizeof(market_data_request_security_group) == market_data_request_security_group::size, "market_data_request_security_group lies over its bytes exactly");

// Market Data Request Security Groups: NoSecurityGroups Block
struct market_data_request_security_groups {
    static constexpr std::string_view name = "Market Data Request Security Groups";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    MDP3SEQUENCE(market_data_request_security_group);
};

// Market Data Request Section 1
struct market_data_request_section_1 {
    static constexpr std::string_view name = "Market Data Request Section 1";
    static constexpr std::size_t size = 5;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        md_req_id,
        subscription_req_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(md_req_id);
    MDP3FIELD(subscription_req_type);
};

static_assert(sizeof(market_data_request_section_1) == market_data_request_section_1::size, "market_data_request_section_1 lies over its bytes exactly");

// Market Data Request: MarketDataRequest
struct market_data_request {
    static constexpr std::string_view name = "Market Data Request";
    static constexpr bool is_message = true;
};

// Negotiate
struct negotiate {
    static constexpr std::string_view name = "Negotiate";
    static constexpr std::size_t size = 78;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        hmac_signature,
        access_key_id,
        uuid,
        request_timestamp,
        session,
        firm>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(hmac_signature);
    MDP3FIELD(access_key_id);
    MDP3FIELD(uuid);
    MDP3FIELD(request_timestamp);
    MDP3FIELD(session);
    MDP3FIELD(firm);
};

static_assert(sizeof(negotiate) == negotiate::size, "negotiate lies over its bytes exactly");

// Client Payload: Cme message body sent by the firm to Cme
struct client_payload {
    static constexpr std::string_view name = "Client Payload";
    static constexpr bool is_message = false;
};

// Client Tcp Message: Cme Tcp Message sent by the firm to Cme
struct client_tcp_message {
    static constexpr std::string_view name = "Client Tcp Message";
    static constexpr bool is_message = false;
};

// Client Technical Header: Cme Technical Header sent by the firm to Cme. Tcp Message Size is the last field so this fixed 16 byte header spans everything up to and including the length the reassembly reads.
struct client_technical_header {
    static constexpr std::string_view name = "Client Technical Header";
    static constexpr std::size_t size = 16;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        encoding_type,
        message_sequence_number,
        tcp_sending_time,
        tcp_message_size>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(encoding_type);
    MDP3FIELD(message_sequence_number);
    MDP3FIELD(tcp_sending_time);
    MDP3FIELD(tcp_message_size);
};

static_assert(sizeof(client_technical_header) == client_technical_header::size, "client_technical_header lies over its bytes exactly");

// Client Tcp Frame: One technical header and the message it carries: the unit the wire repeats
struct client_tcp_frame {
    static constexpr std::string_view name = "Client Tcp Frame";
    static constexpr bool is_message = false;
};

// Client Tcp Packet: Cme Sbe Tcp Packet sent by the firm to Cme
struct client_tcp_packet {
    static constexpr std::string_view name = "Client Tcp Packet";
    static constexpr bool is_message = false;
};

// Mdpsessionmgmt Payload: Branch
struct mdpsessionmgmt_payload {
    static constexpr std::string_view name = "Mdpsessionmgmt Payload";
    static constexpr bool is_message = false;
};

// Mdpsessionmgmt Message: Message of sbe schema mdpsessionmgmt (schema id 2)
struct mdpsessionmgmt_message {
    static constexpr std::string_view name = "Mdpsessionmgmt Message";
    static constexpr bool is_message = false;
};

// Mktdata Payload: Branch
struct mktdata_payload {
    static constexpr std::string_view name = "Mktdata Payload";
    static constexpr bool is_message = false;
};

// Mktdata Message: Message of sbe schema mktdata (schema id 1)
struct mktdata_message {
    static constexpr std::string_view name = "Mktdata Message";
    static constexpr bool is_message = false;
};

// Payload: Branch
struct payload {
    static constexpr std::string_view name = "Payload";
    static constexpr bool is_message = false;
};

// Message Section 1
struct message_section_1 {
    static constexpr std::string_view name = "Message Section 1";
    static constexpr std::size_t size = 10;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        message_size,
        message_header>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(message_size);
    MDP3FIELD(message_header);
};

static_assert(sizeof(message_section_1) == message_section_1::size, "message_section_1 lies over its bytes exactly");

// Message: Cme Market Data Message
struct message {
    static constexpr std::string_view name = "Message";
    static constexpr bool is_message = false;
};

// Binary Packet Header: Cme Mdp Packet Header
struct binary_packet_header {
    static constexpr std::string_view name = "Binary Packet Header";
    static constexpr std::size_t size = 12;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        packet_sequence_number,
        sending_time>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    MDP3FIELD(packet_sequence_number);
    MDP3FIELD(sending_time);
};

static_assert(sizeof(binary_packet_header) == binary_packet_header::size, "binary_packet_header lies over its bytes exactly");

// Udp Packet: Cme Mdp Packet
struct udp_packet {
    static constexpr std::string_view name = "Udp Packet";
    static constexpr bool is_message = false;
};

#pragma pack(pop)

} // namespace cme::globex::mdp3::sbe::v1_8
