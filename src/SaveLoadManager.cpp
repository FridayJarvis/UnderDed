#include "SaveLoadManager.h"
#include <nlohmann/json.hpp>
#include <fstream>

using nlohmann::json;

static json DumpPlayer(Player& p) {
  json jp;

  jp["x"] = p.getPosition().x;
  jp["y"] = p.getPosition().y;
  jp["hp"] = p.getHealth();

  const auto& inv = p.getInventory();
  jp["inventory"] = {
      {"money",   inv.getMoney()},
      {"bullets", inv.getBulletAmount()},
      {"medkits", inv.getAidKitAmount()},
      {"shield",  inv.getShieldCharges()},
  };

  jp["weapon_slot"] = p.getCurrentWeaponSlot();

  return jp;
}

static void LoadPlayer(const json& jp, Player& p) {
  // Позиция + HP
  int px = jp.value("x", 0);
  int py = jp.value("y", 0);
  p.setPosition(px, py);
  p.setHealth(jp.value("hp", 10));

  // Инвентарь
  auto& inv = p.getInventory();
  const auto& ji = jp.contains("inventory") ? jp["inventory"] : json::object();
  inv.setMoney(       ji.value("money",   0));
  inv.setBulletAmount(ji.value("bullets", 0));
  inv.setAidKitAmount(ji.value("medkits", 0));
  inv.setShieldCharges(ji.value("shield", 0));

  p.setCurrentWeaponSlot(jp.value("weapon_slot", 1));
}

static json DumpMap(const std::vector<std::string>& map, const std::string& map_path) {
  json jm;
  jm["path"] = map_path;
  jm["grid"] = map;
  return jm;
}

static void LoadMap(const json& jm, std::vector<std::string>& map, std::string& map_path) {
  map_path = jm.value("path", "assets/UnderDedMap.txt");
  if (jm.contains("grid") && jm["grid"].is_array()) {
    map = jm["grid"].get<std::vector<std::string>>();
  } else {
    map.clear();
  }
}

static json DumpEnemies( std::vector<Enemy>& enemies) {
  json je = json::array();
  for ( auto& e : enemies) {
    je.push_back({
        {"x",   e.getPos().x},
        {"y",   e.getPos().y},
        {"hp",  e.getHealth()},
        {"dmg", e.getDamage()}
    });
  }
  return je;
}

static void LoadEnemies(const json& je, std::vector<Enemy>& enemies) {
  enemies.clear();
  if (!je.is_array()) return;
  for (const auto& e : je) {
    Coord pos{ e.value("x", 0), e.value("y", 0) };
    int hp  = e.value("hp",  2);
    int dmg = e.value("dmg", 1);
    enemies.emplace_back(pos, dmg, hp);
  }
}

bool SaveLoadManager::save(const std::string& path,
                            Player& player,
                            std::vector<std::string>& map,
                            std::vector<Enemy>& enemies,
                            std::string& map_path) {
  json j;
  j["version"] = 1;
  j["player"]  = DumpPlayer(player);
  j["map"]     = DumpMap(map, map_path);
  j["enemies"] = DumpEnemies(enemies);

  std::ofstream out(path);
  if (!out.is_open()) return false;
  out << j.dump(2);
  return true;
}

bool SaveLoadManager::load(const std::string& path,
                           Player& player,
                           std::vector<std::string>& map,
                           std::vector<Enemy>& enemies,
                           std::string& map_path) {
  std::ifstream in(path);
  if (!in.is_open()) return false;

  json j;
  in >> j;

  if (j.contains("player"))  LoadPlayer(j["player"], player);
  if (j.contains("map"))     LoadMap(j["map"], map, map_path);
  if (j.contains("enemies")) LoadEnemies(j["enemies"], enemies);

  return true;
}
