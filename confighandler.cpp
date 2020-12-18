#include "confighandler.h"
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <map>
#include <QFile>
#include <fstream>
#include <vector>
#include "proxyhandler.h"
#include <QQmlEngine>
#include <QQmlComponent>

using namespace std;

ConfigHandler::ConfigHandler(QObject *parent) : QObject(parent){
}


ConfigHandler::~ConfigHandler() {
}

const string FILE_PATH = "./config.yaml";
const string TMEMP_PATH = "./temp";
map<string, YAML::Node> config_map;
QJsonObject local_config;

void sync() {
    YAML::Node config;

    config["socks5Listen"] = local_config["socks5Listen"].toString().toStdString();
    config["httpListen"] = local_config["httpListen"].toString().toStdString();
    vector<YAML::Node>list;

    for (auto entry : config_map) {
        list.push_back(entry.second);
    }
    config["remote"] = list;

    ofstream out(FILE_PATH);
    out << config;
}

void load() {
    YAML::Node config = YAML::LoadFile(FILE_PATH);
    local_config["socks5Listen"] = config["socks5Listen"].as<string>().c_str();
    local_config["httpListen"] = config["httpListen"].as<string>().c_str();

    auto remote = config["remote"].as<vector<YAML::Node>>();

    for (auto v : remote) {
        config_map[v["name"].as<string>()] = v;
    }
}

void check_File() {
    QFile file(QString::fromStdString(FILE_PATH));

    if (!file.exists()) {
        sync();
    }
}

QJsonArray ConfigHandler::selectList() {
    QJsonArray json;

    for (auto entry: config_map) {
        auto node = entry.second;
        QJsonObject obj;

        obj["name"] = node["name"].as<string>().c_str();
        obj["protocol"] = node["protocol"].as<string>().c_str();
        obj["host"] = node["host"].as<string>().c_str();
        json.append(obj);
    }
    return json;
}

QJsonObject ConfigHandler::select(QString name) {
    auto node = config_map[name.toStdString()];
    QJsonObject json;

    for (auto entry : node) {
        auto k = entry.first;
        auto v = entry.second;

        json[k.as<string>().c_str()] = v.as<string>().c_str();
    }
    return json;
}

void ConfigHandler::remove(QString name) {
    config_map.erase(name.toStdString());
    sync();
}

void ConfigHandler::update(QJsonObject json) {
    YAML::Node node;
    QJsonObject::Iterator it;

    for(it=json.begin();it!=json.end();it++) {
        node[it.key().toStdString()] = it.value().toString().toStdString();
    }

    auto name = json["name"].toString().toStdString();
    config_map[name] = node;

    sync();
}

QJsonObject ConfigHandler::getLocalConfig() {
    return local_config;
}

void ConfigHandler::updateLocalConfig(QJsonObject config) {
    local_config = config;
    sync();
}

QJsonArray ConfigHandler::init(){
    check_File();
    load();
    return selectList();
}

void ConfigHandler::writeTemp(QVector<QString> nameList) {
    YAML::Node config;

    config["socks5Listen"] = local_config["socks5Listen"].toString().toStdString();
    config["httpListen"] = local_config["httpListen"].toString().toStdString();
    vector<YAML::Node>list;

    for (auto name : nameList) {
        auto node = config_map[name.toStdString().c_str()];
        list.push_back(node);
    }
    config["remote"] = list;

    ofstream out(TMEMP_PATH);
    out << config;
}
