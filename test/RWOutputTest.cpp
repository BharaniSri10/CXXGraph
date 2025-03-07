#include "gtest/gtest.h"
#include <fstream>
#include "CXXGraph.hpp"

inline bool exists_test(const std::string &name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

static std::map<unsigned long, CXXGRAPH::Node<int> *> generateRandomNodes(unsigned long numberOfNodes, int MaxValue)
{
    std::map<unsigned long, CXXGRAPH::Node<int> *> nodes;
    srand((unsigned)time(NULL));
    int randomNumber;
    for (auto index = 0; index < numberOfNodes; index++)
    {
        randomNumber = (rand() % MaxValue) + 1;
        CXXGRAPH::Node<int> *newNode = new CXXGRAPH::Node<int>(index, randomNumber);
        nodes[index] = newNode;
    }
    return nodes;
}

static std::map<unsigned long, CXXGRAPH::Edge<int> *> generateRandomEdges(unsigned long numberOfEdges, std::map<unsigned long, CXXGRAPH::Node<int> *> nodes)
{
    std::map<unsigned long, CXXGRAPH::Edge<int> *> edges;
    srand((unsigned)time(NULL));
    int randomNumber1;
    int randomNumber2;
    auto MaxValue = nodes.size();
    for (auto index = 0; index < numberOfEdges; index++)
    {
        randomNumber1 = (rand() % MaxValue);
        randomNumber2 = (rand() % MaxValue);
        CXXGRAPH::Edge<int> *newEdge = new CXXGRAPH::Edge<int>(index, *(nodes.at(randomNumber1)), *(nodes.at(randomNumber2)));
        edges[index] = newEdge;
    }
    return edges;
}

static auto nodes = generateRandomNodes(10000, 2);
static auto edges = generateRandomEdges(10000, nodes);

//************* CSV ***************//

TEST(RWOutputTest, test_1)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile();
    ASSERT_EQ(res, 0);
    ASSERT_TRUE(exists_test("graph.csv"));
    ASSERT_FALSE(exists_test("graph_NodeFeat.csv"));
    ASSERT_FALSE(exists_test("graph_EdgeWeight.csv"));
}

TEST(RWOutputTest, test_2)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 4);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_CSV);
    ASSERT_EQ(res, 0);
    ASSERT_TRUE(exists_test("graph.csv"));
    ASSERT_FALSE(exists_test("graph_NodeFeat.csv"));
    ASSERT_FALSE(exists_test("graph_EdgeWeight.csv"));
}

TEST(RWOutputTest, test_3)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_CSV, ".", "test_3");
    ASSERT_EQ(res, 0);
    ASSERT_TRUE(exists_test("test_3.csv"));
    ASSERT_FALSE(exists_test("test_3_NodeFeat.csv"));
    ASSERT_FALSE(exists_test("test_3_EdgeWeight.csv"));
}

TEST(RWOutputTest, test_4)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::OUT_1, "test_4");
    ASSERT_EQ(res, -1);
    ASSERT_FALSE(exists_test("test_4.csv"));
    ASSERT_FALSE(exists_test("test_4_NodeFeat.csv"));
    ASSERT_FALSE(exists_test("test_4_EdgeWeight.csv"));
}

TEST(RWOutputTest, test_5)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_CSV, ".", "test_5", false, true, true);
    ASSERT_EQ(res, 0);
    ASSERT_TRUE(exists_test("test_5.csv"));
    ASSERT_TRUE(exists_test("test_5_NodeFeat.csv"));
    ASSERT_TRUE(exists_test("test_5_EdgeWeight.csv"));
}

TEST(RWOutputTest, test_6)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_CSV, ".", "test_6", false, false, true);
    ASSERT_EQ(res, 0);
    ASSERT_TRUE(exists_test("test_6.csv"));
    ASSERT_FALSE(exists_test("test_6_NodeFeat.csv"));
    ASSERT_TRUE(exists_test("test_6_EdgeWeight.csv"));
}

