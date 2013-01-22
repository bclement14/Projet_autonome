#include "kmeans.h"

using namespace std;



int main()
{
    Kmeans K;
    cout << "Hello World!" << endl;

    vector< vector<double> > data;
    vector< vector<double> > liste_noyaux;
    int k = 4;

    //Kmeans
    vector<double> datas_uni;

    for(int ii = 0; ii<6; ii++)
    {
        datas_uni.push_back(0);
    }

    for(int i = 0; i<50; i++)
    {
        for(int ii = 0; ii<6; ii++)
        {
            datas_uni[ii]=((ii+(i+1)) + (ii+(i+1)*5)/100);
        }

        data.push_back(datas_uni);
    }

    for(int i = 50; i<100; i++)
    {
        for(int ii = 0; ii<6; ii++)
        {
            datas_uni[ii]=(((ii+i*2) + (ii+i*7)/100)*2);
        }

        data.push_back(datas_uni);
    }

    for(int i = 0; i<data.size(); i++)
    {
        cout << "data : " << i << endl;

        for(int ii=0; ii<data[i].size();ii++)
        {
            cout << data[i][ii] << " ; ";
        }

        cout << endl;
    }

    liste_noyaux = K.initialise_data(data,k);

    for(int i = 0; i<liste_noyaux.size(); i++)
    {
        cout << "Noyau : " << i << endl;

        for(int ii=0; ii<liste_noyaux[i].size();ii++)
        {
            cout << liste_noyaux[i][ii] << " ; " << endl;
        }

        cout << endl;
    }

    string a;
    cin >> a;

    vector < vector< vector<double> > > cluster;
    cluster = K.MaJ_cluster(data, liste_noyaux);

    cout << "Nb clusters : " << cluster.size() << endl;

    for(int i = 0; i<cluster.size(); i++)
    {
        cout << "cluster : " << i << endl;

        for(int ii=0; ii<cluster[i].size();ii++)
        {
            cout << "data : " << ii << endl;
            for(int iii=0; iii<cluster[i][ii].size();iii++)
            {
                cout << cluster[i][ii][iii] << " ; ";
            }
        }

        cout << endl;
    }

    cin >> a;

    liste_noyaux = K.MaJ_liste_noyaux(cluster);

    for(int i = 0; i<liste_noyaux.size(); i++)
    {
        cout << "Noyau : " << i << endl;

        for(int ii=0; ii<liste_noyaux[i].size();ii++)
        {
            cout << liste_noyaux[i][ii] << " ; " << endl;
        }

        cout << endl;
    }

    cluster = K.MaJ_cluster(data, liste_noyaux);

    cout << "Nb clusters : " << cluster.size() << endl;

    for(int i = 0; i<cluster.size(); i++)
    {
        cout << "cluster : " << i << endl;

        for(int ii=0; ii<cluster[i].size();ii++)
        {
            cout << "data : " << ii << endl;
            for(int iii=0; iii<cluster[i][ii].size();iii++)
            {
                cout << cluster[i][ii][iii] << " ; ";
            }
        }

        cout << endl;
    }

    cin >> a;

    liste_noyaux = K.MaJ_liste_noyaux(cluster);

    for(int i = 0; i<liste_noyaux.size(); i++)
    {
        cout << "Noyau : " << i << endl;

        for(int ii=0; ii<liste_noyaux[i].size();ii++)
        {
            cout << liste_noyaux[i][ii] << " ; " << endl;
        }

        cout << endl;
    }

    //EM
    nb_cluster = cluster.size();
    nb_data = data.size();
    vector<double> Priors;
    for(int i = 0; i < nb_cluster; i++)
    {
        Priors.push_back(cluster[i].size()/nb_data);
    }

    return 0;
}

