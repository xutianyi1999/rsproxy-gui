#include "qmlcppbridge.h"
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <map>
#include <QFile>
#include <fstream>
#include <vector>
#include <QThread>
#include "proxyhandler.h"

using namespace std;

QThread workerThread;
ProxyHandler *proxyHandler;

QmlCppBridge::QmlCppBridge(QObject *parent) : QObject(parent){
    proxyHandler = new ProxyHandler();
}

QmlCppBridge::~QmlCppBridge() {
    workerThread.quit();
    workerThread.wait();
}

const string file_path = "./config.yaml";
map<string, YAML::Node> config_map;
string bind_host;

void sync() {
    YAML::Node config;

    config["host"] = bind_host;
    vector<YAML::Node>list;

    for (auto entry : config_map) {
        list.push_back(entry.second);
    }
    config["remote"] = list;

    ofstream out(file_path);
    out << config;
}

void load() {
    YAML::Node config = YAML::LoadFile(file_path);
    bind_host.append(config["host"].as<string>());

    auto remote = config["remote"].as<vector<YAML::Node>>();

    for (auto v : remote) {
        config_map[v["name"].as<string>()] = v;
    }
}

void check_File() {
    QFile file(QString::fromStdString(file_path));

    if (!file.exists()) {
        sync();
    }
}

QJsonArray QmlCppBridge::selectList() {
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

QJsonObject QmlCppBridge::select(QString name) {
    auto node = config_map[name.toStdString()];
    QJsonObject json;

    for (auto entry : node) {
        auto k = entry.first;
        auto v = entry.second;

       json[k.as<string>().c_str()] = v.as<string>().c_str();
    }
    return json;
}

void QmlCppBridge::remove(QString name) {
    config_map.erase(name.toStdString());
    sync();
}

void QmlCppBridge::update(QJsonObject json) {
    YAML::Node node;
    QJsonObject::Iterator it;

    for(it=json.begin();it!=json.end();it++) {
        node[it.key().toStdString()] = it.value().toString().toStdString();
    }

    auto name = json["name"].toString().toStdString();
    config_map[name] = node;

    sync();
}

QString QmlCppBridge::getHost() {
    return QString::fromStdString(bind_host);
}

void QmlCppBridge::updateHost(QString host) {
    bind_host.clear();
    bind_host.append(host.toStdString());
    sync();
}

QJsonArray QmlCppBridge::init(){
    check_File();
    load();
    return selectList();
}

void QmlCppBridge::proxyStart() {
    proxyHandler -> moveToThread(&workerThread);
    connect(&workerThread, &QThread::started, proxyHandler, &ProxyHandler::execute);
    workerThread.start();
    qDebug() << "thread start";
}
