#include "WheelItemArmor.h"
#include "../../Rendering/Drawer.h"
#include "../../Utilities/Utils.h"

void WheelItemArmor::DrawSlot(ImVec2 a_center, bool a_hovered, RE::TESObjectREFR::InventoryItemMap& a_imap, DrawArgs a_drawArgs)
{
	std::string text = this->_obj->GetName();
	int itemCount = this->GetItemExtraDataAndCount(a_imap).first;
	if (itemCount > 1) {
		text += " (" + std::to_string(itemCount) + ")";
	}
	this->drawSlotText(a_center, text.data(), a_drawArgs);
	this->drawSlotTexture(a_center, a_drawArgs);
}

void WheelItemArmor::DrawHighlight(ImVec2 a_center, RE::TESObjectREFR::InventoryItemMap& a_imap, DrawArgs a_drawArgs)
{
	this->drawHighlightText(a_center, this->_obj->GetName(), a_drawArgs);
	this->drawHighlightTexture(a_center, a_drawArgs);

	// get inventory entry data, ptr -> unique_ptr(dangerous)
	RE::TESObjectARMO* armor = this->_obj->As<RE::TESObjectARMO>();
	RE::InventoryEntryData* invData = nullptr;
	if (a_imap.contains(armor)) {
		invData = a_imap.find(armor)->second.second.get();
	}
	
	std::string descriptionBuf = "";
	// first check if description is empty, if not we just show the description itself, armor's sepcial description is probably more important.
	if (!this->_description.empty()) {  // non-empty description, armor's main description takes priority(it's probably a special armor)
		descriptionBuf = this->_description;
	} else if (invData != nullptr) {
		// try to get enchant of this armor
		std::vector<RE::EnchantmentItem*> enchants;
		this->GetItemEnchantment(invData, enchants);
		if (!enchants.empty()) {
			// take 1st item for now.
			Utils::Magic::GetMagicItemDescription(enchants[0], descriptionBuf);
		}
	}
	this->drawHighlightDescription(a_center, descriptionBuf.data(), a_drawArgs);

	// draw armor rating
	float armorRating = 0;
	if (invData != nullptr) {
		armorRating = RE::PlayerCharacter::GetSingleton()->GetArmorValue(invData);
	} else {
		armorRating = armor->GetArmorRating();
	}

	this->drawItemHighlightStatIconAndValue(a_center, this->_stat_texture, armorRating, a_drawArgs);
	
}

WheelItemArmor::WheelItemArmor(RE::TESBoundObject* a_armor, uint16_t a_uniqueID)
{
	if (a_armor->GetFormType() != RE::FormType::Armor) {
		throw std::exception("WheelItemArmor::ctor: a_armor is not an armor!");
	}
	this->_obj = a_armor;
	this->SetUniqueID(a_uniqueID);
	// get armor texture
	RE::TESObjectARMO* armor = a_armor->As<RE::TESObjectARMO>();
	using SlotEnum = RE::BGSBipedObjectForm::BipedObjectSlot;
	Texture::icon_image_type iconType = Texture::icon_image_type::armor_default;
	if (armor->HasKeywordString("ArmorJewelry") || armor->HasKeywordString("VendorItemJewelry") || armor->HasKeywordString("JewelryExpensive")) {
		if (armor->HasKeywordString("ClothingNecklace") || armor->HasPartOf(SlotEnum::kAmulet)) {
			iconType = Texture::icon_image_type::armor_necklace;
		} else if (armor->HasKeywordString("ClothingCirclet") || armor->HasPartOf(SlotEnum::kCirclet)) {
			iconType = Texture::icon_image_type::armor_circlet;
		} else if (armor->HasKeywordString("ClothingRing") || armor->HasPartOf(SlotEnum::kRing)) {
			iconType = Texture::icon_image_type::armor_ring;
		}
	} else if (armor->IsHeavyArmor()) {
		if (armor->HasPartOf(SlotEnum::kBody)) {
			iconType = Texture::icon_image_type::armor_heavy_chest;
		} else if (armor->HasPartOf(SlotEnum::kHead) || armor->HasPartOf(SlotEnum::kHair) || armor->HasPartOf(SlotEnum::kCirclet)) {
			iconType = Texture::icon_image_type::armor_heavy_head;
		} else if (armor->HasPartOf(SlotEnum::kFeet) || armor->HasPartOf(SlotEnum::kCalves)) {
			iconType = Texture::icon_image_type::armor_heavy_foot;
		} else if (armor->HasPartOf(SlotEnum::kHands)) {
			iconType = Texture::icon_image_type::armor_heavy_arm;
		} else if (armor->HasPartOf(SlotEnum::kShield)) {
			iconType = Texture::icon_image_type::armor_heavy_shield;
		}
	} else if (armor->IsLightArmor()) {
		if (armor->HasPartOf(SlotEnum::kBody)) {
			iconType = Texture::icon_image_type::armor_light_chest;
		} else if (armor->HasPartOf(SlotEnum::kHead) || armor->HasPartOf(SlotEnum::kHair) || armor->HasPartOf(SlotEnum::kCirclet)) {
			iconType = Texture::icon_image_type::armor_light_head;
		} else if (armor->HasPartOf(SlotEnum::kFeet) || armor->HasPartOf(SlotEnum::kCalves)) {
			iconType = Texture::icon_image_type::armor_light_foot;
		} else if (armor->HasPartOf(SlotEnum::kHands)) {
			iconType = Texture::icon_image_type::armor_light_arm;
		} else if (armor->HasPartOf(SlotEnum::kShield)) {
			iconType = Texture::icon_image_type::armor_light_shield;
		}
	} else if (armor->IsClothing()) {
		if (armor->HasPartOf(SlotEnum::kBody)) {
			iconType = Texture::icon_image_type::armor_clothing_chest;
		} else if (armor->HasPartOf(SlotEnum::kHead) || armor->HasPartOf(SlotEnum::kHair) || armor->HasPartOf(SlotEnum::kCirclet)) {
			iconType = Texture::icon_image_type::armor_clothing_head;
		} else if (armor->HasPartOf(SlotEnum::kFeet) || armor->HasPartOf(SlotEnum::kCalves)) {
			iconType = Texture::icon_image_type::armor_clothing_foot;
		} else if (armor->HasPartOf(SlotEnum::kHands)) {
			iconType = Texture::icon_image_type::armor_clothing_arm;
		}
	}

	_texture = Texture::GetIconImage(iconType, a_armor);
	_stat_texture = Texture::GetIconImage(Texture::icon_image_type::armor_default, nullptr);
	// get description
	RE::BSString descriptionBuf = "";
	armor->GetDescription(descriptionBuf, nullptr);
	this->_description = descriptionBuf.c_str();
}

