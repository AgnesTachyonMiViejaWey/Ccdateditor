#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

static void applyStats() {
	auto gsm = GameStatsManager::sharedState();
	int orbs = (int)Mod::get()->getSettingValue<int64_t>("orbs");
	int diamonds = (int)Mod::get()->getSettingValue<int64_t>("diamonds");
	int keys = (int)Mod::get()->getSettingValue<int64_t>("keys");
	int mini = (int)Mod::get()->getSettingValue<int64_t>("minidiamonds");

	gsm->setStat("14", orbs);      // Mana Orbs
	gsm->setStat("22", orbs);      // Total Orbs
	gsm->setStat("13", diamonds);  // Diamantes
	gsm->setStat("21", keys);      // Llaves de demonio
	gsm->setStat("29", mini);      // Mini diamantes
}

class $modify(RSMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		auto menu = CCMenu::create();
		menu->setID("restore-stats-menu"_spr);
		auto spr = ButtonSprite::create("Restore", "goldFont.fnt", "GJ_button_01.png", .8f);
		auto btn = CCMenuItemSpriteExtra::create(
			spr, this, menu_selector(RSMenuLayer::onRestore)
		);
		menu->addChild(btn);
		auto win = CCDirector::get()->getWinSize();
		menu->setPosition({ 60.f, win.height - 25.f });
		this->addChild(menu, 100);
		return true;
	}

	void onRestore(CCObject*) {
		applyStats();
		auto gsm = GameStatsManager::sharedState();
		FLAlertLayer::create(
			"Listo",
			fmt::format(
				"Orbes: <cg>{}</c>\nDiamantes: <cg>{}</c>\nLlaves: <cg>{}</c>\nMini diamantes: <cg>{}</c>\n\nMinimiza el juego para que se guarde.",
				gsm->getStat("14"), gsm->getStat("13"), gsm->getStat("21"), gsm->getStat("29")
			),
			"OK"
		)->show();
	}
};
