#include "QuoteRejectReason.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(QuoteRejectReason value) {
    switch (value) {
        case QuoteRejectReason::TechnicalErrorFunctionNotPerformed: return "Technical Error: Function not performed";
        case QuoteRejectReason::ExercisePriceNotAllowed: return "Exercise price not allowed";
        case QuoteRejectReason::NoPositionsBlocked: return "No positions blocked";
        case QuoteRejectReason::QuantityDoesntMatchWithTheOriginalRequestQuantityOnOriginalRequestQuantityOnOriginalRequest: return "Quantity doesn't match with the original request [Quantity on original request: <quantity on original request>]";
        case QuoteRejectReason::ExerciseMustBeOnMaturityDate: return "Exercise must be on maturity date.";
        case QuoteRejectReason::FunctionNotAvailableThisTime: return "Function not available this time";
        case QuoteRejectReason::BlockingQuantityMoreThan999999999: return "Blocking quantity more than 999999999";
        case QuoteRejectReason::TradeDoesNotBelongToTheSpecifiedFirmFirmIdXxx: return "Trade does not belong to the specified firm ‘Firm Id: <XXX>’";
        case QuoteRejectReason::BlockingQtyMoreThanAvailableQuantity: return "Blocking qty more than available quantity";
        case QuoteRejectReason::ThereArentPositionsAvailableToExercise: return "There aren't positions available to exercise";
        case QuoteRejectReason::TotalQtyMustBeTheSumOfAllAllocqty: return "Total qty must be the sum of all AllocQty";
        case QuoteRejectReason::TradeAlreadyCancelledOrDoesNotExistTradeIdXxx: return "Trade already cancelled or does not exist ‘Trade Id: <XXX>’";
        case QuoteRejectReason::AvailableQuantityToBlockIsZero: return "Available quantity to block is zero";
        case QuoteRejectReason::InvalidOperationForContractType: return "Invalid Operation for contract type.";
        case QuoteRejectReason::FunctionClosedOrSuspended: return "Function closed or suspended.";
        case QuoteRejectReason::ExercisePriceOutsideRequiredMoneyness: return "Exercise price outside required moneyness.";
        case QuoteRejectReason::InvalidExerciseRequestIdToCancel: return "Invalid exercise request id to cancel";
        case QuoteRejectReason::InvalidBlockingIdToUnblock: return "Invalid blocking Id to unblock";
        case QuoteRejectReason::InvalidQuantityToUnblock: return "Invalid quantity to unblock";
        case QuoteRejectReason::OnBehalfOperationNotAllowedDuringCcrRecovery: return "On Behalf Operation not allowed during CCR recovery";
        case QuoteRejectReason::ProblemParsingIncomingMessage: return "Problem parsing incoming message";
        case QuoteRejectReason::ExerciseQuantityShouldBeGreaterThanZero: return "Exercise quantity should be greater than zero";
        case QuoteRejectReason::ContraryExerciseAlreadyRegisteredForThisPosition: return "Contrary Exercise already registered for this position";
        case QuoteRejectReason::InthemoneyContractAllowsContraryExerciseToNotExerciseAutomaticallyOnly: return "In-the-money contract allows Contrary Exercise to not exercise automatically only";
        case QuoteRejectReason::AtoutthemoneyContractAllowsContraryExerciseToExerciseAutomaticallyOnly: return "At/Out-the-money contract allows Contrary Exercise to exercise automatically only";
        case QuoteRejectReason::DmaIsNotAllowedToRequestContraryExercise: return "DMA is not allowed to request Contrary Exercise";
        case QuoteRejectReason::ContraryExercisesCanOnlyBeRequestedByDefaultLinkOrPositionOwnerWithDirectAccessOnAbsenceOfDefaultLink: return "Contrary Exercises can only be requested by default link or position owner with direct access on absence of default link";
        case QuoteRejectReason::ContraryExerciseInvalidOperation: return "Contrary Exercise invalid operation.";
        case QuoteRejectReason::ThresholdMustNotBeInformed: return "Threshold must not be informed";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, QuoteRejectReason value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
