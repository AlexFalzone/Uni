#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void selectionSort(int *A,int len);
void insertionSort(int *A,int len);
void bubbleSort(int *A,int len);
void mergeSort(int *A,int sx,int dx);
void merge(int *A,int sx,int centro,int dx);
void quickSort(int *A,int sx,int dx);
int partition(int *A,int sx,int dx);

void init(int *A,int len){
	for(int i=0;i<len;i++)	A[i]=rand()%50+1;
}
void stampa(int *A,int len){
	for(int i=0;i<len;i++)	cout<<A[i]<<" ";
	cout<<endl;
}
void swap(int &a,int &b){
	int tmp=a;
	a=b;
	b=tmp;
}
void selectionSort(int *A,int len){
	int min=0;
	for(int i=0;i<len;i++){
		min=i;
		for(int j=i+1;j<len;j++)
			if(A[min]>A[j]) min=j;
		swap(A[i],A[min]);
	}
}
void insertionSort(int *A,int len){
	int tmp=0;
	int j=0;
	for(int i=1;i<len;i++){
		j=i-1;
		tmp=A[i];
		while(j>=0 && A[j]>tmp){
			A[j+1]=A[j];
			j--;
		}
		A[j+1]=tmp;
	}
}
void bubbleSort(int *A,int len){
	bool flag=true;
	for(int i=0;i<len && flag;i++){
		flag=false;
		for(int j=0;j<len-1-i;j++){
			if(A[j]>A[j+1]) {
				flag=true;
				swap(A[j],A[j+1]);
			}
		}
	}
}
void mergeSort(int *A,int sx,int dx){
	if(sx<dx){
		int centro=(sx+dx)/2;
		mergeSort(A,sx,centro);
		mergeSort(A,centro+1,dx);
		merge(A,sx,centro,dx);
	}
}
void merge(int *A,int sx,int centro,int dx){
	int b[dx];
	int i=sx,k=sx,j=centro+1;
	while((i<=centro) && (j<=dx)){
		if(A[i]<A[j]){
			b[k]=A[i];
			i++;
		}
		else{
			b[k]=A[j];
			j++;
		}
		k++;
	}
	while(i<=centro){
		b[k]=A[i];
		k++;
		i++;
	}
	while(j<=dx){
		b[k]=A[j];
		j++;
		k++;
	}
	for(int k=sx;k<=dx;k++)A[k]=b[k];
	
}
void quickSort(int *A,int sx,int dx){
	if(sx<dx){
		int p=partition(A,sx,dx);
		quickSort(A,sx,p-1);
		quickSort(A,p+1,dx);
	}
}
int partition(int *A,int sx,int dx){
	int piv=A[dx];
	int j=sx-1;
	for(int i=sx;i<dx;i++){
		if(A[i]<piv){
			j++;
			swap(A[j],A[i]);
		}
	}
	j++;
	swap(A[j],A[dx]);
	return j;
}

int main(){
	srand(time(NULL));
	int len=10;
	int A[len];
	init(A,len);
	stampa(A,len);
	quickSort(A,0,9);
	stampa(A,len);
	
}





