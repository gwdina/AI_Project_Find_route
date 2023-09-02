#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <limits>
#include <string>

using namespace std;

// define the map type
typedef unordered_map<string, vector<pair<string, int>>> Map;

// function to perform BFS on the given map
pair<int, vector<string>> bfs(const Map &adjList, const string &start, const string &end)
{
    // create a queue to store the vertices to be visited
    int infite = 0;
    queue<pair<vector<string>, int>> q;

    // initialize variables to keep track of the least cost and shortest path
    int leastCost = numeric_limits<int>::max();
    vector<vector<string>> shortestPaths;

    vector<vector<string>> allPaths;

    // mark the starting vertex as visited and enqueue it with cost 0
    q.push(make_pair(vector<string>{start}, 0));

    // loop until the queue is empty
    while (!q.empty())
    {
        // dequeue a vertex from the queue
        ++infite;
        vector<string> path = q.front().first;
        int cost = q.front().second;
        string vertex = path.back();
        q.pop();

        string lastNode = path[path.size() - 1];

        // If we have reached the end node, add the current path to the list of all possible paths
        if (lastNode == end)
        {
            allPaths.push_back(path);
        }

        // if we have reached the destination vertex
        // cout << infite << endl;

        if (infite == 99999)
        {
            cout << "distance: "
                 << "infinity" << endl;

            cout << "route:" << endl
                 << "none";
            // cout << "none";
            exit(EXIT_FAILURE);
        }

        if (vertex == end)
        {
            // update the least cost and shortest path
            if (cost < leastCost)
            {
                leastCost = cost;
                shortestPaths = vector<vector<string>>{path};
            }
            else if (cost == leastCost)
            {
                shortestPaths.push_back(path);
            }
            // else if(shortestPaths.size() > 3){
            //     break;
            // }
            break;
        }

        // get the neighbors of the current vertex
        vector<pair<string, int>> neighbors = adjList.at(vertex);

        // loop through each neighbor
        for (pair<string, int> neighbor : neighbors)
        {
            // calculate the cost to reach the neighbor
            int newCost = cost + neighbor.second;

            // enqueue the neighbor with its cost and the path to reach it
            vector<string> newPath = path;
            newPath.push_back(neighbor.first);
            q.push(make_pair(newPath, newCost));
        }
    }

    // return the least cost and shortest path(s)
    return make_pair(leastCost, shortestPaths[0]);
}

// unordered_map<string, vector<pair<string, int>>> Map;

int main(int argc, char* argv[])
{
    // Open the input file
    ifstream inputFile(argv[1]);
    // find_route input1.txt (argv[1]) Munich (argv[2]) Berlin (argv[3])
    //ifstream inputFile("programming_assignment1_input1.txt");
    // ifstream inputFile("map.txt");
    if (!inputFile.is_open())
    {
        cerr << "Error: could not open input file" << endl;
        return 1;
    }

    // Read the number of vertices, number of lines, start vertex, and end vertex from the first line

    // Create an unordered map to store the adjacency list

    // Read in each line of the input file and add edges to the graph
    string vertex1, vertex2;
    int cost;

    Map adjList;

    while (inputFile >> vertex1 >> vertex2 >> cost)
    {
        if (vertex1 == "END")
        {
            break;
        }
        pair<string, int> first_node;
        pair<string, int> second_node;
        first_node.first = vertex1;
        first_node.second = cost;

        second_node.first = vertex2;
        second_node.second = cost;

        adjList[vertex1].push_back(second_node);
        adjList[vertex2].push_back(first_node);
    }

    // for (auto const &pair: adjList) {
    //     vector<GraphNode> neighbor = pair.second;
    //     cout << pair.first << ": ";
    //     for (auto const &node: neighbor){
    //         cout << node.vertex << " ";
    //     }
    //     cout << endl;
    // }

    // Close the input file
    inputFile.close();

    string start = argv[2];
    string end = argv[3];


    // vector<pair<string, int>> some = adjList["Berlin"];
    // for(pair<string, int> joj : some){
    //     if(joj.first == "Magdeburg"){
    //         cout << "Berlin" << " to " << "Magdeburg , " << joj.second;
    //     }
    // }

    if (start == end)
    {
        cout << "distance: " << 0 << " km" << endl;

        cout << "route:" << endl;
        cout << start << " to " << end << ", 0 km";
    }
    else
    {

        pair<int, vector<string>> result = bfs(adjList, start, end);

        // print the least cost and shortest path
        cout << "distance: " << result.first << " km" << endl;

        cout << "route:" << endl;
        int switch_cities = 1;

        vector<pair<string, int>> some;
        string prev = "";

        for (string vertex : result.second)
        {

            //cout << vertex << endl;
            if(prev != "" && prev != vertex){
                cout << prev << " to " << vertex;
                for (pair<string, int> bridge : some)
                {
                    if (bridge.first == vertex)
                    {

                        cout << ", " << bridge.second << " km" << endl;
                        
                        break;
                    }
                }
            }
            prev = vertex;
            some = adjList[prev];
            

            
        }
    }
    return 0;
}