#pragma once

#include "FlowControl/Manipulators/Helpers/DamageHelper.h"
#include "state/State.h"

namespace FlowControl
{
	namespace Manipulators
	{
		namespace Helpers
		{
			inline DamageHelper::DamageHelper(state::State & state, FlowControl::FlowContext & flow_context, state::CardRef card_ref, state::Cards::Card & card, int amount)
			{
				// TODO: consider prophet effects

				// TODO: add a new event type: PreTakeDamage
				// this might change the card_ref, and the damage amount
				state::CardRef new_target = card_ref; // TODO
				int new_amount = amount; // TODO
				if (new_amount <= 0) return;

				state::Cards::Card const& new_target_card = state.GetCard(new_target);
				if (new_target_card.GetRawData().enchanted_states.shielded) {
					Manipulate(state, flow_context).Character(new_target).Shield(false);
					return;
				}

				DoDamage(state, flow_context, new_target, new_target_card, new_amount);
			}

			inline void DamageHelper::DoDamage(state::State & state, FlowControl::FlowContext & flow_context, state::CardRef card_ref, state::Cards::Card const& card, int amount)
			{
				state.TriggerEvent<state::Events::EventTypes::OnTakeDamage>(card_ref,
					state::Events::EventTypes::OnTakeDamage::Context{ state, flow_context, card, amount });
				state.TriggerCategorizedEvent<state::Events::EventTypes::OnTakeDamage>(card_ref,
					state::Events::EventTypes::OnTakeDamage::Context{ state, flow_context, card, amount });

				Manipulate(state, flow_context).Card(card_ref).Internal_SetDamage().TakeDamage(amount);
				flow_context.AddDeadEntryHint(state, card_ref);
			}
		}
	}
}