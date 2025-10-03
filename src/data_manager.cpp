/**
 * @file data_manager.cpp
 * @brief Implementación del gestor de datos de aplicaciones.
 */

#include "data_manager.h"
#include "cJSON.h"
#include <fstream>
#include <sstream>
#include <iostream>

// --- VARIABLES GLOBALES AL ARCHIVO ---
static std::vector<AppData> app_list;
static const std::string CATALOG_FILENAME = "catalog.json";

// --- IMPLEMENTACIÓN DE FUNCIONES ---

bool data_manager_load_data() {
    app_list.clear();

    std::ifstream file(CATALOG_FILENAME);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir " << CATALOG_FILENAME << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string json_string = buffer.str();
    file.close();

    cJSON *root = cJSON_Parse(json_string.c_str());
    if (root == NULL) {
        std::cerr << "Error: No se pudo analizar el JSON de " << CATALOG_FILENAME << std::endl;
        return false;
    }

    cJSON *items = cJSON_GetObjectItemCaseSensitive(root, "items");
    cJSON *item = NULL;

    cJSON_ArrayForEach(item, items) {
        AppData app;
        cJSON *name = cJSON_GetObjectItemCaseSensitive(item, "name");
        cJSON *desc = cJSON_GetObjectItemCaseSensitive(item, "description");
        cJSON *version = cJSON_GetObjectItemCaseSensitive(item, "version");
        cJSON *author = cJSON_GetObjectItemCaseSensitive(item, "author");
        cJSON *url = cJSON_GetObjectItemCaseSensitive(item, "url");
        cJSON *icon = cJSON_GetObjectItemCaseSensitive(item, "icon");
        cJSON *size_mb = cJSON_GetObjectItemCaseSensitive(item, "size_mb");

        if (cJSON_IsString(name)) app.name = name->valuestring;
        if (cJSON_IsString(desc)) app.description = desc->valuestring;
        if (cJSON_IsString(version)) app.version = version->valuestring;
        if (cJSON_IsString(author)) app.author = author->valuestring;
        if (cJSON_IsString(url)) app.url = url->valuestring;
        if (cJSON_IsString(icon)) app.icon = icon->valuestring;
        if (cJSON_IsNumber(size_mb)) app.size_mb = size_mb->valuedouble;

        app_list.push_back(app);
    }

    cJSON_Delete(root);
    return true;
}

const std::vector<AppData>& data_manager_get_apps() {
    return app_list;
}

void data_manager_delete_app(int index) {
    if (index >= 0 && index < app_list.size()) {
        app_list.erase(app_list.begin() + index);
    }
}

bool data_manager_save_data() {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "repository_name", cJSON_CreateString("Play OS Store - Catálogo Principal"));
    cJSON_AddItemToObject(root, "version", cJSON_CreateString("1.0"));

    cJSON *items = cJSON_CreateArray();
    cJSON_AddItemToObject(root, "items", items);

    for (const auto& app : app_list) {
        cJSON *item = cJSON_CreateObject();
        cJSON_AddItemToArray(items, item);
        cJSON_AddItemToObject(item, "name", cJSON_CreateString(app.name.c_str()));
        cJSON_AddItemToObject(item, "description", cJSON_CreateString(app.description.c_str()));
        cJSON_AddItemToObject(item, "version", cJSON_CreateString(app.version.c_str()));
        cJSON_AddItemToObject(item, "author", cJSON_CreateString(app.author.c_str()));
        cJSON_AddItemToObject(item, "url", cJSON_CreateString(app.url.c_str()));
        cJSON_AddItemToObject(item, "icon", cJSON_CreateString(app.icon.c_str()));
        cJSON_AddItemToObject(item, "size_mb", cJSON_CreateNumber(app.size_mb));
    }

    char *json_string = cJSON_Print(root);
    std::ofstream file(CATALOG_FILENAME);
    if (!file.is_open()) {
        cJSON_Delete(root);
        free(json_string);
        return false;
    }

    file << json_string;
    file.close();

    cJSON_Delete(root);
    free(json_string);
    return true;
}