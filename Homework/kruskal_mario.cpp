#include <stdio.h>
#include <fstream>
#include <vector>
#include <algorithm>

struct vertix{
    int first;
    int second;
    int weight;
};

struct node {
    int value;
    int explored;
    std::vector<int> connected;
};

int find_node(std::vector<node> nodes, int value);
void is_connected(std::vector<node> *nodes, node *current, int value, int *found);
void print_nodes(std::vector<node> nodes);
void clear_exploration(std::vector<node> *nodes);
int kruskal(std::vector<vertix> list, int nodes, int edges);
std::vector<vertix> my_sort(std::vector<vertix> list);


/// @brief Finds the minimum spanning graph
/// @param argc The number of arguments
/// @param argv The arguments
/// @return The exit code
int main(int argc, char **argv)
{
    std::vector<vertix> list;
    if (argc > 1)
    {
        //Read file
        std::ifstream file(argv[1]);
        int a, b, c, sum, nodes, edges;
        file >> nodes >> edges;
        while (file >> a >> b >> c)
        {
            list.push_back({a, b, c});
            //Print unsorted as reading
            //printf("%d <-> %d with weight %d\n", a, b, c);
        }   
        file.close();
        sum = kruskal(my_sort(list), nodes, edges);
        printf("The sum of the weights is %d\n", sum);
        return 0;
    }
    printf("Usage: ./a.out test.txt\n");
    return 1;
}

/// @brief Finds the position of the value in the vector node, if not found returns -1
/// @param nodes The vector of type node
/// @param value The value to find
/// @return Integer with the position of the value in the vector node, if not found returns -1
int find_node(std::vector<node> nodes, int value)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        if(nodes[i].value == value)
            return i;
    }
    return -1;
}

/// @brief Checks if the value is connected to the current node
/// @param nodes The vector of type node
/// @param current The current node
/// @param value The value to find
/// @param found The pointer to the variable where the result is stored
void is_connected(std::vector<node> *nodes, node *current, int value, int *found)
{
    node *next;

    current->explored = 1;
    if (current->value == value)
    {
        *found = 1;
        return;
    }
    //printf("Checking if %d is connected to %d\n", current->value, value);

    for (int i = 0; i < current->connected.size(); i++)
    {
        next = &nodes->at(find_node(*nodes, current->connected[i]));
        if (next->explored == 0)
        {
            is_connected(nodes, next, value, found);
        }
    }
    
}

/// @brief Prints the nodes
/// @param nodes The vector of type node
void print_nodes(std::vector<node> nodes)
{
    //Print nodes
    for(int i=0; i < nodes.size(); i++)
    {
        printf("%d: ", nodes[i].value);
        for(int j=0; j < nodes[i].connected.size(); j++)
        {
            printf("%d ", nodes[i].connected[j]);
        }
        printf("\n");
    }
}

/// @brief Clears the explored value of the nodes
/// @param nodes The vector of type node
void clear_exploration(std::vector<node> *nodes)
{
    for(int i=0; i < nodes->size(); i++)
    {
        nodes->at(i).explored = 0;
    }
}

/// @brief Kruskal algorithm
/// @param list The vector of type vertix already sorted by weights
/// @param num_nodes The number of nodes
/// @param edges The number of edges
/// @return The sum of the weights of the minimum spanning tree
int kruskal(std::vector<vertix> list, int num_nodes, int edges)
{
    int sum = 0, num_edges = 0, pos1, pos2, added, cycle;
    std::vector<node> nodes;

    for(int i=0; i < list.size(); i++)
    {
        if (num_edges == num_nodes-1)
            break;
        pos1 = find_node(nodes, list[i].first);
        pos2 = find_node(nodes, list[i].second);

        added = 0;
        //Add nodes if not already in vector
        if (pos1 == -1)
        {
            added = 1;
            sum+=list[i].weight;
            num_edges++;
            printf("1. %d <-> %d with weight %d\n", list[i].first, list[i].second, list[i].weight);
            nodes.push_back({list[i].first, 0, std::vector<int>(1, list[i].second)});
        }
        //If not a new vector sees if the left node and right node are connected already
        else
        {
            clear_exploration(&nodes);
            cycle = 0;
            is_connected(&nodes, &nodes[pos1], list[i].second, &cycle);
            if (cycle == 0)
            {
                added = 1;
                sum+=list[i].weight;
                num_edges++;
                printf("2. %d <-> %d with weight %d\n", list[i].first, list[i].second, list[i].weight);
                nodes[pos1].connected.push_back(list[i].second);
                if (pos2 != -1)
                    nodes[pos2].connected.push_back(list[i].first);
            }
        }

        if (pos2 == -1)
        {
            if (!added)
            {
                sum+=list[i].weight;
                num_edges++;
                printf("3. %d <-> %d with weight %d\n", list[i].first, list[i].second, list[i].weight);
                nodes[pos1].connected.push_back(list[i].second);
            }
            nodes.push_back({list[i].second, 0, std::vector<int>(1, list[i].first)});
        }
        else
        {
            clear_exploration(&nodes);
            cycle = 0;
            is_connected(&nodes, &nodes[pos2], list[i].first, &cycle);
            if (cycle == 0)
            {
                if (!added)
                {
                    sum+=list[i].weight;
                    num_edges++;
                    printf("4. %d <-> %d with weight %d\n", list[i].first, list[i].second, list[i].weight);
                    nodes[pos1].connected.push_back(list[i].second);
                }
                nodes[pos2].connected.push_back(list[i].first);
            }
        }
        //print_nodes(nodes);
    }
    //print_nodes(nodes);
    return sum;
}

/// @brief Sorts the vector by weight
/// @param a Comparison value of type vertix
/// @param b Comparison value of type vertix
/// @param list The vector of type vertix
/// @return The sorted vector
/// @note The vector is sorted by weight

std::vector<vertix> my_sort(std::vector<vertix> list)
{
    std::sort(list.begin(), list.end(), [](vertix a, vertix b) {
        return a.weight < b.weight;});
    return list;
}