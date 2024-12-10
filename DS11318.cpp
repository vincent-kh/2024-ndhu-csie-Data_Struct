// C++
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iomanip>

#define MAX_NAME_LEN 50
#define MAX_ENTRIES 2

using namespace std;

// 定義結構體
typedef struct {
    double minX, minY;
    double maxX, maxY;
} BoundingBox;

typedef struct {
    double latitude, longitude;
    char name[MAX_NAME_LEN];
} DataItem;

typedef struct RTreeNode {
    int isLeaf;                     // 是否為葉節點
    int count;                      // 節點中的項目數
    BoundingBox mbr;                // 最小包含矩形
    struct RTreeNode* children[MAX_ENTRIES + 1];
    DataItem data[MAX_ENTRIES];     // 儲存資料
} RTreeNode;

typedef struct {
    DataItem item;
    double distance;
} SearchResult;

// 創建節點
RTreeNode* createNode(int isLeaf) {
    RTreeNode* node = (RTreeNode*)malloc(sizeof(RTreeNode));
    node->isLeaf = isLeaf;
    node->count = 0;
    node->mbr.minX = node->mbr.minY = 1e9;
    node->mbr.maxX = node->mbr.maxY = -1e9;
    for (int i = 0; i < MAX_ENTRIES + 1; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// 更新 MBR
void updateMBR(RTreeNode* node, BoundingBox mbr) {
    if (mbr.minX < node->mbr.minX) node->mbr.minX = mbr.minX;
    if (mbr.minY < node->mbr.minY) node->mbr.minY = mbr.minY;
    if (mbr.maxX > node->mbr.maxX) node->mbr.maxX = mbr.maxX;
    if (mbr.maxY > node->mbr.maxY) node->mbr.maxY = mbr.maxY;
}

// 插入資料項
void insertDataItem(RTreeNode*& node, DataItem item) {
    if (node == NULL) {
        node = createNode(1);
    }

    if (node->isLeaf) {
        if (node->count < MAX_ENTRIES) {
            // 插入資料項到葉節點
            node->data[node->count++] = item;

            // 更新 MBR
            BoundingBox mbr;
            mbr.minX = mbr.maxX = item.latitude;
            mbr.minY = mbr.maxY = item.longitude;
            updateMBR(node, mbr);
        } else {
            // 分裂葉節點並分配項目
            RTreeNode* newNode = createNode(node->isLeaf);
            int mid = node->count / 2;
            newNode->count = node->count - mid;
            for (int i = mid; i < node->count; i++) {
                newNode->data[i - mid] = node->data[i];
                // 更新 MBR for newNode
                BoundingBox mbr;
                mbr.minX = mbr.maxX = newNode->data[i - mid].latitude;
                mbr.minY = mbr.maxY = newNode->data[i - mid].longitude;
                updateMBR(newNode, mbr);
            }
            node->count = mid;
            
            // Create new parent and assign children
            RTreeNode* parent = createNode(0);
            parent->children[parent->count++] = node;
            parent->children[parent->count++] = newNode;
            updateMBR(parent, node->mbr);
            updateMBR(parent, newNode->mbr);
        }
    } else {
        // 選擇子節點
        int index = 0;
        double minAreaIncrease = 1e9;
        for (int i = 0; i < node->count; i++) {
            BoundingBox mbr = node->children[i]->mbr;
            double areaOriginal = (mbr.maxX - mbr.minX) * (mbr.maxY - mbr.minY);

            // 計算新 MBR
            BoundingBox newMBR = mbr;
            if (item.latitude < newMBR.minX) newMBR.minX = item.latitude;
            if (item.latitude > newMBR.maxX) newMBR.maxX = item.latitude;
            if (item.longitude < newMBR.minY) newMBR.minY = item.longitude;
            if (item.longitude > newMBR.maxY) newMBR.maxY = item.longitude;

            double areaNew = (newMBR.maxX - newMBR.minX) * (newMBR.maxY - newMBR.minY);
            double areaIncrease = areaNew - areaOriginal;

            if (areaIncrease < minAreaIncrease) {
                minAreaIncrease = areaIncrease;
                index = i;
            }
        }

        insertDataItem(node->children[index], item);
        // 更新 MBR
        updateMBR(node, node->children[index]->mbr);

        // 分裂子節點（簡化處理）
        if (node->children[index]->count > MAX_ENTRIES) {
            RTreeNode* newChild = createNode(node->children[index]->isLeaf);
            node->children[node->count++] = newChild;
        }
    }
}

// 打印 R 樹
void printRTree(RTreeNode* node, int depth = 0) {
    if (node == NULL) return;

    for (int i = 0; i < depth; i++)
        cout << "  ";
    cout << "Node (count=" << node->count << ", isLeaf=" << node->isLeaf << "):" << endl;

    if (node->isLeaf) {
        for (int i = 0; i < node->count; i++) {
            for (int j = 0; j <= depth; j++)
                cout << "  ";
            cout << "Data: " << node->data[i].name << " ("
                 << fixed << setprecision(2) << node->data[i].latitude << ", "
                 << node->data[i].longitude << ")" << endl;
        }
    } else {
        for (int i = 0; i < node->count; i++) {
            printRTree(node->children[i], depth + 1);
        }
    }
}

// 計算兩點之間的距離
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    return sqrt((lat1 - lat2)*(lat1 - lat2) + (lon1 - lon2)*(lon1 - lon2));
}

// 搜尋最近的資料項
void searchRTree(RTreeNode* node, double lat, double lon, vector<SearchResult>& results) {
    if (node == NULL) return;

    if (node->isLeaf) {
        for (int i = 0; i < node->count; i++) {
            double distance = calculateDistance(lat, lon, node->data[i].latitude, node->data[i].longitude);
            SearchResult result;
            result.item = node->data[i];
            result.distance = distance;
            results.push_back(result);
        }
    } else {
        for (int i = 0; i < node->count; i++) {
            searchRTree(node->children[i], lat, lon, results);
        }
    }
}

int main() {
    RTreeNode* root = NULL;

    string command;
    while (cin >> command) {
        if (command == "insert") {
            double lat, lon;
            string name;
            cin >> lat >> lon >> name;
            DataItem item;
            item.latitude = lat;
            item.longitude = lon;
            strncpy(item.name, name.c_str(), MAX_NAME_LEN - 1);
            item.name[MAX_NAME_LEN - 1] = '\0';
            insertDataItem(root, item);
        } else if (command == "print") {
            printRTree(root);
        } else if (command == "search") {
            double lat, lon;
            cin >> lat >> lon;
            vector<SearchResult> results;
            searchRTree(root, lat, lon, results);
            // 排序結果
            sort(results.begin(), results.end(), [](const SearchResult& a, const SearchResult& b) {
                return a.distance < b.distance;
            });
            // 輸出結果（距離在 1.5 內的資料項）
            for (const auto& res : results) {
                if (res.distance <= 1.5) {
                    cout << res.item.name << " (" << fixed << setprecision(2) << res.item.latitude
                         << ", " << res.item.longitude << ") - Distance: "
                         << fixed << setprecision(2) << res.distance << endl;
                }
            }
        } else if (command == "exit") {
            break;
        }
    }

    return 0;
}