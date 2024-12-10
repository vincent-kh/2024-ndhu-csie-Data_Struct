#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

#define MAX_ENTRIES 2  // maximum number of data items each node can hold
#define MAX_NAME_LEN 50 // maximum number of characters for item name

typedef struct 
{
    double minX, minY;
    double maxX, maxY;
} BoundingBox;

typedef struct 
{
    double latitude, longitude;
    char name[MAX_NAME_LEN];
} DataItem;

typedef struct RTreeNode 
{
    int isLeaf;                     // is leaf or not
    int count;                      // number of nodes
    int total;                      // total number of nodes under this node
    BoundingBox mbr;                // minimum bounding rectangle
    struct RTreeNode* children[MAX_ENTRIES + 1];
    DataItem data[MAX_ENTRIES];
} RTreeNode;

typedef struct 
{
    DataItem item;
    double distance;
} SearchResult;

RTreeNode* createNode(int isLeaf) 
{
    RTreeNode* node = (RTreeNode*)malloc(sizeof(RTreeNode));
    node->isLeaf = isLeaf;
    node->count = 0;
    node->total = 0;
    node->mbr.minX = node->mbr.minY = DBL_MAX;
    node->mbr.maxX = node->mbr.maxY = -DBL_MAX;
    for (int i = 0; i < MAX_ENTRIES + 1; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void updateMBR(RTreeNode* node, DataItem item) 
{
    if (item.latitude < node->mbr.minX) node->mbr.minX = item.latitude;
    if (item.latitude > node->mbr.maxX) node->mbr.maxX = item.latitude;
    if (item.longitude < node->mbr.minY) node->mbr.minY = item.longitude;
    if (item.longitude > node->mbr.maxY) node->mbr.maxY = item.longitude;
}

void updateMBRBox(RTreeNode* node, BoundingBox mbr) 
{
    if (mbr.minX < node->mbr.minX) node->mbr.minX = mbr.minX;
    if (mbr.minY < node->mbr.minY) node->mbr.minY = mbr.minY;
    if (mbr.maxX > node->mbr.maxX) node->mbr.maxX = mbr.maxX;
    if (mbr.maxY > node->mbr.maxY) node->mbr.maxY = mbr.maxY;
}

DataItem* nearestDataItems(DataItem it1, DataItem it2, DataItem it3) 
{
    DataItem* nearest = (DataItem*)malloc((MAX_ENTRIES + 1) * sizeof(DataItem));
    float d12 = pow(it1.latitude - it2.latitude, 2) + pow(it1.longitude - it2.longitude, 2);
    float d13 = pow(it1.latitude - it3.latitude, 2) + pow(it1.longitude - it3.longitude, 2);
    float d23 = pow(it2.latitude - it3.latitude, 2) + pow(it2.longitude - it3.longitude, 2);
    if (d12 <= d13 && d12 <= d23) {
        nearest[0] = it1;
        nearest[1] = it2;
        nearest[2] = it3;
    } else if (d13 <= d12 && d13 <= d23) {
        nearest[0] = it1;
        nearest[1] = it3;
        nearest[2] = it2;
    } else {
        nearest[0] = it2;
        nearest[1] = it3;
        nearest[2] = it1;
    }
    return nearest;
}

DataItem center_of_box(BoundingBox box) 
{
    DataItem center;
    center.latitude = (box.minX + box.maxX) / 2;
    center.longitude = (box.minY + box.maxY) / 2;
    return center;
}

float distance(DataItem it1, DataItem it2) 
{
    return sqrt(pow(it1.latitude - it2.latitude, 2) + pow(it1.longitude - it2.longitude, 2));
}

void updateTotal(RTreeNode* node) 
{
    if (node->isLeaf) 
    {
        node->total = node->count;
    } 
    else 
    {
        node->total = 0;
        for (int i = 0; i < node->count; i++) 
        {
            if (node->children[i] != NULL) 
            {
                updateTotal(node->children[i]);
                node->total += node->children[i]->total;
            }
        }
    }
}

int compare_item(const void* a, const void* b) 
{
    DataItem* item1 = (DataItem*)a;
    DataItem* item2 = (DataItem*)b;
    if (item1->latitude < item2->latitude) return 1;
    else if (item1->latitude > item2->latitude) return -1;
    else 
    {
        if (item1->longitude < item2->longitude) return 1;
        else if (item1->longitude > item2->longitude) return -1;
        else return 0;
    }
}

int compare_mbr(const void* a, const void* b) 
{
    RTreeNode* item1 = *(RTreeNode**)a;
    RTreeNode* item2 = *(RTreeNode**)b;
    if (item1->mbr.minX < item2->mbr.minX) return 1;
    else if (item1->mbr.minX > item2->mbr.minX) return -1;
    else 
    {
        if (item1->mbr.minY < item2->mbr.minY) return 1;
        else if (item1->mbr.minY > item2->mbr.minY) return -1;
        else return 0;
    }
}

void sort(RTreeNode* node) 
{
    if (node->isLeaf) 
        qsort(node->data, node->count, sizeof(DataItem), compare_item);
    else 
    {
        qsort(node->children, node->count, sizeof(RTreeNode*), compare_mbr);
        for (int i = 0; i < node->count; i++) 
        {
            if (node->children[i] != NULL)
                sort(node->children[i]);
        }
    }
}

// Insert data
void insert(RTreeNode** node, DataItem item) 
{
    if (*node == NULL) 
    {
        *node = createNode(1);
        (*node)->data[(*node)->count++] = item;
        updateMBR(*node, item);
    } 
    else if ((*node)->isLeaf) 
    {
        if ((*node)->count < MAX_ENTRIES) 
        {
            (*node)->data[(*node)->count++] = item;
            updateMBR(*node, item);
        } 
        else 
        {
            (*node)->isLeaf = 0;
            RTreeNode* new_sub_root = createNode(1);
            DataItem* nearest = nearestDataItems((*node)->data[0], (*node)->data[1], item);

            new_sub_root->data[0] = nearest[0];
            new_sub_root->data[1] = nearest[1];
            new_sub_root->count = 2;
            updateMBR(new_sub_root, nearest[0]);
            updateMBR(new_sub_root, nearest[1]);

            (*node)->children[1] = new_sub_root;
            (*node)->children[0] = createNode(1);
            (*node)->children[0]->data[0] = nearest[2];
            (*node)->children[0]->count = 1;
            updateMBR((*node)->children[0], nearest[2]);
            updateMBRBox(*node, new_sub_root->mbr);
            updateMBRBox(*node, (*node)->children[0]->mbr);
            (*node)->count = 2;

            free(nearest);
        }
    } 
    else 
    {
        if ((*node)->count == 0) 
        {
            // No children yet, create a new leaf node
            RTreeNode* new_leaf = createNode(1);
            new_leaf->data[new_leaf->count++] = item;
            updateMBR(new_leaf, item);
            (*node)->children[0] = new_leaf;
            (*node)->count = 1;
            updateMBRBox(*node, new_leaf->mbr);
        } 
        else if ((*node)->count == 1) 
        {
            insert(&(*node)->children[0], item);
        } 
        else 
        {
            DataItem center0 = center_of_box((*node)->children[0]->mbr);
            DataItem center1 = center_of_box((*node)->children[1]->mbr);

            float d0 = distance(center0, item);
            float d1 = distance(center1, item);

            if (d0 < d1) {
                insert(&(*node)->children[0], item);
            } else {
                insert(&(*node)->children[1], item);
            }
        }
    }
    updateTotal(*node);
    sort(*node);
}

DataItem* all_item_under_node(RTreeNode* node) 
{
    if (node->total == 0) {return NULL;}
    DataItem* all_item = (DataItem*)malloc(node->total * sizeof(DataItem));
    int index = 0;
    if (node->isLeaf) 
    {
        for (int i = 0; i < node->count; i++) 
            all_item[index++] = node->data[i];
    } 
    else 
    {
        for (int i = 0; i < node->count; i++) 
        {
            if (node->children[i] != NULL) 
            {
                DataItem* temp = all_item_under_node(node->children[i]);
                if (temp != NULL) 
                {
                    for (int j = 0; j < node->children[i]->total; j++) 
                    {
                        all_item[index++] = temp[j];
                    }
                    free(temp);
                }
            }
        }
    }
    return all_item;
}

int compare_with_dis(const void* a, const void* b) 
{
    SearchResult* item1 = (SearchResult*)a;
    SearchResult* item2 = (SearchResult*)b;
    if (item1->distance < item2->distance) return -1;
    else if (item1->distance > item2->distance) return 1;
    else return 0;
}

// Search data
SearchResult* search(RTreeNode* node, double latitude, double longitude, int* num_results) 
{
    DataItem item;
    item.latitude = latitude;
    item.longitude = longitude;
    RTreeNode* current = node;

    // Traverse the tree to find the leaf node
    while (!current->isLeaf) 
    {
        if (current->count == 0) 
        {
            // No children to traverse
            break;
        } else if (current->count == 1) 
        
        {
            current = current->children[0];
        } 
        else 
        {
            DataItem center0 = center_of_box(current->children[0]->mbr);
            DataItem center1 = center_of_box(current->children[1]->mbr);

            float d0 = distance(center0, item);
            float d1 = distance(center1, item);

            if (d0 < d1 && current->children[0]->total > 2) 
            {
                current = current->children[0];
            } else if (d0 > d1 && current->children[1]->total > 2) 
            {
                current = current->children[1];
            } 
            else 
            {
                break;
            }
        }
    }

    if (current->total == 0) 
    {
        *num_results = 0;
        return NULL;
    }

    DataItem* all_item = all_item_under_node(current);
    SearchResult* mid_results = (SearchResult*)malloc(current->total * sizeof(SearchResult));
    for (int i = 0; i < current->total; i++) 
    {
        mid_results[i].item = all_item[i];
        mid_results[i].distance = distance(item, all_item[i]);
    }
    free(all_item);
    qsort(mid_results, current->total, sizeof(SearchResult), compare_with_dis);

    int result_count = current->total < 2 ? current->total : 2;
    *num_results = result_count;
    SearchResult* results = (SearchResult*)malloc(result_count * sizeof(SearchResult));
    for (int i = 0; i < result_count; i++)      results[i] = mid_results[i];
    free(mid_results);
    return results;
}

void printTree(RTreeNode* root, int depth) 
{
    for (int i = 0; i < depth; i++) printf("  ");
    printf("Node (count=%d, isLeaf=%d):\n", root->count, root->isLeaf);
    for (int i = 0; i < root->count; i++) 
    {
        if (root->isLeaf) 
        {
            for (int j = 0; j < depth + 1; j++) printf("  ");
            printf("Data: %s (%.2f, %.2f)\n", root->data[i].name, root->data[i].latitude, root->data[i].longitude);
        } 
        else 
        {
            if (root->children[i] != NULL) 
            {
                printTree(root->children[i], depth + 1);
            }
        }
    }
}

int main() {
    RTreeNode* root = createNode(1);
    DataItem item;
    double latitude, longitude;
    SearchResult* results;
    int num_results;

    char command[50];

    while (1) {
        if (scanf("%s", command) != 1) {
            fprintf(stderr, "Error reading command.\n");
            break;
        }
        if (strcmp("insert", command) == 0) {
            if (scanf("%lf%lf%s", &item.latitude, &item.longitude, item.name) != 3) {
                fprintf(stderr, "Error reading insert parameters.\n");
                continue;
            }
            insert(&root, item);
        } else if (strcmp("print", command) == 0) {
            printTree(root, 0);
        } else if (strcmp("exit", command) == 0) {
            break;
        } else if (strcmp("search", command) == 0) {
            if (scanf("%lf%lf", &latitude, &longitude) != 2) {
                fprintf(stderr, "Error reading search parameters.\n");
                continue;
            }
            results = search(root, latitude, longitude, &num_results);
            if (num_results == 0) {
                printf("No results found.\n");
            } else {
                for (int i = 0; i < num_results; i++) {
                    printf("%s (%.2f, %.2f) - Distance: %.2f\n",
                           results[i].item.name,
                           results[i].item.latitude,
                           results[i].item.longitude,
                           results[i].distance);
                }
                free(results);
            }
        } else {
            printf("Unknown command.\n");
        }
    }
    return 0;
}
