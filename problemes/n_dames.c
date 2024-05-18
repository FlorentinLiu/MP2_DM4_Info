#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

char* variable(int i, int j){
    char* res = malloc(10*sizeof(char));
    sprintf(res,"X_%d_%d",i,j);
    return res;
}

char* contrainte_une_ligne(int i, int n){
    char** l = malloc(n*sizeof(char*));
    for (int j = 0; j < n; j++){
        l[j] = variable(i,j);
    }
    int *taille_phi1=NULL;
    int *taille_phi2=NULL;
    char* phi1 = au_moins_une(l,n,taille_phi1);
    char* phi2 = au_plus_une(l,n,taille_phi2);
    char* phi3 = malloc(   ((*taille_phi1)+ (*taille_phi2)+1)*sizeof(char)); 
    strcpy(phi3, phi1); 
    strcat(phi3, "&");
    strcat(phi3, phi2);

    free (l);
    return phi3;
}

char* contrainte_toutes_lignes(int n){
    char** l = malloc(n*sizeof(char*));
    for (int i = 0; i < n; i++){
        char* phi = contrainte_une_ligne(i,n);
        l[i] = phi;
    }
    char* res = separation_et   (l,n);
    free(l);
    return res;
}

char * contrainte_une_colonne(int i ,int n ){
   char** l=malloc(n*sizeof(char*));
   for(int j=0;j<n;j++){
      l[j]=variable(j,i);
   }
   int *taille_phi=NULL;
   char* phi = au_moins_une(l,n,taille_phi);

    

    free (l);
    return phi;
}

char *contrainte_toutes_colonnes(int n ){
    char** l = malloc(n*sizeof(char*));
    char *phi=NULL;
    for (int i = 0; i < n; i++){
        phi = contrainte_une_colonne(i,n);
        l[i] = phi;
    }
    char* res = separation_et (l,n);
    free(l);
    return res;
}
//Diagonale -1 -> diagonale qui commence à [1][0]
char *contrainte_une_diagonale(int i,int n ){
    char **l=malloc(n*sizeof(char*));
    
    if (i<0){
       i= -i ;
       int colonne=0; 
       n=n-i;
       for(int j=i;j<n;j++){
          l[colonne]=variable(j,colonne);
          colonne++;
       }
    }
    else{
       int ligne=0;
       n=n-i;
       for(int j=i;j<n;j++){
          l[ligne]=variable(ligne,j);
          ligne++;
       }
    }
    int *taille_phi=NULL;
    char *phi=au_plus_une(l,n,taille_phi);

    free(l);
    return phi;


}

char *contraire_toute_diagonale(int n ){
   char** l = malloc(((2*n)-1)*sizeof(char*));
    char *phi=NULL;
    l[0]=contrainte_une_diagonale(0,n);

    for (int i = -1; i > (-n); i--){
        phi = contrainte_une_colonne(i,n);
        l[-i] = phi;
    }
    for(int i=1;i<n;i++){
       phi=contrainte_une_diagonale(i,n);
       l[i+n+1]=phi;
    }
    char* res = separation_et (l,n);
    free(l);
    return res;
}


int main(){
    char* phi = contrainte_toutes_lignes(5);
    printf("%s\n", phi); 
    return 0;
}
