#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

vector< vector<double> > initialise_data(vector< vector<double> > data, int nb_liste_noyaux)
{
    vector< vector<double> > liste_noyaux;

    /*int taille_data = data.size();

    int taille_cluster = taille_data/nb_liste_noyaux;

    vector<double> somme;
    vector<double> noyau;


    for(int ii = 0; ii < data[0].size(); ii++)
    {
        somme.push_back(0);
        noyau.push_back(0);
    }

    for (int i=0; i<nb_liste_noyaux; i++)
    {
        for(int ii = i*taille_cluster; ii< taille_cluster*(i+1); ii++)
        {
            for(int iii = 0; iii < data[0].size(); iii++)
            {
                somme[iii] += data[ii][iii];
            }
        }

        for(int ii = 0; ii<somme.size(); ii++)
        {
            noyau[ii] = (somme[ii]/taille_cluster);
        }

        liste_noyaux.push_back(noyau);
    }*/
    vector<double> noyau;
    srand ( time(NULL) );
    int data_size = data.size();
    int indice;
    for(int i=0; i< nb_liste_noyaux; i++)
    {
        indice = rand() % data_size;
        noyau = data[indice];
        liste_noyaux.push_back(noyau);
    }

    return liste_noyaux;
}

vector < vector< vector<double> > > MaJ_cluster(vector< vector<double> > data, vector< vector<double> > liste_noyaux)
{
    double diff_dimension;
    int num_noyau;
    double diff;
    double min_diff = -1;
    vector < vector< vector<double> > > cluster;

    for(int iii =0; iii<liste_noyaux.size(); iii++)
    {
        vector< vector<double> > liste_data;
        cluster.push_back(liste_data);

    }


    for (int i = 0; i < data.size(); i++)
    {
        num_noyau = 0;
        min_diff = -1;
        for(int iii =0; iii<liste_noyaux.size(); iii++)
        {
            diff =0;
            for (int ii =0; ii<data[i].size(); ii++)
            {
                diff_dimension = (data[i][ii]-liste_noyaux[iii][ii])*(data[i][ii]-liste_noyaux[iii][ii]);
                diff += diff_dimension;
            }

            if(min_diff == -1 || diff < min_diff)
            {
               min_diff = diff;
               num_noyau=iii;
               //cout << "rentre dedans" <<endl;
            }
            //else
                //cout << "pas dedans" <<endl;
        }

        cluster[num_noyau].push_back(data[i]);
        //for(int ii = 0; ii< data[i].size(); ii++)
        //int b=0;
        //cin >> b;
    }

    return cluster;
}

vector< vector<double> > MaJ_liste_noyaux(vector < vector< vector<double> > > cluster)
{
    vector< vector<double> > liste_noyaux;

    for(int i=0; i<cluster.size(); i++)
    {
        vector<double> noyau;

        for(int iii = 0; iii < cluster[i][0].size(); iii++)
        {
            noyau.push_back(0);
        }

        liste_noyaux.push_back(noyau);
        for(int ii = 0; ii < cluster[i].size();ii++)
        {
            for(int iii = 0; iii < cluster[i][ii].size(); iii++)
            {
                liste_noyaux[i][iii]+=cluster[i][ii][iii];
            }
        }

        for(int iii = 0; iii < liste_noyaux[i].size(); iii++)
        {
            liste_noyaux[i][iii] = liste_noyaux[i][iii]/cluster[i].size();
        }

    }

    return liste_noyaux;
}

int main()
{

    cout << "Hello World!" << endl;

    vector< vector<double> > data;
    vector< vector<double> > liste_noyaux;
    int k = 4;



    //Inititalisation
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

    liste_noyaux = initialise_data(data,k);

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
    cluster = MaJ_cluster(data, liste_noyaux);

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

    liste_noyaux = MaJ_liste_noyaux(cluster);

    for(int i = 0; i<liste_noyaux.size(); i++)
    {
        cout << "Noyau : " << i << endl;

        for(int ii=0; ii<liste_noyaux[i].size();ii++)
        {
            cout << liste_noyaux[i][ii] << " ; " << endl;
        }

        cout << endl;
    }

    cluster = MaJ_cluster(data, liste_noyaux);

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

    liste_noyaux = MaJ_liste_noyaux(cluster);

    for(int i = 0; i<liste_noyaux.size(); i++)
    {
        cout << "Noyau : " << i << endl;

        for(int ii=0; ii<liste_noyaux[i].size();ii++)
        {
            cout << liste_noyaux[i][ii] << " ; " << endl;
        }

        cout << endl;
    }



    //Algo

    return 0;
}