void WheelItemArmor::ActivateItemSecondary()
{
	toggleEquip();
}

void WheelItemArmor::ActivateItemPrimary()
{
	toggleEquip();
}

void WheelItemArmor::SerializeIntoJsonObj(nlohmann::json& a_json)
{
	a_json["type"] = WheelItemArmor::ITEM_TYPE_STR;
	a_json["formID"] = this->_obj->GetFormID();
	a_json["uniqueID"] = this->GetUniqueID();
}

void WheelItemArmor::toggleEquip()
{
	auto pc = RE::PlayerCharacter::GetSingleton();
	if (!pc) {
		return;
	}
	RE::TESObjectREFR::InventoryItemMap imap = pc->GetInventory();
	if (this->IsActive(imap)) {
		this->unequipArmor();
	} else {
		this->equipArmor();
	}
}

void WheelItemArmor::equipArmor()
{
	auto pc = RE::PlayerCharacter::GetSingleton();
	if (!pc || !pc->Is3DLoaded()) {
		return;
	}
	auto aeMan = RE::ActorEquipManager::GetSingleton();
	if (!aeMan) {
		return;
	}
	RE::TESObjectREFR::InventoryItemMap inv = pc->GetInventory();
	auto itemData = this->GetItemExtraDataAndCount(inv);
	int count = itemData.first;
	RE::ExtraDataList* extraData = itemData.second;
	if (count <= 0) { // nothing to equip
		return;
	}
	auto slot = this->_obj->As<RE::TESObjectARMO>()->GetEquipSlot();
	aeMan->EquipObject(pc, _obj, extraData, 1, slot);
}

void WheelItemArmor::unequipArmor()
{
	auto pc = RE::PlayerCharacter::GetSingleton();
	if (!pc || !pc->Is3DLoaded()) {
		return;
	}
	auto aeMan = RE::ActorEquipManager::GetSingleton();
	if (!aeMan) {
		return;
	}
	aeMan->UnequipObject(pc, this->_obj, nullptr, 1, this->_obj->As<RE::TESObjectARMO>()->GetEquipSlot());
}





bool WheelItemArmor::IsActive(RE::TESObjectREFR::InventoryItemMap& a_inv)
{
	auto pc = RE::PlayerCharacter::GetSingleton();
	if (!a_inv.contains(this->_obj)) {
		return false;
	}
	auto entry = a_inv.find(this->_obj)->second.second.get();
	return entry && entry->IsWorn();
}
bool WheelItemArmor::IsAvailable(RE::TESObjectREFR::InventoryItemMap& a_inv)
{
	auto pc = RE::PlayerCharacter::GetSingleton();

	auto itemData = this->GetItemExtraDataAndCount(a_inv);

	return itemData.first > 0;
}