TEST(RWOutputTest, test_7)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_CSV, ".", "test_7", false, true, false);
    ASSERT_EQ(res, 0);
    ASSERT_TRUE(exists_test("test_7.csv"));
    ASSERT_TRUE(exists_test("test_7_NodeFeat.csv"));
    ASSERT_FALSE(exists_test("test_7_EdgeWeight.csv"));
}

TEST(RWOutputTest, test_8)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_CSV, ".", "test_8");
    ASSERT_EQ(res, 0);
    ASSERT_TRUE(exists_test("test_8.csv"));
    ASSERT_FALSE(exists_test("test_8_NodeFeat.csv"));
    ASSERT_FALSE(exists_test("test_8_EdgeWeight.csv"));

    CXXGRAPH::Graph<int> readGraph;
    readGraph.readFromFile(CXXGRAPH::InputOutputFormat::STANDARD_CSV, ".", "test_8");
    auto readNode = readGraph.getNodeSet();
    auto readEdge = readGraph.getEdgeSet();
    ASSERT_EQ(readEdge.size(), 3);
    ASSERT_EQ(readNode.size(), 3);

    for (auto readEdgeIt = readEdge.begin(); readEdgeIt != readEdge.end(); ++readEdgeIt)
    {
        if ((*readEdgeIt)->getId() == 1)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && (*readEdgeIt)->isDirected().value());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node1.getId());
            //ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node1.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node2.getId());
            //ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node2.getData());
        }
        else if ((*readEdgeIt)->getId() == 2)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && (*readEdgeIt)->isDirected().value());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node2.getId());
            //ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node2.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node3.getId());
            //ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node3.getData());
        }
        else if ((*readEdgeIt)->getId() == 3)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && !(*readEdgeIt)->isDirected().value());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node1.getId());
            //ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node1.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node3.getId());
            //ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node3.getData());
        }
        else
        {
            ASSERT_TRUE(false); // forced Error
        }
    }
}

TEST(RWOutputTest, test_9)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_CSV, ".", "test_9", false, true);
    ASSERT_EQ(res, 0);
    ASSERT_TRUE(exists_test("test_9.csv"));
    ASSERT_TRUE(exists_test("test_9_NodeFeat.csv"));
    ASSERT_FALSE(exists_test("test_9_EdgeWeight.csv"));

    CXXGRAPH::Graph<int> readGraph;
    readGraph.readFromFile(CXXGRAPH::InputOutputFormat::STANDARD_CSV, ".", "test_9", false, true);
    auto readNode = readGraph.getNodeSet();
    auto readEdge = readGraph.getEdgeSet();
    ASSERT_EQ(readEdge.size(), 3);
    ASSERT_EQ(readNode.size(), 3);

    for (auto readEdgeIt = readEdge.begin(); readEdgeIt != readEdge.end(); ++readEdgeIt)
    {
        if ((*readEdgeIt)->getId() == 1)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && (*readEdgeIt)->isDirected().value());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node1.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node1.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node2.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node2.getData());
        }
        else if ((*readEdgeIt)->getId() == 2)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && (*readEdgeIt)->isDirected().value());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node2.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node2.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node3.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node3.getData());
        }
        else if ((*readEdgeIt)->getId() == 3)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && !(*readEdgeIt)->isDirected().value());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node1.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node1.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node3.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node3.getData());
        }
        else
        {
            ASSERT_TRUE(false); // forced Error
        }
    }
}

