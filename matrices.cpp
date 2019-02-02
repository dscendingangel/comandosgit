#include<stdio.h>
#define TAM 100
#include<math.h>
#include<stdlib.h>

int simplificacionModN (int a, int b){
	int q,r,s;
	if (a>0 && b>0)
		for (q=1 ;  ; q++){
			s=b*q;
			r=a-s;
				if (r<b)
					break;
		}
	else if (a>0 && b<0)
		for (q=-1 ;  ; q--){
			s=b*q;
			r=a-s;
			if (r<-b)
				break;
		}
	else if (a<0 && b>0)
		for (q=-1 ;  ; q--){
			s=b*q;
			r=a-s;
				if (0< r && r<b)
					break;
		}
	else if (a<0 && b<0)
		for (q=1 ;  ; q++){
			s=b*q;
			r=a-s;
			if (0< r && r<-b)
				break;
		}
	return r;
}

int inversoAmodN(int numero,int modN){
	int i = pow(numero,modN-2);
	i = simplificacionModN(i,modN);
	return i;
}
 
void crearMatriz(int mat[TAM][TAM],int m,int n){
		 for(int i=0;i<m;i++){
			 for(int j=0;j<n;j++){
				scanf("%d",&mat[i][j]);
			 }
		 }
}

void printMatriz (int mat[TAM][TAM],int m,int n){
		 for(int i=0;i<m;i++){
			 for(int j=0;j<n;j++){
				 printf("  %d",mat[i][j]);
			 }
			 printf("\n");
		 }
		 printf("\n");
}

// mult es el numero por el que se multiplicara y fila pues es la fila :v
void opPrimerTipo( int mat[TAM][TAM],int mult,int fila,int n, int modN){
	for(int i=0;i<n;i++){
		mat[fila][i]=mat[fila][i]*mult;
		mat[fila][i] = simplificacionModN(mat[fila][i],modN);
	}
}

// mult es el numero por el que se multiplicara y fila pues es la fila :v

// a y b son las filas a intercambiar
void opSegundoTipo(int mat[TAM][TAM],int a, int b,int n){
		int aux;
		for(int i=0;i<n;i++){
				aux=mat[a][i];
				mat[a][i]=mat[b][i];
				mat[b][i]=aux;
		}
}
 // El entero a es la fila a la que se le sumara c veces la fila b.
void opTercerTipoSuma(int mat[TAM][TAM],int a,int b, int c,int n,int ModN){
	for (int i=0;i<n;i++){
		mat[a][i]=mat[a][i]+mat[b][i]*c;
		mat[a][i] = simplificacionModN(mat[a][i],ModN);
	}
}

// \m/ ono \m/
int gaussJordan(int mat[TAM][TAM], int m, int n,int modN){
	int j=0;
	for(int i=0; i < m; i++){
		if(j>=n-1){
			//más ecuaciones que incognitas
			return -1;
		}
		if(mat[i][j] == 0){
			if(i<m){
				for(int k;k<m;k++){
					if(mat[k][j]!=0){
						opSegundoTipo(mat,i,k,n);
						break;
					}
				}
			}else{
				//ecuaciones no independeintes
				return -2;
			}
		}
		if(mat[i][j] != 1){
			int mul=inversoAmodN(mat[i][j],modN);
			opPrimerTipo(mat,mul,i,n,modN);
		}
		for(int k=0;k<m;k++){
			if(k!=i){
				if(mat[k][j]!=0){
					int mul=inversoAmodN(mat[k][j],modN);
					printf(" %d ", mul);
					opTercerTipoSuma(mat,k,i,mul,n,modN);
				}
					printf("\n");
			}
		}
		j++;
		printMatriz(mat,m,n);
	}
}
			

int main(){
	int mat[100][100];
	int m,n,modN;
	puts("Introduce cuantas filas y cuantas columnas tendrá tu matriz");
	scanf("%d %d %d",&m,&n,&modN);
	puts("Llena tu matriz con chocolate");
	crearMatriz(mat,m,n);
	printMatriz(mat,m,n);
  gaussJordan(mat,m,n,modN);
	printMatriz(mat,m,n);
}
