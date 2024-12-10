#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char title[100];
    float rating;
    int runtime;
    char encodingFormats[50];
} ContentMetadata;

typedef struct {
    float resolutionPreference;
    int playbackHistory[10];
    float bandwidthUsage;
} DevicePreferences;

typedef struct {
    double* engagementRow;
    DevicePreferences** devices;
    int numDevices;
} UserProfile;

void initializeEngagementMatrix(double*** matrix, int numUsers, int numCategories) {
    *matrix = (double**)malloc(numUsers * sizeof(double*));
    for (int i = 0; i < numUsers; i++) {
        (*matrix)[i] = (double*)calloc(numCategories, sizeof(double));
    }
}

void initializeDeviceMatrix(DevicePreferences**** deviceMatrix, int numUsers, int maxDevices) {
    *deviceMatrix = (DevicePreferences***)malloc(numUsers * sizeof(DevicePreferences**));
    for (int i = 0; i < numUsers; i++) {
        (*deviceMatrix)[i] = (DevicePreferences**)malloc(maxDevices * sizeof(DevicePreferences*));
        for (int j = 0; j < maxDevices; j++) {
            (*deviceMatrix)[i][j] = (DevicePreferences*)malloc(sizeof(DevicePreferences));
            (*deviceMatrix)[i][j]->resolutionPreference = 1080;
            (*deviceMatrix)[i][j]->bandwidthUsage = 0;
            memset((*deviceMatrix)[i][j]->playbackHistory, 0, 10 * sizeof(int));
        }
    }
}

void initializeContentMetadata(ContentMetadata*** contentMatrix, int numCategories, int numContents) {
    *contentMatrix = (ContentMetadata**)malloc(numCategories * sizeof(ContentMetadata*));
    for (int i = 0; i < numCategories; i++) {
        (*contentMatrix)[i] = (ContentMetadata*)malloc(numContents * sizeof(ContentMetadata));
        for (int j = 0; j < numContents; j++) {
            snprintf((*contentMatrix)[i][j].title, 100, "Content_%d_%d", i + 1, j + 1);
            (*contentMatrix)[i][j].rating = (rand() % 50) / 10.0 + 5.0;
            (*contentMatrix)[i][j].runtime = (rand() % 60) + 90;
            snprintf((*contentMatrix)[i][j].encodingFormats, 50, "HD, 4K");
        }
    }
}

void updateEngagementScore(double** matrix, int userIndex, int categoryIndex, double score) {
    matrix[userIndex][categoryIndex] += score;
}

void displayEngagementMatrix(double** matrix, int numUsers, int numCategories) {
    for (int i = 0; i < numUsers; i++) {
        printf("User %d: ", i + 1);
        for (int j = 0; j < numCategories; j++) {
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void freeEngagementMatrix(double** matrix, int numUsers) {
    for (int i = 0; i < numUsers; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void freeDeviceMatrix(DevicePreferences*** deviceMatrix, int numUsers, int maxDevices) {
    for (int i = 0; i < numUsers; i++) {
        for (int j = 0; j < maxDevices; j++) {
            free(deviceMatrix[i][j]);
        }
        free(deviceMatrix[i]);
    }
    free(deviceMatrix);
}

void freeContentMetadata(ContentMetadata** contentMatrix, int numCategories, int numContents) {
    for (int i = 0; i < numCategories; i++) {
        free(contentMatrix[i]);
    }
    free(contentMatrix);
}

int main() {
    int numUsers = 3, numCategories = 5, maxDevices = 2, numContents = 4;

    double** engagementMatrix;
    initializeEngagementMatrix(&engagementMatrix, numUsers, numCategories);

    DevicePreferences*** deviceMatrix;
    initializeDeviceMatrix(&deviceMatrix, numUsers, maxDevices);

    ContentMetadata** contentMatrix;
    initializeContentMetadata(&contentMatrix, numCategories, numContents);

    updateEngagementScore(engagementMatrix, 0, 1, 5.0);
    updateEngagementScore(engagementMatrix, 1, 3, 3.5);

    displayEngagementMatrix(engagementMatrix, numUsers, numCategories);

    freeEngagementMatrix(engagementMatrix, numUsers);
    freeDeviceMatrix(deviceMatrix, numUsers, maxDevices);
    freeContentMetadata(contentMatrix, numCategories, numContents);

    return 0;
}
