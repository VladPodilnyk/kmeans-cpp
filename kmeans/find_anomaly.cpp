#include "kmeans.hpp"

int main()
{
    auto data = utils::Parser::getDataFromFile("../data/durudataset.txt");
    auto kmeans = ml::kmeans();
    auto centroids = kmeans(data[0].size(), 0, data);

    utils::FileWriter::dump_data(centroids, data);
    return 0;
}