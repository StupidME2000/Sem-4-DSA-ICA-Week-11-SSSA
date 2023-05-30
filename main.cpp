#include <iostream>
#include <vector>
#include <queue>
#include <limits>

#define INF std::numeric_limits<int>::max()

using namespace std;

// Structure to represent a node in the graph
struct Node {
    int id;
    int distance;

    Node(int id, int distance) : id(id), distance(distance) {}

    // Comparison operator for the priority queue
    bool operator<(const Node& other) const {
        return distance > other.distance;
    }
};

// Dijkstra's algorithm for finding the shortest paths from a source node to all other nodes
vector<int> dijkstra(const vector<vector<int>>& graph, int source) {
    int numNodes = graph.size();
    vector<int> distances(numNodes, INF);
    vector<bool> visited(numNodes, false);

    distances[source] = 0;
    priority_queue<Node> pq;
    pq.push(Node(source, 0));

    while (!pq.empty()) {
        int currentNode = pq.top().id;
        pq.pop();

        if (visited[currentNode]) {
            continue;
        }

        visited[currentNode] = true;

        for (int neighbor = 0; neighbor < numNodes; ++neighbor) {
            if (graph[currentNode][neighbor] != 0) {
                int weight = graph[currentNode][neighbor];
                int newDistance = distances[currentNode] + weight;

                if (newDistance < distances[neighbor]) {
                    distances[neighbor] = newDistance;
                    pq.push(Node(neighbor, newDistance));
                }
            }
        }
    }

    return distances;
}

int main() {
    vector<vector<int>> adjacencyMatrix = {
            {0, 10, 0, 0, 15, 5},
            {10, 0, 0, 30, 0, 0},
            {0, 10, 0, 12, 5, 0},
            {0, 30, 12, 0, 0, 20},
            {15, 0, 5, 0, 0, 0},
            {5, 0, 0, 20, 0, 0}
    };

    int numNodes = adjacencyMatrix.size();

    // Running Dijkstra's algorithm for each source city
    vector<int> averageTimes(numNodes, 0);
    int smallestAverageTime = INF;
    vector<int> smallestCities;

    for (int source = 0; source < numNodes; ++source) {
        vector<int> distances = dijkstra(adjacencyMatrix, source);

        // Calculating the average time taken from the source city to all other cities
        int sum = 0;
        int count = 0;

        for (int city = 0; city < numNodes; ++city) {
            if (city == source) {
                continue;
            }

            if (distances[city] != INF) {
                sum += distances[city];
                count++;
            }

            // Printing the shortest time between source city and each other city
            cout << "Shortest time from City " << source << " to City " << city << ": ";
            if (distances[city] == INF) {
                cout << "No path exists";
            } else {
                cout << distances[city] << " units";
            }
            cout << endl;
        }

        averageTimes[source] = sum / count;

        // Updating the city/cities with the smallest average time
        if (averageTimes[source] < smallestAverageTime) {
            smallestAverageTime = averageTimes[source];
            smallestCities.clear();
            smallestCities.push_back(source);
        } else if (averageTimes[source] == smallestAverageTime) {
            smallestCities.push_back(source);
        }

        cout << endl;
    }

    // Printing the average time taken from each source city to all other cities
    cout << "Average times from each source city to other cities:" << endl;
    for (int source = 0; source < numNodes; ++source) {
        cout << "City " << source << ": " << averageTimes[source] << " units" << endl;
    }
    cout << endl;

    // Printing the city/cities with the smallest average time
    cout << "City/Cities with the smallest average time: ";
    for (int city : smallestCities) {
        cout << city << " ";
    }
    cout << endl;

    return 0;
}
