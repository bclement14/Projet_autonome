#ifndef KMEANS_H
#define KMEANS_H

#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

class Kmeans
{
public:
    Kmeans();
    std::vector< std::vector<double> > initialise_data(std::vector< std::vector<double> > data, int nb_liste_noyaux);
    std::vector < std::vector< std::vector<double> > > MaJ_cluster(std::vector< std::vector<double> > data, std::vector< std::vector<double> > liste_noyaux);
    std::vector< std::vector<double> > MaJ_liste_noyaux(std::vector < std::vector< std::vector<double> > > cluster);
    std::vector< std::vector<double> > Covariance(std::vector< std::vector<double> > v1, std::vector< std::vector<double> > v2);

};

#endif // KMEANS_H
