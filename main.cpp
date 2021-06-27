#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;

// This program create four threads and each thread calculate sum of 1/4th part of array (dividing array into four parts)
// and also sum of result array and in the end after collecting the sum of result array from each thread and finally writes the output in file

int k;
int* p;
int* q;
int *result;

void readfromfile(string filename, int* &p, int* &q, int& size);

void* part1(void* param) {
	int size2 = *(int*) param;
	int *a=new int;
    *a = 0;
	for (int i=0;i<size2;i++)
	{
		result[i]=p[i]+q[i];
        *a += result[i];
	}
	pthread_exit((void*) a);
}

void* part2(void* param) {
	int size = *(int*) param;
	int *a=new int;
	for (int i=size;i<2*size;i++)
	{
		result[i]=p[i]+q[i];
        *a += result[i];
	}
	pthread_exit((void *) a);
}

void* part3(void* param) {
	int size = *(int*) param;
	int *a=new int;
	for (int i=2*size;i<3*size;i++)
	{
		result[i]=p[i]+q[i];
        *a += result[i];
	}
	pthread_exit((void *) a);
}

void* part4(void* param) {
	int size = *(int*) param;
	int *a=new int;
	for (int i=3*size;i<(4*size)+k;i++)
	{
        result[i] =p[i] + q[i];
		*a+=result[i];
	}
	pthread_exit((void*) a);
}

int main() {
  	int size = 0;
	ofstream fout("result");
	readfromfile("input.txt",p,q,size);
    if (size%2!=0)
        k = 1;
	result = new int[size];
	pthread_t id;
	pthread_t id1;
	pthread_t id2;
	pthread_t id3;
    int sum=0;
	int size1 = size / 4;
	if (pthread_create(&id, NULL, &part1, &size1)==-1) {
	cout<<"Thread Creation Failed!"<<endl;
	return 1;
	}
	if (pthread_create(&id1, NULL, &part2, &size1)==-1) {
	cout<<"Thread Creation Failed!"<<endl;
	return 1;
	}
	if (pthread_create(&id2, NULL, &part3, &size1)==-1) {
	cout<<"Thread Creation Failed!"<<endl;
	return 1;
	}
	if (pthread_create(&id3, NULL, &part4, &size1)==-1) {
	cout<<"Thread Creation Failed!"<<endl;
	return 1;
	}
	int *ptr, *ptr1, *ptr2, *ptr3;
	pthread_join(id, (void**) &ptr);
	pthread_join(id1, (void**) &ptr1);
	pthread_join(id2, (void**) &ptr2);
	pthread_join(id3, (void**) &ptr3);
	sum = *ptr+*ptr1+*ptr2+*ptr3;
	for (int i=0;i<size;i++) {
		fout<<result[i];
		fout<<"\n";
	}
	fout<<"\n";
	fout<<sum;
}

void readfromfile(string filename,int* &p, int* &q, int& size) {
	int a[100];
	int b[100];
	int i = 0;
	ifstream fin(filename);
	if (fin.is_open()) {
		while (!fin.eof()) {
			fin >> a[i];
			fin >> b[i];
			i++;
		}
	}
	size = i;
	p = new int[size];
	q = new int[size];
	for (int i = 0; i < size; i++) {
		p[i] = a[i];
		q[i] = b[i];
	}
}