TEST(RWOutputTest, test_10)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_CSV, ".", "test_10", false, true, true);
    ASSERT_EQ(res, 0);
    ASSERT_TRUE(exists_test("test_10.csv"));
    ASSERT_TRUE(exists_test("test_10_NodeFeat.csv"));
    ASSERT_TRUE(exists_test("test_10_EdgeWeight.csv"));

    CXXGRAPH::Graph<int> readGraph;
    readGraph.readFromFile(CXXGRAPH::InputOutputFormat::STANDARD_CSV, ".", "test_10", false, true, true);
    auto readNode = readGraph.getNodeSet();
    auto readEdge = readGraph.getEdgeSet();
    ASSERT_EQ(readEdge.size(), 3);
    ASSERT_EQ(readNode.size(), 3);

    for (auto readEdgeIt = readEdge.begin(); readEdgeIt != readEdge.end(); ++readEdgeIt)
    {
        if ((*readEdgeIt)->getId() == 1)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && (*readEdgeIt)->isDirected().value());
            ASSERT_TRUE((*readEdgeIt)->isWeighted().has_value() && (*readEdgeIt)->isWeighted().value());
            ASSERT_EQ((dynamic_cast<const CXXGRAPH::Weighted *>(*readEdgeIt))->getWeight(), 5);
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node1.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node1.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node2.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node2.getData());
        }
        else if ((*readEdgeIt)->getId() == 2)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && (*readEdgeIt)->isDirected().value());
            ASSERT_TRUE((*readEdgeIt)->isWeighted().has_value() && !(*readEdgeIt)->isWeighted().value());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node2.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node2.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node3.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node3.getData());
        }
        else if ((*readEdgeIt)->getId() == 3)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && !(*readEdgeIt)->isDirected().value());
            ASSERT_TRUE((*readEdgeIt)->isWeighted().has_value() && (*readEdgeIt)->isWeighted().value());
            ASSERT_EQ((dynamic_cast<const CXXGRAPH::Weighted *>(*readEdgeIt))->getWeight(), 6);
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node1.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node1.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node3.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node3.getData());
        }
        else
        {
            ASSERT_TRUE(false); // forced Error
        }
    }
}

//************* TSV ***************//

TEST(RWOutputTest, test_11)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 1);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile();
    ASSERT_EQ(res, 0);
    ASSERT_FALSE(exists_test("graph.tsv"));
    ASSERT_FALSE(exists_test("graph_NodeFeat.tsv"));
    ASSERT_FALSE(exists_test("graph_EdgeWeight.tsv"));
}

TEST(RWOutputTest, test_12)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 4);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_TSV);
    ASSERT_EQ(res, 0);
    ASSERT_TRUE(exists_test("graph.tsv"));
    ASSERT_FALSE(exists_test("graph_NodeFeat.tsv"));
    ASSERT_FALSE(exists_test("graph_EdgeWeight.tsv"));
}

TEST(RWOutputTest, test_13)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_TSV, ".", "test_13");
    ASSERT_EQ(res, 0);
    ASSERT_TRUE(exists_test("test_13.tsv"));
    ASSERT_FALSE(exists_test("test_13_NodeFeat.tsv"));
    ASSERT_FALSE(exists_test("test_13_EdgeWeight.tsv"));
}

TEST(RWOutputTest, test_14)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::OUT_1, "test_14");
    ASSERT_EQ(res, -1);
    ASSERT_FALSE(exists_test("test_14.tsv"));
    ASSERT_FALSE(exists_test("test_14_NodeFeat.tsv"));
    ASSERT_FALSE(exists_test("test_14_EdgeWeight.tsv"));
}

TEST(RWOutputTest, test_15)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_TSV, ".", "test_15", false, true, true);
    ASSERT_EQ(res, 0);
    ASSERT_TRUE(exists_test("test_15.tsv"));
    ASSERT_TRUE(exists_test("test_15_NodeFeat.tsv"));
    ASSERT_TRUE(exists_test("test_15_EdgeWeight.tsv"));
}

TEST(RWOutputTest, test_16)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_TSV, ".", "test_16", false, false, true);
    ASSERT_EQ(res, 0);
    ASSERT_TRUE(exists_test("test_16.tsv"));
    ASSERT_FALSE(exists_test("test_16_NodeFeat.tsv"));
    ASSERT_TRUE(exists_test("test_16_EdgeWeight.tsv"));
}

