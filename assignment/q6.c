#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float temperature;
    float rainfall;
    float windSpeed;
} Weather;

typedef struct {
    char cropType[50];
    char growthStage[50];
    float expectedYield;
    Weather* weatherForecasts; 
    int numForecasts;
} Crop;

typedef struct {
    char equipmentName[50];
    char operationalStatus[20];
    float fuelLevel;
    char activitySchedule[100];
} Equipment;

typedef struct {
    float soilNutrients;
    float pHLevel;
    float pestActivity;
} Sensor;

typedef struct {
    float latitude;
    float longitude;
    float soilHealth;
    float moistureLevel;
    Crop* crops;           
    Equipment* equipment;  
    Sensor* sensors;  
    int numCrops;
    int numEquipment;
    int numSensors;
} Field;

typedef struct {
    char regionName[50];
    Field* fields;         
    int numFields;
    float yieldPrediction;
    float resourceDistribution;
    char emergencyPlan[200];
} RegionalHub;

void initializeField(Field* field, int numCrops, int numEquipment, int numSensors);
void initializeRegionalHub(RegionalHub* hub, const char* name, int numFields);
void addCrop(Field* field, const char* cropType, const char* growthStage, float yield, int numForecasts);
void addEquipment(Field* field, const char* equipmentName, const char* status, float fuel, const char* schedule);
void addSensor(Field* field, float nutrients, float pH, float pests);
void displayRegionalHub(const RegionalHub* hub);
void freeField(Field* field);
void freeRegionalHub(RegionalHub* hub);

int main() {
    RegionalHub hub;
    initializeRegionalHub(&hub, "Northern Region", 2);

    initializeField(&hub.fields[0], 2, 2, 2);
    addCrop(&hub.fields[0], "Wheat", "Flowering", 1200.5, 3);
    addCrop(&hub.fields[0], "Barley", "Mature", 900.8, 2);
    addEquipment(&hub.fields[0], "Autonomous Tractor", "Active", 80.0, "Daily tilling");
    addSensor(&hub.fields[0], 6.5, 7.0, 0.3);

    initializeField(&hub.fields[1], 1, 1, 1);
    addCrop(&hub.fields[1], "Corn", "Seeding", 1500.3, 2);
    addEquipment(&hub.fields[1], "Irrigation System", "Inactive", 0.0, "Under maintenance");
    addSensor(&hub.fields[1], 7.8, 6.2, 0.1);
    displayRegionalHub(&hub);
    freeRegionalHub(&hub);

    return 0;
}

void initializeField(Field* field, int numCrops, int numEquipment, int numSensors) {
    field->latitude = field->longitude = 0.0;
    field->soilHealth = field->moistureLevel = 0.0;
    field->numCrops = numCrops;
    field->numEquipment = numEquipment;
    field->numSensors = numSensors;
    field->crops = (Crop*)malloc(numCrops * sizeof(Crop));
    field->equipment = (Equipment*)malloc(numEquipment * sizeof(Equipment));
    field->sensors = (Sensor*)malloc(numSensors * sizeof(Sensor));
}

void initializeRegionalHub(RegionalHub* hub, const char* name, int numFields) {
    strcpy(hub->regionName, name);
    hub->numFields = numFields;
    hub->fields = (Field*)malloc(numFields * sizeof(Field));
    hub->yieldPrediction = hub->resourceDistribution = 0.0;
    strcpy(hub->emergencyPlan, "No emergency plan defined.");
}

void addCrop(Field* field, const char* cropType, const char* growthStage, float yield, int numForecasts) {
    static int cropIndex = 0;
    if (cropIndex >= field->numCrops) return;
    Crop* crop = &field->crops[cropIndex++];
    strcpy(crop->cropType, cropType);
    strcpy(crop->growthStage, growthStage);
    crop->expectedYield = yield;
    crop->numForecasts = numForecasts;
    crop->weatherForecasts = (Weather*)malloc(numForecasts * sizeof(Weather));
}

void addEquipment(Field* field, const char* equipmentName, const char* status, float fuel, const char* schedule) {
    static int equipIndex = 0;
    if (equipIndex >= field->numEquipment) return;
    Equipment* equip = &field->equipment[equipIndex++];
    strcpy(equip->equipmentName, equipmentName);
    strcpy(equip->operationalStatus, status);
    equip->fuelLevel = fuel;
    strcpy(equip->activitySchedule, schedule);
}

void addSensor(Field* field, float nutrients, float pH, float pests) {
    static int sensorIndex = 0;
    if (sensorIndex >= field->numSensors) return;
    Sensor* sensor = &field->sensors[sensorIndex++];
    sensor->soilNutrients = nutrients;
    sensor->pHLevel = pH;
    sensor->pestActivity = pests;
}

void displayRegionalHub(const RegionalHub* hub) {
    printf("Regional Hub: %s\n", hub->regionName);
    printf("Yield Prediction: %.2f\n", hub->yieldPrediction);
    printf("Resource Distribution: %.2f\n", hub->resourceDistribution);
    printf("Emergency Plan: %s\n\n", hub->emergencyPlan);
    for (int i = 0; i < hub->numFields; ++i) {
        printf("Field %d:\n", i + 1);
        printf("  Location: (%.2f, %.2f)\n", hub->fields[i].latitude, hub->fields[i].longitude);
        printf("  Soil Health: %.2f, Moisture: %.2f\n", hub->fields[i].soilHealth, hub->fields[i].moistureLevel);
        printf("  Crops:\n");
        for (int j = 0; j < hub->fields[i].numCrops; ++j) {
            printf("    %s (%s), Yield: %.2f\n", hub->fields[i].crops[j].cropType, hub->fields[i].crops[j].growthStage, hub->fields[i].crops[j].expectedYield);
        }
        printf("  Equipment:\n");
        for (int j = 0; j < hub->fields[i].numEquipment; ++j) {
            printf("    %s (%s), Fuel: %.2f\n", hub->fields[i].equipment[j].equipmentName, hub->fields[i].equipment[j].operationalStatus, hub->fields[i].equipment[j].fuelLevel);
        }
        printf("  Sensors:\n");
        for (int j = 0; j < hub->fields[i].numSensors; ++j) {
            printf("    Nutrients: %.2f, pH: %.2f, Pests: %.2f\n", hub->fields[i].sensors[j].soilNutrients, hub->fields[i].sensors[j].pHLevel, hub->fields[i].sensors[j].pestActivity);
        }
        printf("\n");
    }
}

void freeField(Field* field) {
    for (int i = 0; i < field->numCrops; ++i) {
        free(field->crops[i].weatherForecasts);
    }
    free(field->crops);
    free(field->equipment);
    free(field->sensors);
}

void freeRegionalHub(RegionalHub* hub) {
    for (int i = 0; i < hub->numFields; ++i) {
        freeField(&hub->fields[i]);
    }
    free(hub->fields);
}