TEST(RWOutputTest, test_17)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_TSV, ".", "test_17", false, true, false);
    ASSERT_EQ(res, 0);
    ASSERT_TRUE(exists_test("test_17.tsv"));
    ASSERT_TRUE(exists_test("test_17_NodeFeat.tsv"));
    ASSERT_FALSE(exists_test("test_17_EdgeWeight.tsv"));
}

TEST(RWOutputTest, test_18)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_TSV, ".", "test_18");
    ASSERT_EQ(res, 0);
    ASSERT_TRUE(exists_test("test_18.tsv"));
    ASSERT_FALSE(exists_test("test_18_NodeFeat.tsv"));
    ASSERT_FALSE(exists_test("test_18_EdgeWeight.tsv"));

    CXXGRAPH::Graph<int> readGraph;
    readGraph.readFromFile(CXXGRAPH::InputOutputFormat::STANDARD_TSV, ".", "test_18");
    auto readNode = readGraph.getNodeSet();
    auto readEdge = readGraph.getEdgeSet();
    ASSERT_EQ(readEdge.size(), 3);
    ASSERT_EQ(readNode.size(), 3);

    for (auto readEdgeIt = readEdge.begin(); readEdgeIt != readEdge.end(); ++readEdgeIt)
    {
        if ((*readEdgeIt)->getId() == 1)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && (*readEdgeIt)->isDirected().value());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node1.getId());
            //ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node1.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node2.getId());
            //ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node2.getData());
        }
        else if ((*readEdgeIt)->getId() == 2)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && (*readEdgeIt)->isDirected().value());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node2.getId());
            //ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node2.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node3.getId());
            //ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node3.getData());
        }
        else if ((*readEdgeIt)->getId() == 3)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && !(*readEdgeIt)->isDirected().value());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node1.getId());
            //ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node1.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node3.getId());
            //ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node3.getData());
        }
        else
        {
            ASSERT_TRUE(false); // forced Error
        }
    }
}

TEST(RWOutputTest, test_19)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_TSV, ".", "test_19", false, true);
    ASSERT_EQ(res, 0);
    ASSERT_TRUE(exists_test("test_19.tsv"));
    ASSERT_TRUE(exists_test("test_19_NodeFeat.tsv"));
    ASSERT_FALSE(exists_test("test_19_EdgeWeight.tsv"));

    CXXGRAPH::Graph<int> readGraph;
    readGraph.readFromFile(CXXGRAPH::InputOutputFormat::STANDARD_TSV, ".", "test_19", false, true);
    auto readNode = readGraph.getNodeSet();
    auto readEdge = readGraph.getEdgeSet();
    ASSERT_EQ(readEdge.size(), 3);
    ASSERT_EQ(readNode.size(), 3);

    for (auto readEdgeIt = readEdge.begin(); readEdgeIt != readEdge.end(); ++readEdgeIt)
    {
        if ((*readEdgeIt)->getId() == 1)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && (*readEdgeIt)->isDirected().value());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node1.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node1.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node2.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node2.getData());
        }
        else if ((*readEdgeIt)->getId() == 2)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && (*readEdgeIt)->isDirected().value());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node2.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node2.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node3.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node3.getData());
        }
        else if ((*readEdgeIt)->getId() == 3)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && !(*readEdgeIt)->isDirected().value());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node1.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node1.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node3.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node3.getData());
        }
        else
        {
            ASSERT_TRUE(false); // forced Error
        }
    }
}

TEST(RWOutputTest, test_20)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_TSV, ".", "test_20", false, true, true);
    ASSERT_EQ(res, 0);
    ASSERT_TRUE(exists_test("test_20.tsv"));
    ASSERT_TRUE(exists_test("test_20_NodeFeat.tsv"));
    ASSERT_TRUE(exists_test("test_20_EdgeWeight.tsv"));

    CXXGRAPH::Graph<int> readGraph;
    readGraph.readFromFile(CXXGRAPH::InputOutputFormat::STANDARD_TSV, ".", "test_20", false, true, true);
    auto readNode = readGraph.getNodeSet();
    auto readEdge = readGraph.getEdgeSet();
    ASSERT_EQ(readEdge.size(), 3);
    ASSERT_EQ(readNode.size(), 3);

    for (auto readEdgeIt = readEdge.begin(); readEdgeIt != readEdge.end(); ++readEdgeIt)
    {
        if ((*readEdgeIt)->getId() == 1)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && (*readEdgeIt)->isDirected().value());
            ASSERT_TRUE((*readEdgeIt)->isWeighted().has_value() && (*readEdgeIt)->isWeighted().value());
            ASSERT_EQ((dynamic_cast<const CXXGRAPH::Weighted *>(*readEdgeIt))->getWeight(), 5);
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node1.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node1.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node2.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node2.getData());
        }
        else if ((*readEdgeIt)->getId() == 2)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && (*readEdgeIt)->isDirected().value());
            ASSERT_TRUE((*readEdgeIt)->isWeighted().has_value() && !(*readEdgeIt)->isWeighted().value());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node2.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node2.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node3.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node3.getData());
        }
        else if ((*readEdgeIt)->getId() == 3)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && !(*readEdgeIt)->isDirected().value());
            ASSERT_TRUE((*readEdgeIt)->isWeighted().has_value() && (*readEdgeIt)->isWeighted().value());
            ASSERT_EQ((dynamic_cast<const CXXGRAPH::Weighted *>(*readEdgeIt))->getWeight(), 6);
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node1.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node1.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node3.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node3.getData());
        }
        else
        {
            ASSERT_TRUE(false); // forced Error
        }
    }
}

TEST(RWOutputTest, test_21)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_CSV, ".", "test_21", true, true, false);
    ASSERT_EQ(res, 0);
    ASSERT_FALSE(exists_test("test_21.csv"));
    ASSERT_FALSE(exists_test("test_21_NodeFeat.csv"));
    ASSERT_FALSE(exists_test("test_21_EdgeWeight.csv"));
    ASSERT_TRUE(exists_test("test_21.csv.gz"));
    ASSERT_TRUE(exists_test("test_21_NodeFeat.csv.gz"));
    ASSERT_FALSE(exists_test("test_21_EdgeWeight.csv.gz"));
}

TEST(RWOutputTest, test_22)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_CSV, ".", "test_22", true, true, true);
    ASSERT_EQ(res, 0);
    ASSERT_FALSE(exists_test("test_22.csv"));
    ASSERT_FALSE(exists_test("test_22_NodeFeat.csv"));
    ASSERT_FALSE(exists_test("test_22_EdgeWeight.csv"));
    ASSERT_TRUE(exists_test("test_22.csv.gz"));
    ASSERT_TRUE(exists_test("test_22_NodeFeat.csv.gz"));
    ASSERT_TRUE(exists_test("test_22_EdgeWeight.csv.gz"));

    CXXGRAPH::Graph<int> readGraph;
    auto readResult = readGraph.readFromFile(CXXGRAPH::InputOutputFormat::STANDARD_CSV, ".", "test_22", true, true, true);
    ASSERT_EQ(readResult, 0);
    auto readNode = readGraph.getNodeSet();
    auto readEdge = readGraph.getEdgeSet();
    ASSERT_EQ(readEdge.size(), 3);
    ASSERT_EQ(readNode.size(), 3);

    for (auto readEdgeIt = readEdge.begin(); readEdgeIt != readEdge.end(); ++readEdgeIt)
    {
        if ((*readEdgeIt)->getId() == 1)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && (*readEdgeIt)->isDirected().value());
            ASSERT_TRUE((*readEdgeIt)->isWeighted().has_value() && (*readEdgeIt)->isWeighted().value());
            ASSERT_EQ((dynamic_cast<const CXXGRAPH::Weighted *>(*readEdgeIt))->getWeight(), 5);
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node1.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node1.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node2.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node2.getData());
        }
        else if ((*readEdgeIt)->getId() == 2)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && (*readEdgeIt)->isDirected().value());
            ASSERT_TRUE((*readEdgeIt)->isWeighted().has_value() && !(*readEdgeIt)->isWeighted().value());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node2.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node2.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node3.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node3.getData());
        }
        else if ((*readEdgeIt)->getId() == 3)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && !(*readEdgeIt)->isDirected().value());
            ASSERT_TRUE((*readEdgeIt)->isWeighted().has_value() && (*readEdgeIt)->isWeighted().value());
            ASSERT_EQ((dynamic_cast<const CXXGRAPH::Weighted *>(*readEdgeIt))->getWeight(), 6);
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node1.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node1.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node3.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node3.getData());
        }
        else
        {
            ASSERT_TRUE(false); // forced Error
        }
    }
}

TEST(RWOutputTest, test_23)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_CSV, ".", "test_23", true, false, false);
    ASSERT_EQ(res, 0);
    ASSERT_FALSE(exists_test("test_23.csv"));
    ASSERT_FALSE(exists_test("test_23_NodeFeat.csv"));
    ASSERT_FALSE(exists_test("test_23_EdgeWeight.csv"));
    ASSERT_TRUE(exists_test("test_23.csv.gz"));
    ASSERT_FALSE(exists_test("test_23_NodeFeat.csv.gz"));
    ASSERT_FALSE(exists_test("test_23_EdgeWeight.csv.gz"));
}

TEST(RWOutputTest, test_24)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_TSV, ".", "test_24", true, true, false);
    ASSERT_EQ(res, 0);
    ASSERT_FALSE(exists_test("test_24.tsv"));
    ASSERT_FALSE(exists_test("test_24_NodeFeat.tsv"));
    ASSERT_FALSE(exists_test("test_24_EdgeWeight.tsv"));
    ASSERT_TRUE(exists_test("test_24.tsv.gz"));
    ASSERT_TRUE(exists_test("test_24_NodeFeat.tsv.gz"));
    ASSERT_FALSE(exists_test("test_24_EdgeWeight.tsv.gz"));
}

TEST(RWOutputTest, test_25)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    std::pair<const CXXGRAPH::Node<int> *, const CXXGRAPH::Node<int> *> pairNode(&node1, &node2);
    CXXGRAPH::DirectedWeightedEdge<int> edge1(1, pairNode, 5);
    CXXGRAPH::DirectedEdge<int> edge2(2, node2, node3);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge1);
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_TSV, ".", "test_25", true, true, true);
    ASSERT_EQ(res, 0);
    ASSERT_FALSE(exists_test("test_25.tsv"));
    ASSERT_FALSE(exists_test("test_25_NodeFeat.tsv"));
    ASSERT_FALSE(exists_test("test_25_EdgeWeight.tsv"));
    ASSERT_TRUE(exists_test("test_25.tsv.gz"));
    ASSERT_TRUE(exists_test("test_25_NodeFeat.tsv.gz"));
    ASSERT_TRUE(exists_test("test_25_EdgeWeight.tsv.gz"));

    CXXGRAPH::Graph<int> readGraph;
    auto readResult = readGraph.readFromFile(CXXGRAPH::InputOutputFormat::STANDARD_TSV, ".", "test_25", true, true, true);
    ASSERT_EQ(readResult, 0);
    auto readNode = readGraph.getNodeSet();
    auto readEdge = readGraph.getEdgeSet();
    ASSERT_EQ(readEdge.size(), 3);
    ASSERT_EQ(readNode.size(), 3);

    for (auto readEdgeIt = readEdge.begin(); readEdgeIt != readEdge.end(); ++readEdgeIt)
    {
        if ((*readEdgeIt)->getId() == 1)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && (*readEdgeIt)->isDirected().value());
            ASSERT_TRUE((*readEdgeIt)->isWeighted().has_value() && (*readEdgeIt)->isWeighted().value());
            ASSERT_EQ((dynamic_cast<const CXXGRAPH::Weighted *>(*readEdgeIt))->getWeight(), 5);
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node1.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node1.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node2.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node2.getData());
        }
        else if ((*readEdgeIt)->getId() == 2)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && (*readEdgeIt)->isDirected().value());
            ASSERT_TRUE((*readEdgeIt)->isWeighted().has_value() && !(*readEdgeIt)->isWeighted().value());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node2.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node2.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node3.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node3.getData());
        }
        else if ((*readEdgeIt)->getId() == 3)
        {
            ASSERT_TRUE((*readEdgeIt)->isDirected().has_value() && !(*readEdgeIt)->isDirected().value());
            ASSERT_TRUE((*readEdgeIt)->isWeighted().has_value() && (*readEdgeIt)->isWeighted().value());
            ASSERT_EQ((dynamic_cast<const CXXGRAPH::Weighted *>(*readEdgeIt))->getWeight(), 6);
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getId(), node1.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().first->getData(), node1.getData());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getId(), node3.getId());
            ASSERT_EQ((*readEdgeIt)->getNodePair().second->getData(), node3.getData());
        }
        else
        {
            ASSERT_TRUE(false); // forced Error
        }
    }
}

TEST(RWOutputTest, test_26)
{
    CXXGRAPH::Node<int> node1(1, 1);
    CXXGRAPH::Node<int> node2(2, 2);
    CXXGRAPH::Node<int> node3(3, 3);
    CXXGRAPH::DirectedWeightedEdge<int> edge2(2, node2, node3, 1);
    CXXGRAPH::UndirectedWeightedEdge<int> edge3(3, node1, node3, 6);
    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    edgeSet.push_back(&edge2);
    edgeSet.push_back(&edge3);
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_TSV, ".", "test_26", true, false, false);
    ASSERT_EQ(res, 0);
    ASSERT_FALSE(exists_test("test_26.tsv"));
    ASSERT_FALSE(exists_test("test_26_NodeFeat.tsv"));
    ASSERT_FALSE(exists_test("test_26_EdgeWeight.tsv"));
    ASSERT_TRUE(exists_test("test_26.tsv.gz"));
    ASSERT_FALSE(exists_test("test_26_NodeFeat.tsv.gz"));
    ASSERT_FALSE(exists_test("test_26_EdgeWeight.tsv.gz"));
}

TEST(RWOutputTest, test_27)
{

    std::list<const CXXGRAPH::Edge<int> *> edgeSet;
    for (auto edge : edges)
    {
        edgeSet.push_back(edge.second);
    }
    CXXGRAPH::Graph<int> graph(edgeSet);
    int res = graph.writeToFile(CXXGRAPH::InputOutputFormat::STANDARD_TSV, ".", "test_27", true, false, false);
    ASSERT_EQ(res, 0);
    ASSERT_FALSE(exists_test("test_27.tsv"));
    ASSERT_FALSE(exists_test("test_27_NodeFeat.tsv"));
    ASSERT_FALSE(exists_test("test_27_EdgeWeight.tsv"));
    ASSERT_TRUE(exists_test("test_27.tsv.gz"));
    ASSERT_FALSE(exists_test("test_27_NodeFeat.tsv.gz"));
    ASSERT_FALSE(exists_test("test_27_EdgeWeight.tsv.gz"));
    std::ifstream file("test_27.tsv", std::ios::binary);
    file.seekg(0, std::ios::end);
    int file_size = file.tellg();
    std::ifstream fileCompressed("a.txt", std::ios::binary);
    fileCompressed.seekg(0, std::ios::end);
    int file_compressed_size = fileCompressed.tellg();
    ASSERT_LE(file_compressed_size, file_size);
}